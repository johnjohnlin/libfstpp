// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
// direct include
#include "fstcpp/Writer.h"
// C system headers
// C++ standard library headers
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstring>
#include <cstdio>
// Other libraries' .h files.
#include <lz4.h>
#include <zlib.h>
// Your project's .h files.
#include "fstcpp/StreamWriteHelper.h"
#include "fstcpp/VariableInfo.h"
#include "fstcpp/assertion.h"
#include "fstcpp/fst.h"
#include "fstcpp/fst_string_view.h"

using namespace std;

// AT(x) is used to access vector at index x, and it will throw exception if out of bound
// in debug mode, but in release mode, it will not throw exception
// Usually you should only need AT(x) only at very hot code path.
#ifndef NDEBUG
#  define AT(x) .at(x)
#else
#  define AT(x) [x]
#endif

namespace fst {

namespace detail {

void BlackoutData::EmitDumpActive(uint64_t current_timestamp, bool enable) {
	StreamWriteHelper h(buffer);
	h
	.WriteUInt<uint8_t>(enable)
	.WriteLEB128(current_timestamp - previous_timestamp);
	++count;
}

ValueChangeData::ValueChangeData() {
	variable_infos.reserve(1024);
}

ValueChangeData::~ValueChangeData() = default;

void ValueChangeData::KeepOnlyTheLatestValue() {
	for (auto& v : variable_infos) {
		v.KeepOnlyTheLatestValue();
	}
	timestamps.resize(0);
}

} // namespace detail

void Writer::Open(const string_view_ name) {
	CHECK(not main_fst_file_.is_open());
	main_fst_file_.open(string(name), ios::binary);
	// reserve space for header, we will write it at Close(), append geometry and hierarchy at the end
	// wave data will be flushed in between by FlushWaveDataIfNecessary_()
	main_fst_file_.seekp(kSharedBlockHeaderSize + HeaderInfo::total_size, ios_base::beg);
}

void Writer::Close() {
	if (not main_fst_file_.is_open()) return;
	// Finalize header fields
	if (header_.date[0] == '\0') {
		// date is not set yet, set to the current date
		SetDate();
	}
	if (header_.start_time == kInvalidTime) {
		header_.start_time = 0;
	}
	FlushValueChangeData_(value_change_data_, main_fst_file_);
	AppendGeometry_(main_fst_file_);
	AppendHierarchy_(main_fst_file_);
	AppendBlackout_(main_fst_file_);
	// Note: write header seek to 0, so we need to do
	// this after all append operations
	WriteHeader_(header_, main_fst_file_);
	main_fst_file_.close();
}

/////////////////////////////////////////
// Hierarchy / variable API
/////////////////////////////////////////
void Writer::SetScope(
	Hierarchy::ScopeType scopetype,
	const string_view_ scopename, const string_view_ scopecomp
) {
	CHECK(not hierarchy_finalized_);
	StreamWriteHelper h(hierarchy_buffer_);
	h
	.WriteUInt<uint8_t>(Hierarchy::ScopeControlType::eVcdScope)
	.WriteUInt<uint8_t>(scopetype)
	.WriteString0(scopename)
	.WriteString0(scopecomp);
	++header_.num_scopes;
}

void Writer::Upscope() {
	CHECK(not hierarchy_finalized_);
	// TODO: shall we inline it?
	StreamWriteHelper h(hierarchy_buffer_);
	h.WriteUInt<uint8_t>(Hierarchy::ScopeControlType::eVcdUpscope);
}

Handle Writer::CreateVar(
	Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
	uint32_t bitwidth, const string_view_ name,
	Handle alias_handle
) {
	CHECK(not hierarchy_finalized_);
	// Write hierarchy entry: type, direction, name, length, alias
	StreamWriteHelper h(hierarchy_buffer_);

	// determine real/string handling like original C implementation
	bool is_real = false;
	switch (vartype) {
		case Hierarchy::VarType::eVcdReal:
		case Hierarchy::VarType::eVcdReal_parameter:
		case Hierarchy::VarType::eVcdRealtime:
		case Hierarchy::VarType::eSvShortreal:
			is_real = true;
			bitwidth = 8; // recast to double size
			break;
		case Hierarchy::VarType::eGenString:
			bitwidth = 0;
			break;
		default:
			break;
	}
	if (alias_handle > header_.num_handles) {
		// sanitize
		alias_handle = 0;
	}
	const bool is_alias = alias_handle != 0;
	// This counter is incremented whether alias or non-alias
	++header_.num_vars;
	if (not is_alias) {
		// This counter is incremented only for non-alias variables
		++header_.num_handles;
		alias_handle = header_.num_handles;
	}

	h
	.WriteUInt<uint8_t>(vartype)
	.WriteUInt<uint8_t>(vardir)
	.WriteString0(name)
	.WriteLEB128(bitwidth)
	.WriteLEB128(is_alias ? alias_handle : 0);

	// If alias_handle == 0, we must allocate geom/valpos/curval entries and create a new handle
	if (not is_alias) {
		StreamWriteHelper g(geometry_buffer_);
		// I don't know why the original C implementation encode bitwidth again
		const uint32_t geom_len = (
			bitwidth == 0 ? uint32_t(-1) :
			is_real       ? uint32_t(0) :
			                bitwidth
		);
		g.WriteLEB128(geom_len);
		value_change_data_.variable_infos.emplace_back(bitwidth, is_real);
	}

	return alias_handle;
}

// LCOV_EXCL_START
Handle Writer::CreateVar2(
	Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
	uint32_t bitwidth, const string_view_ name, Handle alias_handle, const string_view_ type,
	Hierarchy::SupplementalVarType svt, Hierarchy::SupplementalDataType sdt
) {
	CHECK(not hierarchy_finalized_);
	(void)vartype; (void)vardir; (void)bitwidth; (void)name; (void)alias_handle; (void)type; (void)svt; (void)sdt;
	throw runtime_error("TODO");
	return 0;
}
// LCOV_EXCL_STOP

/////////////////////////////////////////
// Waveform API
/////////////////////////////////////////
void Writer::EmitTimeChange(uint64_t tim) {
	FinalizeHierarchy_();

	if (value_change_data_usage_ > value_change_data_flush_threshold_) {
		FlushValueChangeData_(value_change_data_, main_fst_file_);
	}

	// Update header
	header_.start_time = min(header_.start_time, tim);
	header_.end_time = tim;

	if (value_change_data_.timestamps.empty() or value_change_data_.timestamps.back() != tim) {
		value_change_data_.timestamps.push_back(tim);
	}
}

void Writer::EmitDumpActive(bool enable) {
	// TODO: this API is not fully understood, need to check
	CHECK(not value_change_data_.timestamps.empty());
	blackout_data_.EmitDumpActive(value_change_data_.timestamps.back(), enable);
}

template<typename T, typename ...U>
uint64_t EmitValueHelperStaticDispatch_(
	VariableInfo* var_info,
	const uint64_t time_index,
	U&&... val
) {
	return static_cast<T*>(var_info)->EmitValueChange(time_index, std::forward<U>(val)...);
}

template<typename... T>
void Writer::EmitValueChangeHelper_(Handle handle, T&&... val) {
	// Let data prefetch go first
	auto& var_info = value_change_data_.variable_infos AT(handle - 1);
	__builtin_prefetch(var_info.data.data() + var_info.data.size() - 1, 1, 0);

	FinalizeHierarchy_();

	// Original implementation: virtual, but vtable is too costly, we switch to if-else static dispatch
	value_change_data_usage_ += var_info.EmitValueChange(value_change_data_.timestamps.size() - 1, std::forward<T>(val)...);
}

void Writer::EmitValueChange(Handle handle, const uint32_t *val, EncodingType encoding) {
	EmitValueChangeHelper_(handle, val, encoding);
}

void Writer::EmitValueChange(Handle handle, const uint64_t *val, EncodingType encoding) {
	EmitValueChangeHelper_(handle, val, encoding);
}

void Writer::EmitValueChange(Handle handle, uint64_t val) {
	EmitValueChangeHelper_(handle, val);
}

void Writer::EmitValueChange(Handle handle, const char *val) {
	FinalizeHierarchy_();
	auto &var_info = value_change_data_.variable_infos AT(handle - 1);
	const uint32_t bitwidth = var_info.bitwidth;
	CHECK_NE(bitwidth, 0);

	val += bitwidth;
	thread_local static vector<uint64_t> packed_value_buffer;
	const unsigned num_words = (bitwidth + 63) / 64;
	packed_value_buffer.assign(num_words, 0);
	for (unsigned i = 0; i < num_words; ++i) {
		const char* start = val - std::min((i+1)*64, bitwidth);
		const char* end = val - 64*i;
		packed_value_buffer[i] = 0;
		for (const char* p = start; p < end; ++p) {
			// No checking for invalid characters, follow original C implementation
			packed_value_buffer[i] <<= 1;
			packed_value_buffer[i] |= (*p - '0');
		}
	}

	if (bitwidth <= 64) {
		EmitValueChange(handle, packed_value_buffer.front());
	} else {
		EmitValueChange(handle, packed_value_buffer.data(), EncodingType::eBinary);
	}
}

/////////////////////////////////////////
// File flushing functions
/////////////////////////////////////////
void Writer::WriteHeader_(const Header& header, ostream& os) {
	StreamWriteHelper h(os);
	static char kDefaultWriterName[sizeof(header.writer)] = "fstcppWriter";
	const char* writer_name = header.writer[0] == '\0' ? kDefaultWriterName : header.writer;

	// Actual write
	h
	.Seek(streamoff(0), ios_base::beg)
	.WriteBlockHeader(BlockType::Header, HeaderInfo::total_size)
	.WriteUInt(header.start_time)
	.WriteUInt(header.end_time)
	.WriteFloat(HeaderInfo::kEndianessMagicIdentifier)
	.WriteUInt(header.writer_memory_use)
	.WriteUInt(header.num_scopes)
	.WriteUInt(header.num_vars)
	.WriteUInt(header.num_handles)
	.WriteUInt(header.num_value_change_data_blocks)
	.WriteUInt(header.timescale)
	.Write(writer_name, sizeof(header.writer))
	.Write(header.date, sizeof(header.date))
	.Fill('\0', HeaderInfo::Size::reserved)
	.WriteUInt(static_cast<uint8_t>(header.filetype))
	.WriteUInt(header.timezero);

	DCHECK_EQ(os.tellp(), HeaderInfo::total_size + kSharedBlockHeaderSize);
};

namespace { // compression helpers

// TODO: replace with C++20 concepts
#if 0
template <typename T>
concept BufferLike = requires(T v) {
	{ v.data() } -> std::same_as<char*>;
	{ v.size() } -> std::same_as<std::size_t>;
};
#endif

// These API pass compressed_data to avoid frequent reallocations
template<typename BufferLike1, typename BufferLike2>
void CompressUsingLz4(
	const BufferLike1& uncompressed_data,
	BufferLike2& compressed_data
) {
	const int uncompressed_size = uncompressed_data.size();
	const int compressed_bound = LZ4_compressBound(uncompressed_size);
	compressed_data.resize(compressed_bound);
	const int compressed_size = LZ4_compress_default(
		uncompressed_data.data(),
		compressed_data.data(),
		uncompressed_size,
		compressed_bound
	);
	compressed_data.resize(compressed_size);
}

template<typename BufferLike1, typename BufferLike2>
void CompressUsingZlib(
	const BufferLike1& uncompressed_data,
	BufferLike2& compressed_data,
	int level
) {
	// compress using zlib
	const uLong uncompressed_size = uncompressed_data.size();
	uLongf compressed_bound = compressBound(uncompressed_size);
	compressed_data.resize(compressed_bound);
	const auto z_status = compress2(
		reinterpret_cast<Bytef*>(compressed_data.data()),
		&compressed_bound,
		reinterpret_cast<const Bytef*>(uncompressed_data.data()),
		uncompressed_size,
		level
	);
	if (z_status != Z_OK) {
		throw runtime_error("Failed to compress data with zlib, error code: " + to_string(z_status));
	}
	compressed_data.resize(compressed_bound);
}

template<typename BufferLike1, typename BufferLike2>
auto SelectSmaller(const BufferLike1& compressed_data, const BufferLike2& uncompressed_data) {
	pair<const char*, size_t> ret;
	if (compressed_data.size() < uncompressed_data.size()) {
		ret.first = compressed_data.data();
		ret.second = compressed_data.size();
	} else {
		ret.first = uncompressed_data.data();
		ret.second = uncompressed_data.size();
	}
	return ret;
}

} // namespace

// AppendHierarchy_ and AppendGeometry_ shares a very similar structure
// But they are slightly different in the original C implementation...
void Writer::AppendGeometry_(ostream& os) {
	const string& geometry_uncompressed_data = geometry_buffer_.str();
	if (geometry_uncompressed_data.empty()) {
		// skip the geometry block if there is no data
		return;
	}
	vector<char> geometry_compressed_data;
	CompressUsingZlib(geometry_uncompressed_data, geometry_compressed_data, 9);
	// TODO: Replace with structured binding in C++17
	const auto selected_pair = SelectSmaller(geometry_compressed_data, geometry_uncompressed_data);
	const auto selected_data = selected_pair.first;
	const auto selected_size = selected_pair.second;

	StreamWriteHelper h(os);
	h
	.Seek(0, ios_base::end)
	// 16 is for the uncompressed_size and header_.num_handles
	.WriteBlockHeader(BlockType::Geometry, selected_size + 16)
	.WriteUInt<uint64_t>(geometry_uncompressed_data.size())
	// I don't know why the original C implementation write num_handles again here
	// but we have to follow it
	.WriteUInt(header_.num_handles)
	.Write(selected_data, selected_size);
}

void Writer::AppendHierarchy_(ostream& os) {
	const string& hierarchy_uncompressed_data = hierarchy_buffer_.str();
	if (hierarchy_uncompressed_data.empty()) {
		// skip the hierarchy block if there is no data
		return;
	}

	// compress hierarchy_buffer_ using LZ4.
	const int uncompressed_size = hierarchy_uncompressed_data.size();
	const int compressed_bound = LZ4_compressBound(uncompressed_size);
	vector<char> hierarchy_compressed_data(compressed_bound);
	const int compressed_size = LZ4_compress_default(
		hierarchy_uncompressed_data.data(),
		hierarchy_compressed_data.data(),
		uncompressed_size,
		compressed_bound
	);

	StreamWriteHelper h(os);
	h
	.Seek(0, ios_base::end)
	// +16 is for the uncompressed_size
	.WriteBlockHeader(BlockType::HierarchyLz4Compressed, compressed_size + 8)
	.WriteUInt<uint64_t>(uncompressed_size)
	.Write(hierarchy_compressed_data.data(), compressed_size);
}

void Writer::AppendBlackout_(ostream& os) {
	if (blackout_data_.count == 0) {
		// skip the blackout block if there is no data
		return;
	}
	const string& blackout_data = blackout_data_.buffer.str();
	const auto begin_of_blackout_block = os.tellp();
	StreamWriteHelper h(os);
	h
	// skip the block header
	.Seek(kSharedBlockHeaderSize, ios_base::cur)
	// Note: we cannot know the size beforehand since this length is LEB128 encoded
	.WriteLEB128(blackout_data.size())
	.Write(blackout_data.data(), blackout_data.size());

	const auto size_of_blackout_block = os.tellp() - begin_of_blackout_block;
	h
	// go back to the beginning of the block
	.Seek(begin_of_blackout_block, ios_base::beg)
	// and write the block header
	.WriteBlockHeader(BlockType::Blackout, size_of_blackout_block - kSharedBlockHeaderSize);
}

void detail::ValueChangeData::WriteInitialBits(ostream& os) const {
	// Build vc_bits_data by concatenating each variable's initial bits as documented.
	// We will not compress for now; just generate the raw bytes and print summary to stdout.
	for (size_t i = 0; i < variable_infos.size(); ++i) {
		auto &vref = variable_infos[i];
		vref.DumpInitialBits(os);
	}
}

vector<vector<char>> detail::ValueChangeData::ComputeWaveData() const {
	stringstream ss;
	vector<vector<char>> data;
	for (auto& v : variable_infos) {
		v.DumpValueChanges(ss);
		const string& s = ss.str();
		data.emplace_back(s.begin(), s.end());
		ss.str("");
	}
	return data;
}

vector<int64_t> detail::ValueChangeData::UniquifyWaveData(
	vector<vector<char>>& data
) {
	// After this function, positions[i] is:
	//  - = 0: If data[i] is unique (first occurrence)
	//  - < 0: If data[i] is a duplicate, encoded as -(original_index + 1)
	vector<int64_t> positions(data.size(), 0);
	struct MyHash {
		size_t operator()(const vector<char>* vec) const {
			const string_view_ sv(vec->data(), vec->size());
			return hash<string_view_>()(sv);
		}
	};
	struct MyEqual {
		bool operator()(const vector<char>* a, const vector<char>* b) const {
			return *a == *b;
		}
	};
	unordered_map<const vector<char>*, int64_t, MyHash, MyEqual> data_map;
	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i].empty()) {
			continue;
		}
		// insert vec->i to data_map if not exists
		auto p = data_map.emplace(&data[i], static_cast<int64_t>(i));
		auto it = p.first;
		auto inserted = p.second;

		if (not inserted) {
			// duplicated wave data found
			positions[i] = -(it->second + 1);
			// clear data to save memory
			data[i].clear();
		}
	}
	return positions;
}

