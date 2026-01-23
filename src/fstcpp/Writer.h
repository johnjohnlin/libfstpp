// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once
// direct include
#include "fstcpp/fst.h"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
// Other libraries' .h files.
// Your project's .h files.
#include "fstcpp/assertion.h"
#include "fstcpp/fst_string_view.h"
#include "fstcpp/VariableInfo.h"

namespace fst {

class Writer;

namespace detail {

[[nodiscard]]
static inline constexpr string_view_ SafeStringView(const char* str) noexcept {
	return str ? string_view_(str) : string_view_{};
}

// We define WriterWaveData here for better code inlining, no forward declaration
struct BlackoutData {
	std::vector<uint8_t> buffer;
	uint64_t previous_timestamp = 0;
	uint64_t count = 0;

	void EmitDumpActive(uint64_t current_timestamp, bool enable);
};

// We define ValueChangeData here for better code inlining, no forward declaration
struct ValueChangeData {
	std::vector<VariableInfo> variable_infos;
	std::vector<uint64_t> timestamps;

	ValueChangeData();
	~ValueChangeData();

	void WriteInitialBits(std::vector<uint8_t> &os) const;
	std::vector<std::vector<uint8_t>> ComputeWaveData() const;
	static std::vector<int64_t> UniquifyWaveData(
		std::vector<std::vector<uint8_t>> &data
	);
	static uint64_t EncodePositionsAndWriteUniqueWaveData(
		std::ostream &os,
		const std::vector<std::vector<uint8_t>> &unique_data,
		std::vector<int64_t> &positions,
		WriterPackType pack_type
	);
	static void WriteEncodedPositions(
		const std::vector<int64_t> &encoded_positions,
		std::ostream &os
	);
	void WriteTimestamps(std::vector<uint8_t> &os) const;
	void KeepOnlyTheLatestValue();
};

} // namespace detail

class Writer {
	friend class WriterTest;
public:
	Writer() {}
	Writer(const string_view_ name) { if (not name.empty()) Open(name); }
	~Writer() { Close(); }

	Writer(const Writer&) = delete;
	Writer(Writer&&) = delete;
	Writer& operator=(const Writer&) = delete;
	Writer& operator=(Writer&&) = delete;

	// File control
	void Open(const string_view_ name);
	void Close();

	//////////////////////////////
	// Header manipulation API
	//////////////////////////////
	const Header& GetHeader() const;
	void SetTimecale(int8_t timescale) { header_.timescale = timescale; }
	void SetWriter(const string_view_ writer) {
		const auto len = std::min(writer.size(), sizeof(header_.writer));
		std::copy_n(writer.data(), len, header_.writer);
		if (len != sizeof(header_.writer)) {
			header_.writer[len] = '\0';
		}
	}
	void SetDate(const string_view_ date_str) {
		const auto len = date_str.size();
		CHECK_EQ(len, sizeof(header_.date)-1);
		std::copy_n(date_str.data(), len, header_.date);
		header_.date[len] = '\0';
	}
	void SetTimezero(int64_t timezero) { header_.timezero = timezero; }

	//////////////////////////////
	// Change scope API
	//////////////////////////////
	void SetScope(Hierarchy::ScopeType scopetype, const string_view_ scopename, const string_view_ scopecomp);
	void Upscope();

	//////////////////////////////
	// Attribute / Misc API
	//////////////////////////////
	void SetAttrBegin(
		Hierarchy::AttrType attrtype, Hierarchy::AttrSubType subtype,
		const string_view_ attrname, uint64_t arg
	);
	inline void SetAttrEnd() {
		hierarchy_buffer_.push_back(static_cast<uint8_t>(Hierarchy::ScopeControlType::eGenAttrEnd));
	}
	EnumHandle CreateEnumTable(
		const string_view_ name,
		uint32_t min_valbits,
		const std::vector<std::pair<string_view_, string_view_>>& literal_val_arr
	);
	inline void EmitEnumTableRef(EnumHandle handle) {
		SetAttrBegin(Hierarchy::AttrType::eMisc, Hierarchy::AttrSubType::eMisc_EnumTable, string_view_{}, handle);
	}
	inline void SetWriterPackType(WriterPackType pack_type) {
		CHECK(
			pack_type != WriterPackType::eZlib and
			pack_type != WriterPackType::eFastLz
		);
		pack_type_ = pack_type;
	}

	//////////////////////////////
	// Create variable API
	//////////////////////////////
	Handle CreateVar(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const string_view_ name,
		uint32_t alias_handle
	);
	Handle CreateVar2(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const string_view_ name, uint32_t alias_handle, const string_view_ type,
		Hierarchy::SupplementalVarType svt, Hierarchy::SupplementalDataType sdt
	);

