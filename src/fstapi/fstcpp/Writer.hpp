#pragma once
// direct include
#include "fstcpp/fst.hpp"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
// Other libraries' .h files.
// Your project's .h files.
#include "fstcpp/assertion.h"

namespace fst {

class Writer;

namespace detail {

[[nodiscard]]
static inline constexpr std::string_view SafeStringView(const char* str) noexcept {
	return str ? std::string_view(str) : std::string_view{};
}

// We define WriterWaveData here for better code inlining, no forward declaration
struct BlackoutData {
	std::ostringstream buffer;
	uint64_t previous_timestamp = 0;
	uint64_t count = 0;

	void EmitDumpActive(uint64_t current_timestamp, bool enable);
};

// We define ValueChangeData here for better code inlining, no forward declaration
struct ValueChangeData {
	struct VariableInfoBase;
	std::vector<std::unique_ptr<VariableInfoBase>> variable_infos;
	std::vector<uint64_t> timestamps;

	ValueChangeData();
	~ValueChangeData();

	uint64_t current_timestamp() const {
		return timestamps.empty() ? 0 : timestamps.back();
	}
	uint64_t first_timestamp = 0;

	void WriteInitialBits(std::ostream &os) const;
	std::vector<std::vector<char>> ComputeWaveData() const;
	static std::vector<int64_t> UniquifyWaveData(
		std::vector<std::vector<char>> &data
	);
	static uint64_t EncodePositionsAndWriteUniqueWaveData(
		std::ostream &os,
		const std::vector<std::vector<char>> &unique_data,
		std::vector<int64_t> &positions
	);
	static void WriteEncodedPositions(
		const std::vector<int64_t> &encoded_positions,
		std::ostream &os
	);
	void WriteTimestamps(std::ostream &os) const;
};

} // namespace detail

class Writer {
	friend class WriterTest;
public:
	Writer() {}
	Writer(const std::string_view name) { if (not name.empty()) Open(name); }
	~Writer() { Close(); }

	Writer(const Writer&) = delete;
	Writer(Writer&&) = delete;
	Writer& operator=(const Writer&) = delete;
	Writer& operator=(Writer&&) = delete;

	// File control
	void Open(const std::string_view name);
	void Close();

	//////////////////////////////
	// Header manipulation API
	//////////////////////////////
	const Header& GetHeader() const;
	void SetTimecale(int8_t timescale) { header_.timescale = timescale; }
	void SetWriter(const std::string_view writer) {
		const auto len = std::min(writer.size(), sizeof(header_.writer));
		std::copy_n(writer.data(), len, header_.writer);
		if (len != sizeof(header_.writer)) {
			header_.writer[len] = '\0';
		}
	}
	void SetDate(const std::string_view date_str) {
		const auto len = date_str.size();
		CHECK_EQ(len, sizeof(header_.date)-1);
		std::copy_n(date_str.data(), len, header_.date);
		header_.date[len] = '\0';
	}
	void SetTimezero(int64_t timezero) { header_.timezero = timezero; }

	//////////////////////////////
	// Change scope API
	//////////////////////////////
	void SetScope(Hierarchy::ScopeType scopetype, const std::string_view scopename, const std::string_view scopecomp);
	void Upscope();

	//////////////////////////////
	// Attribute / Misc API
	//////////////////////////////
	void SetAttrBegin(
		Hierarchy::AttrType attrtype, Hierarchy::AttrSubType subtype,
		const std::string_view attrname, uint64_t arg
	);
	inline void SetAttrEnd() {
		hierarchy_buffer_.put(static_cast<char>(Hierarchy::ScopeControlType::eGenAttrEnd));
	}
	EnumHandle CreateEnumTable(
		const std::string_view name,
		uint32_t min_valbits,
		const std::vector<std::pair<std::string_view, std::string_view>>& literal_val_arr
	);
	inline void EmitEnumTableRef(EnumHandle handle) {
		SetAttrBegin(Hierarchy::AttrType::eMisc, Hierarchy::AttrSubType::eMisc_EnumTable, std::string_view{}, handle);
	}
	inline void SetWriterPackType(WriterPackType pack_type) {
		CHECK_NE(pack_type_, WriterPackType::eZlib);
		CHECK_NE(pack_type_, WriterPackType::eFastLz);
		pack_type_ = pack_type;
	}

	//////////////////////////////
	// Create variable API
	//////////////////////////////
	Handle CreateVar(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const std::string_view name,
		uint32_t alias_handle
	);
	Handle CreateVar2(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const std::string_view name, uint32_t alias_handle, const std::string_view type,
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
	Writer(const std::string& name) : Writer(std::string_view(name)) {}
	// Open
	inline void Open(const std::string& name) { Open(std::string_view(name)); }
	// SetWriter
	inline void SetWriter(const char* writer) { if (writer) SetWriter(std::string_view(writer)); }
	inline void SetWriter(const std::string& writer) { SetWriter(std::string_view(writer)); }
	// SetDate
	inline void SetDate(const char* date_str) { if (date_str) SetDate(std::string_view(date_str)); }
	inline void SetDate(const std::string& date_str) { SetDate(std::string_view(date_str)); }
	inline void SetDate(const std::tm* d) { SetDate(std::string_view(std::asctime(d))); }
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
		CHECK_NE(name, nullptr);
		return CreateVar(vartype, vardir, bitwidth, std::string_view(name), alias_handle);
	}
	inline Handle CreateVar(
		Hierarchy::VarType vartype, Hierarchy::VarDirection vardir,
		uint32_t bitwidth, const std::string& name,
		uint32_t alias_handle
	) { return CreateVar(vartype, vardir, bitwidth, std::string_view(name), alias_handle); }
	// SetScope
	inline void SetScope(Hierarchy::ScopeType scopetype, const std::string& scopename, const std::string& scopecomp) {
		SetScope(scopetype, std::string_view(scopename), std::string_view(scopecomp));
	}
	inline void SetScope(Hierarchy::ScopeType scopetype, const char* scopename, const char* scopecomp) {
		SetScope(scopetype, detail::SafeStringView(scopename), detail::SafeStringView(scopecomp));
	}
private:
	// File/memory buffers
	// 1. For hierarchy and geometry, we do not keep the data structure, instead we just
	//    serialize them into buffers, and compress+write them at the end of file.
	// 2. For header, we keep the data structure in memory since it is quite small
	// 3. For wave data, we keep a complicated data structure in memory, and flush them to file when necessary
	std::ofstream main_fst_file_;
	std::ostringstream hierarchy_buffer_;
	std::ostringstream geometry_buffer_;
	Header header_{};
	detail::BlackoutData blackout_data_;
	detail::ValueChangeData value_change_data_;
	bool hierarchy_finalized_ = false;
	enum WriterPackType pack_type_ = WriterPackType::eLz4;
	uint32_t enum_count_ = 0;

	// internal helpers
	static void WriteHeader_(const Header &header, std::ostream &os);
	void AppendGeometry_(std::ostream &os);
	void AppendHierarchy_(std::ostream &os);
	void AppendBlackout_(std::ostream &os);
	static void FlushValueChangeData_(
		const detail::ValueChangeData &vcd,
		std::ostream &os
	);
	void FinalizeHierarchy_() { hierarchy_finalized_ = true; }
	template <typename... T>
	void EmitValueChangeHelper_(Handle handle, T&&... val);
};

} // namespace fst