uint64_t detail::ValueChangeData::EncodePositionsAndWriteUniqueWaveData(
	ostream& os,
	const vector<vector<char>>& data,
	vector<int64_t>& positions,
	WriterPackType pack_type
) {
	// After this function, positions[i] is:
	//  - = 0: If variable i has no wave data
	//  - < 0: The negative value from FlushValueChangeData_ValueChanges_UniquifyWaveData_, unchanged
	//  - > 0: The size (in bytes) of the wave data block for *previous* variable,
	//         the previous block size of the first block is 1 (required by FST spec).
	StreamWriteHelper h(os);
	int64_t previous_size = 1;
	uint64_t written_count = 0;
	vector<char> compressed_data;
	for (size_t i = 0; i < positions.size(); ++i) {
		if (positions[i] < 0) {
			// duplicate (negative index), do nothing
		} else if (data[i].empty()) {
			// no change (empty data), positions[i] remains 0
		} else {
			// try to compress
			const char* selected_data;
			size_t selected_size;
			if (pack_type == WriterPackType::eNoCompression or data[i].size() < 32) {
				selected_data = data[i].data();
				selected_size = data[i].size();
			} else {
				CompressUsingLz4(data[i], compressed_data);
				const auto selected_pair = SelectSmaller(compressed_data, data[i]);
				selected_data = selected_pair.first;
				selected_size = selected_pair.second;
			}
			const bool is_compressed = selected_data != data[i].data();

			// non-empty unique data, write it
			written_count++;
			streamoff bytes_written;
			h
			.BeginOffset(bytes_written)
			// FST spec: 0 means no compression, >0 for the size of the original data
			.WriteLEB128(is_compressed ? data[i].size() : 0)
			.Write(selected_data, selected_size)
			.EndOffset(&bytes_written);
			positions[i] = previous_size;
			previous_size = bytes_written;
		}
	}
	return written_count;
}