	//////////////////////////////
	// Waveform API
	//////////////////////////////
	void EmitTimeChange(uint64_t tim);
	void EmitDumpActive(bool enable);
	void EmitValueChange(Handle handle, const uint32_t *val, EncodingType encoding = EncodingType::eBinary);
	void EmitValueChange(Handle handle, const uint64_t *val, EncodingType encoding = EncodingType::eBinary);
	// Pass by value for small integers
	void EmitValueChange(Handle handle, uint64_t val);
	// Add support for C-string value changes (e.g. fst string values)
	void EmitValueChange(Handle handle, const char *val);

	//////////////////////////////
	// Alias version
	//////////////////////////////
	// Constructor
	Writer(const char* name) : Writer(detail::SafeStringView(name)) {}
	Writer(const std::string& name) : Writer(string_view_(name)) {}
	// Open
	inline void Open(const std::string& name) { Open(string_view_(name)); }
	// SetWriter
	inline void SetWriter(const char* writer) { if (writer) SetWriter(string_view_(writer)); }
	inline void SetWriter(const std::string& writer) { SetWriter(string_view_(writer)); }
	// SetDate
	inline void SetDate(const char* date_str) { if (date_str) SetDate(string_view_(date_str)); }
	inline void SetDate(const std::string& date_str) { SetDate(string_view_(date_str)); }
	inline void SetDate(const std::tm* d) { SetDate(string_view_(std::asctime(d))); }
	inline void SetDate() {
		// set date to now
		std::time_t t = std::time(nullptr);
		SetDate(std::localtime(&t));
	}
	// CreateVar(2)
	inline Handle CreateVar(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const char* name,
		uint32_t alias_handle
	) {
		CHECK_NE(name, static_cast<void*>(nullptr));
		return CreateVar(vartype, vardir, bitwidth, string_view_(name), alias_handle);
	}
	inline Handle CreateVar(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const std::string& name,
		uint32_t alias_handle
	) { return CreateVar(vartype, vardir, bitwidth, string_view_(name), alias_handle); }
	// SetScope
	inline void SetScope(Hierarchy::ScopeType scopetype, const std::string& scopename, const std::string& scopecomp) {
		SetScope(scopetype, string_view_(scopename), string_view_(scopecomp));
	}
	inline void SetScope(Hierarchy::ScopeType scopetype, const char* scopename, const char* scopecomp) {
		SetScope(scopetype, detail::SafeStringView(scopename), detail::SafeStringView(scopecomp));
	}
	// Flush value change data
	inline void FlushValueChangeData() {
		flush_pending_ = true;
	}
private:
	// File/memory buffers
	// 1. For hierarchy and geometry, we do not keep the data structure, instead we just
	//    serialize them into buffers, and compress+write them at the end of file.
	// 2. For header, we keep the data structure in memory since it is quite small
	// 3. For wave data, we keep a complicated data structure in memory, and flush them to file when necessary
	std::ofstream main_fst_file_;
	std::vector<uint8_t> hierarchy_buffer_;
	std::vector<uint8_t> geometry_buffer_;
	Header header_{};
	detail::BlackoutData blackout_data_;
	detail::ValueChangeData value_change_data_;
	bool hierarchy_finalized_ = false;
	WriterPackType pack_type_ = WriterPackType::eLz4;
	uint64_t value_change_data_usage_ = 0; // Note: this value is just an estimation
	uint64_t value_change_data_flush_threshold_ = 128<<20; // 128MB
	uint32_t enum_count_ = 0;
	bool flush_pending_ = false;

	// internal helpers
	static void WriteHeader_(const Header &header, std::ostream &os);
	void AppendGeometry_(std::ostream &os);
	void AppendHierarchy_(std::ostream &os);
	void AppendBlackout_(std::ostream &os);
	// This function is used to flush value change data to file, and keep only the latest value in memory
	// Just want to separate the const part from the non-const part for code clarity
	static void FlushValueChangeDataConstPart_(
		const detail::ValueChangeData &vcd,
		std::ostream &os,
		WriterPackType pack_type
	);
	inline void FlushValueChangeData_(
		detail::ValueChangeData &vcd,
		std::ostream &os
	) {
		if (vcd.timestamps.empty()) {
			return;
		}
		FlushValueChangeDataConstPart_(vcd, os, pack_type_);
		vcd.KeepOnlyTheLatestValue();
		++header_.num_value_change_data_blocks;
		value_change_data_usage_ = 0;
		flush_pending_ = false;
	}
	void FinalizeHierarchy_() {
		if (hierarchy_finalized_) return;
		hierarchy_finalized_ = true;
		// Original FST code comments: as a default, use 128MB and increment when
		// every 1M signals are defined.
		value_change_data_flush_threshold_ = (((header_.num_handles-1) >> 20) + 1) << 27;
	}
	template <typename... T>
	void EmitValueChangeHelper_(Handle handle, T&&... val);
};

} // namespace fst
