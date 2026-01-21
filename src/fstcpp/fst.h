// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once
// direct include
// C system headers
// C++ standard library headers
#include <cstdint>
// Other libraries' .h files.
// Your project's .h files.

// Remove these when we upgrade to C++20
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wc++17-attribute-extensions"
#pragma GCC diagnostic ignored "-Wc++20-attribute-extensions"

namespace fst {

typedef uint32_t Handle;
typedef uint32_t EnumHandle;

enum class WriterPackType : uint8_t {
	eZlib = 0, // not supported
	eFastLz = 1, // not supported
	eLz4 = 2,
	// usually for testing, you should use eLz4
	// This will turn off compression for geometry/hierarchy/wave data
	eNoCompression = 3,
};

enum class FileType : uint8_t {
	eVerilog = 0,
	eVhdl,
	eVerilogVhdl,
};

enum class EncodingType : uint8_t {
	eBinary = 0, // 1 bit per bit to represent 0,1
	eVerilog = 1, // 2 bits per bit to represent X,Z
	eVhdl = 2, // 4 bits per bit to represent H,U,W,L,-,?
};
[[maybe_unused]]
static inline constexpr unsigned BitPerEncodedBit(EncodingType type) {
	return 1 << static_cast<uint8_t>(type);
}
[[maybe_unused]] static const char* kEncodedBitToCharTable = "01xzhuwl";

struct Hierarchy {
	enum ScopeType : uint8_t {
		eVcdModule = 0,
		eVcdTask = 1,
		eVcdFunction = 2,
		eVcdBegin = 3,
		eVcdFork = 4,
		eVcdGenerate = 5,
		eVcdStruct = 6,
		eVcdUnion = 7,
		eVcdClass = 8,
		eVcdInterface = 9,
		eVcdPackage = 10,
		eVcdprogram = 11,
		eVhdlArchitecture = 12,
		eVhdlProcedure = 13,
		eVhdlFunction = 14,
		eVhdlRecord = 15,
		eVhdlProcess = 16,
		eVhdlBlock = 17,
		eVhdlForGenerate = 18,
		eVhdlIfGenerate = 19,
		eVhdlGenerate = 20,
		eVhdlPackage = 21,
	};

	enum ScopeControlType : uint8_t {
		eGenAttrBegin = 252,
		eGenAttrEnd = 253,
		eVcdScope = 254,
		eVcdUpscope = 255,
	};

	enum VarType : uint8_t {
		eVcdEvent = 0,
		eVcdInteger = 1,
		eVcdParameter = 2,
		eVcdReal = 3,
		eVcdReal_parameter = 4,
		eVcdReg = 5,
		eVcdSupply0 = 6,
		eVcdSupply1 = 7,
		eVcdTime = 8,
		eVcdTri = 9,
		eVcdTriand = 10,
		eVcdTrior = 11,
		eVcdTrireg = 12,
		eVcdTri0 = 13,
		eVcdTri1 = 14,
		eVcdWand = 15,
		eVcdWire = 16,
		eVcdWor = 17,
		eVcdPort = 18,
		eVcdSparray = 19,
		eVcdRealtime = 20,
		eGenString = 21,
		eSvBit = 22,
		eSvLogic = 23,
		eSvInt = 24,
		eSvShortint = 25,
		eSvLongint = 26,
		eSvByte = 27,
		eSvEnum = 28,
		eSvShortreal = 29,
	};

	enum VarDirection : uint8_t {
		eMin = 0,

		eImplicit = 0,
		eInput = 1,
		eOutput = 2,
		eInout = 3,
		eBuffer = 4,
		eLinkage = 5,

		eMax = 5,
	};

	enum class AttrType : uint8_t {
		eMin = 0,
		eMisc = 0,
		eArray = 1,
		eEnum = 2,
		ePack = 3,
		eMax = 3,
	};

	enum class AttrSubType : uint8_t {
		// For AttrType::eMisc
		eMisc_Min = 0,
		eMisc_Comment = 0,
		eMisc_EnvVar = 1,
		eMisc_SupVar = 2,
		eMisc_PathName = 3,
		eMisc_SourceStem = 4,
		eMisc_SourceIStem = 5,
		eMisc_ValueList = 6,
		eMisc_EnumTable = 7,
		eMisc_Unknown = 8,
		eMisc_Max = 8,

		// For AttrType::eArray
		eArray_Min = 0,
		eArray_None = 0,
		eArray_Unpacked = 1,
		eArray_Packed = 2,
		eArray_Sparse = 3,
		eArray_Max = 3,

		// For AttrType::eEnum
		eEnum_Min = 0,
		eEnum_SvInteger = 0,
		eEnum_SvBit = 1,
		eEnum_SvLogic = 2,
		eEnum_SvInt = 3,
		eEnum_SvShortint = 4,
		eEnum_SvLongint = 5,
		eEnum_SvByte = 6,
		eEnum_SvUnsignedInteger = 7,
		eEnum_SvUnsignedBit = 8,
		eEnum_SvUnsignedLogic = 9,
		eEnum_SvUnsignedInt = 10,
		eEnum_SvUnsignedShortint = 11,
		eEnum_SvUnsignedLongint = 12,
		eEnum_SvUnsignedByte = 13,
		eEnum_Reg = 14,
		eEnum_Time = 15,
		eEnum_Max = 15,

		// For AttrType::ePack
		ePack_Min = 0,
		ePack_None = 0,
		ePack_Unpacked = 1,
		ePack_Packed = 2,
		ePack_Sparse = 3,
		ePack_Max = 3,
	};

	enum SupplementalVarType : uint8_t {
	};

	enum SupplementalDataType : uint8_t {
	};
};

struct Header {
	uint64_t start_time = uint64_t(-1);
	uint64_t end_time = 0;
	int64_t timezero = 0;
	uint64_t writer_memory_use = 1ull << 27; // Match the original fstapi.c. Just for information, not used in FST.
	uint64_t num_scopes = 0;
	uint64_t num_vars = 0; // #CreateVar calls, including aliases
	uint64_t num_handles = 0; // #unique handles, excluding aliases, shall be <= num_vars
	uint64_t num_value_change_data_blocks = 1;
	char writer[128] {};
	char date[26] {};
	FileType filetype = FileType::eVerilog;
	int8_t timescale = -9;
};

static constexpr uint64_t kInvalidTime = uint64_t(-1);

} // namespace fst