void detail::ValueChangeData::WriteEncodedPositions(const vector<int64_t>& encoded_positions, ostream& os) {
	// Encode positions with the specified run/varint rules into a varint buffer.
	StreamWriteHelper h(os);

	size_t i = 0;
	const size_t n = encoded_positions.size();

	// arbitrary positive value for prev_negative
	// so that first negative is always != prev_negative
	int64_t prev_negative = 1;

	// Please refer to the comments in FlushValueChangeData_ValueChanges_EncodePositionsAndWriteWaveData_()
	// for the encoding rules of positions.
	while (i < n) {
		if (encoded_positions[i] == 0) {
			// zero: handle zero run-length
			size_t run = 0;
			while (i < n && encoded_positions[i] == 0) { ++run; ++i; }
			// encode as signed (run << 1) | 0 and write as signed LEB128
			h.WriteLEB128Signed(run<<1);
		} else {
			// non-zero
			int64_t value_to_encode = 0;
			int64_t cur = encoded_positions[i];
			if (cur < 0) {
				if (cur == prev_negative) {
					value_to_encode = 0;
				} else {
					value_to_encode = cur;
					prev_negative = cur;
				}
			} else {
				value_to_encode = cur;
			}

			// encode as signed (value << 1) | 1 and write as signed LEB128
			h.WriteLEB128Signed((value_to_encode << 1) | 1);

			++i;
		}
	}
}

void detail::ValueChangeData::WriteTimestamps(ostream& os) const {
	// Build LEB128-encoded delta stream (first delta is timestamp[0] - 0)
	StreamWriteHelper h(os);
	uint64_t prev = 0;
	for (size_t i = 0; i < timestamps.size(); ++i) {
		const uint64_t cur = timestamps[i];
		const uint64_t delta = cur - prev;
		h.WriteLEB128(delta);
		prev = cur;
	}
}

void Writer::FlushValueChangeDataConstPart_(
	const detail::ValueChangeData& vcd,
	ostream& os,
	WriterPackType pack_type
) {
	if (vcd.timestamps.empty()) {
		return;
	}

	// 0. Setup
	StreamWriteHelper h(os);

	// 1. Write Block Header & Global Fields (start/end/mem_req placeholder)
	// FST_BL_VCDATA_DYN_ALIAS2 (8) maps to WaveDataVersion3 in fst_file.h
	// The positions we cannot fill in yet
	const auto p_tmp1 = [&]() {
		streamoff start_pos, memory_usage_pos;
		h
		.BeginOffset(start_pos) // record start position
		.WriteBlockHeader(BlockType::WaveDataVersion3, 0 /* Length placeholder 0 */)
		.WriteUInt(vcd.timestamps.front())
		.WriteUInt(vcd.timestamps.back())
		.BeginOffset(memory_usage_pos) // record memory usage position
		.WriteUInt<uint64_t>(0); // placeholder for memory usage
		return make_pair(start_pos, memory_usage_pos);
	}();
	const auto start_pos = p_tmp1.first;
	const auto memory_usage_pos = p_tmp1.second;

	// 2. Bits Section
	{
		stringstream ss;
		vcd.WriteInitialBits(ss);
		string raw = ss.str();
		vector<char> compressed_data;
		const char* selected_data;
		size_t selected_size;
		if (pack_type == WriterPackType::eNoCompression) {
			selected_data = raw.data();
			selected_size = raw.size();
		} else {
			CompressUsingZlib(raw, compressed_data, 4);
			const auto selected_pair = SelectSmaller(compressed_data, raw);
			selected_data = selected_pair.first;
			selected_size = selected_pair.second;
		}

		h
		.WriteLEB128(raw.size()) // uncompressed length
		.WriteLEB128(selected_size) // compressed length
		.WriteLEB128(vcd.variable_infos.size()) // bits count
		.Write(selected_data, selected_size);
	}

	// 3. Waves Section
	// Note: We need positions for the next section
	const auto p_tmp2 = [&,pack_type]() {
		auto wave_data = vcd.ComputeWaveData();
		auto positions = vcd.UniquifyWaveData(wave_data);
		const size_t memory_usage = accumulate(
			wave_data.begin(), wave_data.end(), size_t(0),
			[](size_t a, const auto& b) { return a + b.size(); }
		);
		stringstream ss;
		const uint64_t count = detail::ValueChangeData::EncodePositionsAndWriteUniqueWaveData(ss, wave_data, positions, pack_type);
		(void)count;
		const string raw = ss.str();
		h
		// Note: this is not a typo, I expect we shall write count here.
		// but the spec indeed write vcd.variable_infos.size(),
		// which is repeated 1 times in header block, 2 times in valuechange block
		.WriteLEB128(vcd.variable_infos.size())
		.WriteUInt(uint8_t('4'))
		.Write(raw.data(), raw.size());
		return make_pair(positions, memory_usage);
	}();
	const auto positions = p_tmp2.first;
	const auto memory_usage = p_tmp2.second;

	// 4. Position Section
	{
		const auto pos_begin = os.tellp();
		vcd.WriteEncodedPositions(positions, os);
		const uint64_t pos_size = os.tellp() - pos_begin;
		h.WriteUInt(pos_size); // Length comes AFTER data for positions
	}

	// 5. Time Section
	{
		stringstream ss;
		vcd.WriteTimestamps(ss);
		const string raw = ss.str();
		vector<char> compressed_data;
		const char* selected_data;
		size_t selected_size;
		if (pack_type == WriterPackType::eNoCompression) {
			selected_data = raw.data();
			selected_size = raw.size();
		} else {
			CompressUsingZlib(raw, compressed_data, 9);
			const auto selected_pair = SelectSmaller(compressed_data, raw);
			selected_data = selected_pair.first;
			selected_size = selected_pair.second;
		}
		h
		.Write(selected_data, selected_size) // time data
		.WriteUInt(raw.size()) // uncompressed len
		.WriteUInt(selected_size) // compressed len
		.WriteUInt(uint64_t(vcd.timestamps.size())); // count
	}

	// 6. Patch Block Length and Memory Required
	streamoff end_pos;
	h
	.BeginOffset(end_pos)
	// Patch Block Length (after 1 byte Type)
	.Seek(start_pos + streamoff(1), ios_base::beg)
	.WriteUInt<uint64_t>(end_pos - start_pos - 1)
	// Patch Memory Required
	.Seek(memory_usage_pos, ios_base::beg)
	.WriteUInt<uint64_t>(memory_usage)
	// Restore position to end
	.Seek(end_pos, ios_base::beg);
}

namespace { // Helper functions for CreateEnumTable

void AppendEscToString(const string_view_ in, string& out) {
	for (char c : in) {
		switch (c) {
		case '\a': { out += "\\a"; break; }
		case '\b': { out += "\\b"; break; }
		case '\f': { out += "\\f"; break; }
		case '\n': { out += "\\n"; break; }
		case '\r': { out += "\\r"; break; }
		case '\t': { out += "\\t"; break; }
		case '\v': { out += "\\v"; break; }
		case '\'': { out += "\\'"; break; }
		case '\"': { out += "\\\""; break; }
		case '\\': { out += "\\\\"; break; }
		case '?': { out += "\\?"; break; }
		default: {
			if (c > ' ' && c <= '~') {
				out += c;
			} else {
				unsigned char val = static_cast<unsigned char>(c);
				out += '\\';
				out += (val / 64) + '0';
				val &= 63;
				out += (val / 8) + '0';
				val &= 7;
				out += val + '0';
			}
			break;
		}}
	}
}

} // namespace

void Writer::SetAttrBegin(
	Hierarchy::AttrType attrtype, Hierarchy::AttrSubType subtype,
	const string_view_ attrname, uint64_t arg
) {
	CHECK(not hierarchy_finalized_);

	StreamWriteHelper h(hierarchy_buffer_);

	if (attrtype > Hierarchy::AttrType::eMax) {
		attrtype = Hierarchy::AttrType::eMisc;
		subtype = Hierarchy::AttrSubType::eMisc_Unknown;
	}

	switch (attrtype) {
	case Hierarchy::AttrType::eArray:
		if (subtype < Hierarchy::AttrSubType::eArray_None ||
			subtype > Hierarchy::AttrSubType::eArray_Sparse) {
			subtype = Hierarchy::AttrSubType::eArray_None;
		}
		break;
	case Hierarchy::AttrType::eEnum:
		if (subtype < Hierarchy::AttrSubType::eEnum_SvInteger ||
			subtype > Hierarchy::AttrSubType::eEnum_Time) {
			subtype = Hierarchy::AttrSubType::eEnum_SvInteger;
		}
		break;
	case Hierarchy::AttrType::ePack:
		if (subtype < Hierarchy::AttrSubType::ePack_None ||
			subtype > Hierarchy::AttrSubType::ePack_Sparse) {
			subtype = Hierarchy::AttrSubType::ePack_None;
		}
		break;
	case Hierarchy::AttrType::eMisc:
	default:
		break;
	}

	h
	.WriteUInt(static_cast<uint8_t>(Hierarchy::ScopeControlType::eGenAttrBegin))
	.WriteUInt(static_cast<uint8_t>(attrtype))
	.WriteUInt(static_cast<uint8_t>(subtype))
	.WriteString0(attrname)
	.WriteLEB128(arg);
}

namespace {

// overload for string += string_view_
// Remove this once C++17 is required
string& operator+=(string& lhs, const string_view_ rhs) {
	lhs.append(rhs.data(), rhs.size());
	return lhs;
}

} // namespace

EnumHandle Writer::CreateEnumTable(
	const string_view_ name,
	uint32_t min_valbits,
	const vector<pair<string_view_, string_view_>>& literal_val_arr
) {
	EnumHandle handle = 0;

	if (name.empty() or literal_val_arr.empty()) {
		return handle;
	}

	string attr_str;
	attr_str.reserve(256);
	attr_str += name;
	attr_str += ' ';
	attr_str += to_string(literal_val_arr.size());
	attr_str += ' ';

	for (const auto& p : literal_val_arr) {
		const auto& literal = p.first;
		// literal
		AppendEscToString(literal, attr_str);
		attr_str += ' ';
	}
	for (const auto& p : literal_val_arr) {
		const auto& val = p.second;
		// val (with padding)
		if (min_valbits > 0 and val.size() < min_valbits) {
			attr_str.insert(attr_str.end(), min_valbits - val.size(), '0');
		}
		AppendEscToString(val, attr_str);
		attr_str += ' ';
	}
	attr_str.pop_back(); // remove last space

	handle = ++enum_count_;
	SetAttrBegin(
		Hierarchy::AttrType::eMisc,
		Hierarchy::AttrSubType::eMisc_EnumTable,
		attr_str,
		handle
	);

	return handle;
}

} // namespace fst
