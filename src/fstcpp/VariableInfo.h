// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once
// direct include
#include "fstcpp/fst.hpp"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
// Other libraries' .h files.
// Your project's .h files.
#include "fstcpp/assertion.h"
#include "fstcpp/StreamWriteHelper.hpp"

namespace fst {

// This file is a header-only library to maximize the performance of EmitValueChange.

struct VariableInfoBase {
	const uint32_t bitwidth : 31;
	const bool is_real : 1;
	struct ChangeEntry {
		// Common change info that all children share
		// TODO: consider using union or bit-field if size is a concern
		uint64_t time_index;
		EncodingType encoding;
	};
	std::vector<ChangeEntry> change_entries;
	static VariableInfoBase* Create(uint32_t bitwidth, bool is_real);

	VariableInfoBase(uint32_t bitwidth_, bool is_real_ = false) : bitwidth(bitwidth_), is_real(is_real_) {
		change_entries.reserve(32);
		// keep initial time_index = 0; default encoding to eBinary (children may overwrite)
		change_entries.push_back({kInvalidTime, EncodingType::eBinary});
	}

	unsigned num_words() const { return (bitwidth + 63) / 64; }

	// If child classes do not override this function, it will throw an exception when called.
	// They are not virtual since EmitValueChange is very hot code and is small.
	// We want to avoid the virtual function call overhead.
	// LCOV_EXCL_START
	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t val) {
		(void)current_time_index; (void)val;
		std::string error_msg = "EmitValueChange(uint64_t) not supported for ";
		error_msg += typeid(*this).name();
		throw std::runtime_error(error_msg);
	}
	uint64_t EmitValueChange(uint64_t current_time_index, const uint32_t *val, EncodingType encoding) {
		(void)current_time_index; (void)val; (void)encoding;
		std::string error_msg = "EmitValueChange(uint32_t*) not supported for ";
		error_msg += typeid(*this).name();
		throw std::runtime_error(error_msg);
	}
	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t *val, EncodingType encoding) {
		(void)current_time_index; (void)val; (void)encoding;
		std::string error_msg = "EmitValueChange(uint64_t*) not supported for ";
		error_msg += typeid(*this).name();
		throw std::runtime_error(error_msg);
	}
	// LCOV_EXCL_STOP

	virtual void KeepOnlyTheLatestValue() = 0;
	virtual void DumpInitialBits(std::ostream &os) const = 0;
	virtual void DumpValueChanges(std::ostream &os) const = 0;
	virtual ~VariableInfoBase() = default;
};

class VariableInfoDouble : public VariableInfoBase {
	std::vector<double> value_changes; // Only support EncodingType::eBinary

	inline uint64_t ComputeEmitMemory(EncodingType encoding) {
		return sizeof(double) * static_cast<unsigned>(encoding);
	}

public:
	using VariableInfoBase::EmitValueChange;
	VariableInfoDouble() : VariableInfoBase(8, true) {
		value_changes.reserve(32);
		value_changes.push_back(0.0);
	}

	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t val) {
		if (current_time_index + 1 == 0) {
			// This is the first value change, we need to remove everything
			// and then add the new value
			change_entries.resize(0);
			value_changes.resize(0);
		}
		change_entries.push_back({current_time_index, EncodingType::eBinary});
		double dst;
		std::memcpy(&dst, &val, sizeof(double));
		value_changes.push_back(dst);
		return ComputeEmitMemory(EncodingType::eBinary);
	}

	void KeepOnlyTheLatestValue() override {
		change_entries.front().encoding = change_entries.back().encoding;
		change_entries.resize(1);
		value_changes.front() = value_changes.back();
		value_changes.resize(1);
	}

	void DumpInitialBits(std::ostream &os) const override {
		// FST requires initial bits present
		DCHECK(not change_entries.empty());
		// Reals: store native-endian f64 (8 bytes)
		double v = 0.0;
		if (!value_changes.empty()) v = value_changes.front();
		os.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	// LCOV_EXCL_START
	void DumpValueChanges(std::ostream &os) const override {
		(void)os;
		throw std::runtime_error("TODO: DumpValueChanges not implemented for VariableInfoDouble");
	}
	// LCOV_EXCL_STOP
};

template<typename T>
class VariableInfoScalarInt : public VariableInfoBase {
	std::vector<T> value_changes;

public:
	VariableInfoScalarInt(uint32_t bitwidth_) : VariableInfoBase(bitwidth_) {
		value_changes.reserve(32);
		// This is required by FST, we must have at least one entry
		// This encodes X
		value_changes.push_back(0);
		value_changes.push_back(T(-1));
		// override the encoding to Verilog (which is set to eBinary in parent constructor)
		change_entries[0].encoding = EncodingType::eVerilog;
	}

private:
	inline void EmitValueChangeCommonPart(uint64_t current_time_index, EncodingType encoding) {
		if (current_time_index+1 == 0) {
			// This is the first value change, we need to remove everything
			// and then add the new value
			change_entries.resize(0);
			value_changes.resize(0);
		}
		change_entries.push_back({current_time_index, encoding});
	}

	inline uint64_t ComputeEmitMemory(EncodingType encoding) {
		return sizeof(T) * static_cast<unsigned>(encoding);
	}

public:
	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t val) {
		EmitValueChangeCommonPart(current_time_index, EncodingType::eBinary);
		value_changes.push_back(val);
		return ComputeEmitMemory(EncodingType::eBinary);
	}

	uint64_t EmitValueChange(uint64_t current_time_index, const uint32_t* val, EncodingType encoding) {
		EmitValueChangeCommonPart(current_time_index, encoding);
		for (unsigned i = 0; i < static_cast<unsigned>(encoding); ++i) {
			// C++17: replace this with if constexpr
			if (sizeof(T) == 8) {
				uint64_t v = val[1]; // high bits
				v <<= 32;
				v |= val[0]; // low bits
				value_changes.push_back(v);
				val += 2;
			} else {
				value_changes.push_back(val[0]);
				val += 1;
			}
		}
		return ComputeEmitMemory(encoding);
	}

	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t* val, EncodingType encoding) {
		EmitValueChangeCommonPart(current_time_index, encoding);
		for (unsigned i = 0; i < static_cast<unsigned>(encoding); ++i) {
			value_changes.push_back(val[i]);
		}
		return ComputeEmitMemory(encoding);
	}

	void KeepOnlyTheLatestValue() override {
		change_entries.front().encoding = change_entries.back().encoding;
		change_entries.resize(1);
		const unsigned remaining = static_cast<unsigned>(change_entries.front().encoding);
		std::copy_n(
			value_changes.end() - remaining,
			remaining,
			value_changes.begin()
		);
		value_changes.resize(remaining);
	}

	void DumpInitialBits(std::ostream &os) const override {
		// FST requires initial bits present
		DCHECK(not change_entries.empty() and not value_changes.empty());
		const auto enc = change_entries.front().encoding;

		switch (enc) {
		case EncodingType::eBinary: {
			for (unsigned i = bitwidth; i-- > 0;) {
				const char c = ((value_changes[0] >> i) & T(1)) ? '1' : '0';
				os.put(c);
			}
			break;
		}

		case EncodingType::eVerilog: {
			for (unsigned i = bitwidth; i-- > 0;) {
				const T b1 = ((value_changes[1] >> i) & T(1));
				const T b0 = ((value_changes[0] >> i) & T(1));
				const char c = kEncodedBitToCharTable[(b1 << 1) | b0];
				os.put(c);
			}
			break;
		}
		// Not supporting VHDL now
		// LCOV_EXCL_START
		default:
		case EncodingType::eVhdl: {
			for (unsigned i = bitwidth; i-- > 0;) {
				const T b2 = ((value_changes[2] >> i) & T(1));
				const T b1 = ((value_changes[1] >> i) & T(1));
				const T b0 = ((value_changes[0] >> i) & T(1));
				const char c = kEncodedBitToCharTable[(b2 << 2) | (b1 << 1) | b0];
				os.put(c);
			}
			break;
		}}
		// LCOV_EXCL_STOP
	}

	void DumpValueChanges(std::ostream &os) const override {
		// Note: [0] is initial value, which is already dumped in DumpInitialBits()
		StreamWriteHelper h(os);
		if (bitwidth == 1) {
			const T* value_ptr = value_changes.data();
			value_ptr += static_cast<unsigned>(change_entries[0].encoding);
			uint64_t prev_time_index = 0;
			for (size_t i = 1; i < change_entries.size(); ++i) {
				unsigned val = 0;
				switch (change_entries[i].encoding) {
				// Not supporting VHDL now
				// LCOV_EXCL_START
				case EncodingType::eVhdl:
					val |= value_ptr[2];
					[[fallthrough]];
				case EncodingType::eVerilog:
					val |= value_ptr[1];
					[[fallthrough]];
				// LCOV_EXCL_STOP
				default:
				case EncodingType::eBinary:
					val |= value_ptr[0];
				}

				uint64_t delta_time_index = change_entries[i].time_index - prev_time_index;
				prev_time_index = change_entries[i].time_index;
				switch (val) {
				case 0: delta_time_index = (delta_time_index<<2) | (0<<1) | 0; break; // '0'
				case 1: delta_time_index = (delta_time_index<<2) | (1<<1) | 0; break; // '1'
				case 2: delta_time_index = (delta_time_index<<4) | (0<<1) | 1; break; // 'X'
				case 3: delta_time_index = (delta_time_index<<4) | (1<<1) | 1; break; // 'Z'
				// Not supporting VHDL now
				// LCOV_EXCL_START
				case 4: delta_time_index = (delta_time_index<<4) | (2<<1) | 1; break; // 'H'
				case 5: delta_time_index = (delta_time_index<<4) | (3<<1) | 1; break; // 'U'
				case 6: delta_time_index = (delta_time_index<<4) | (4<<1) | 1; break; // 'W'
				case 7: delta_time_index = (delta_time_index<<4) | (5<<1) | 1; break; // 'L'
				case 8: delta_time_index = (delta_time_index<<4) | (6<<1) | 1; break; // '-'
				case 9: delta_time_index = (delta_time_index<<4) | (7<<1) | 1; break; // '?'
				default: break;
				// LCOV_EXCL_STOP
				}
				h.WriteLEB128(delta_time_index);
				value_ptr += static_cast<unsigned>(change_entries[i].encoding);
			}
		} else {
			const T* value_ptr = value_changes.data();
			value_ptr += static_cast<unsigned>(change_entries[0].encoding);
			uint64_t prev_time_index = 0;
			for (size_t i = 1; i < change_entries.size(); ++i) {
				CHECK(change_entries[i].encoding == EncodingType::eBinary); // TODO
				const bool has_non_binary = change_entries[i].encoding != EncodingType::eBinary;
				const uint64_t delta_time_index = change_entries[i].time_index - prev_time_index;
				prev_time_index = change_entries[i].time_index;
				h
				.WriteLEB128((delta_time_index << 1) | has_non_binary)
				.WriteUIntPartialForValueChange(value_ptr[0], bitwidth);
				value_ptr += static_cast<unsigned>(change_entries[i].encoding);
			}
		}
	}
};

class VariableInfoLongInt : public VariableInfoBase {
	std::vector<uint64_t> value_changes;

public:
	VariableInfoLongInt(uint32_t bitwidth_) : VariableInfoBase(bitwidth_) {
		value_changes.reserve(32);
		// This is required by FST, we must have at least one entry
		// This encodes X
		value_changes.insert(value_changes.end(), num_words(), 0);
		value_changes.insert(value_changes.end(), num_words(), uint64_t(-1));
		// override the encoding to Verilog (which is set to eBinary in parent constructor)
		change_entries[0].encoding = EncodingType::eVerilog;
	}

private:
	inline void EmitValueChangeCommonPart(uint64_t current_time_index, EncodingType encoding) {
		if (current_time_index+1 == 0) {
			// This is the first value change, we need to remove everything
			// and then add the new value
			change_entries.resize(0);
			value_changes.resize(0);
		}
		change_entries.push_back({current_time_index, encoding});
	}

	inline uint64_t ComputeEmitMemory(EncodingType encoding) {
		return sizeof(uint64_t) * num_words() * static_cast<unsigned>(encoding);
	}

public:
	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t val) {
		EmitValueChangeCommonPart(current_time_index, EncodingType::eBinary);
		value_changes.push_back(val);
		// LongInt requires more numbers of words to represent a full value
		for (unsigned i = 0; i < num_words() - 1; ++i) {
			value_changes.push_back(0);
		}
		return ComputeEmitMemory(EncodingType::eBinary);
	}

	uint64_t EmitValueChange(uint64_t current_time_index, const uint32_t *val, EncodingType encoding) {
		EmitValueChangeCommonPart(current_time_index, encoding);
		// 32 bit is not the native encoding for LongInt
		// value_changes is vector<uint64_t>
		const unsigned nw = (bitwidth + 31) / 32;
		for (unsigned i = 0; i < static_cast<unsigned>(encoding); ++i) {
			for (unsigned j = 0; j < nw/2; ++j) {
				uint64_t v = val[1]; // high bits
				v <<= 32;
				v |= val[0]; // low bits
				value_changes.push_back(v);
				val += 2;
			}
			if (nw % 2 != 0) {
				value_changes.push_back(val[0]);
				val += 1;
			}
		}
		return ComputeEmitMemory(encoding);
	}

	uint64_t EmitValueChange(uint64_t current_time_index, const uint64_t *val, EncodingType encoding) {
		EmitValueChangeCommonPart(current_time_index, encoding);
		const unsigned nw64 = num_words() * static_cast<unsigned>(encoding);
		value_changes.insert(value_changes.end(), val, val + nw64);
		return ComputeEmitMemory(encoding);
	}

	void KeepOnlyTheLatestValue() override {
		change_entries.front().encoding = change_entries.back().encoding;
		change_entries.resize(1);
		const unsigned remaining = num_words() * static_cast<unsigned>(change_entries.front().encoding);
		std::copy_n(
			value_changes.end() - remaining,
			remaining,
			value_changes.begin()
		);
		value_changes.resize(remaining);
	}

	void DumpInitialBits(std::ostream &os) const override {
		// FST requires initial bits present
		DCHECK(not change_entries.empty());

		// - eBinary: value_changes contains num_words() words (LSB-word at index 0)
		// - eVerilog: value_changes contains num_words() * 2 words: [value words][mask words]
		// - eVhdl: value_changes contains num_words() * 3 words: [value words][mask words][vhdl mask words]
		const unsigned nw = num_words();
		const EncodingType enc = change_entries.front().encoding;
		switch (enc) {
		case EncodingType::eBinary: {
			for (unsigned i = bitwidth; i-- > 0;) {
				const unsigned word_index = i / 64;
				const unsigned bit_index  = i % 64;
				const char c = ((value_changes[word_index] >> bit_index) & uint64_t(1)) ? '1' : '0';
				os.put(c);
			}
			break;
		}
		case EncodingType::eVerilog: {
			for (unsigned i = bitwidth; i-- > 0;) {
				const unsigned word_index = i / 64;
				const unsigned bit_index  = i % 64;
				const bool b1 = ((value_changes[nw*1 + word_index] >> bit_index) & uint64_t(1));
				const bool b0 = ((value_changes[nw*0 + word_index] >> bit_index) & uint64_t(1));
				const char c = kEncodedBitToCharTable[(b1 << 1) | b0];
				os.put(c);
			}
			break;
		}
		default:
		case EncodingType::eVhdl: {
			// Not supporting VHDL now
			// LCOV_EXCL_START
			for (unsigned i = bitwidth; i-- > 0;) {
				const unsigned word_index = i / 64;
				const unsigned bit_index  = i % 64;
				const bool b2 = ((value_changes[nw*2 + word_index] >> bit_index) & uint64_t(1));
				const bool b1 = ((value_changes[nw*1 + word_index] >> bit_index) & uint64_t(1));
				const bool b0 = ((value_changes[nw*0 + word_index] >> bit_index) & uint64_t(1));
				const char c = kEncodedBitToCharTable[(b2 << 2) | (b1 << 1) | b0];
				os.put(c);
			}
			break;
			// LCOV_EXCL_STOP
		}}
	}

	void DumpValueChanges(std::ostream &os) const override {
		StreamWriteHelper h(os);
		const unsigned nw = num_words();
		const uint64_t* value_ptr = value_changes.data();
		value_ptr += static_cast<unsigned>(change_entries[0].encoding) * nw;
		uint64_t prev_time_index = 0;
		for (size_t i = 1; i < change_entries.size(); ++i) {
			CHECK(change_entries[i].encoding == EncodingType::eBinary); // TODO
			const bool has_non_binary = change_entries[i].encoding != EncodingType::eBinary;
			const uint64_t delta_time_index = change_entries[i].time_index - prev_time_index;
			prev_time_index = change_entries[i].time_index;
			h
			.WriteLEB128((delta_time_index << 1) | has_non_binary);
			if (bitwidth % 64 != 0) {
				const unsigned remaining = bitwidth % 64;
				// from nw-1 to 1
				for (unsigned j = nw-1; j > 0; --j) {
					h.WriteUInt(
						(value_ptr[j] << (64-remaining)) |
						(value_ptr[j-1] >> remaining)
					);
				}
				// 0
			h.WriteUIntPartialForValueChange(value_ptr[0], remaining);
			} else {
				// Write from nw-1 to 0
				for (unsigned j = nw; j-- > 0;) {
					h.WriteUInt(value_ptr[j]);
				}
			}
			value_ptr += static_cast<unsigned>(change_entries[i].encoding) * nw;
		}
	}
};

inline VariableInfoBase*
VariableInfoBase::Create(uint32_t bitwidth, bool is_real) {
	if (is_real) {
		return new VariableInfoDouble();
	} else if (bitwidth <= 8) {
		return new VariableInfoScalarInt<uint8_t>(bitwidth);
	} else if (bitwidth <= 16) {
		return new VariableInfoScalarInt<uint16_t>(bitwidth);
	} else if (bitwidth <= 32) {
		return new VariableInfoScalarInt<uint32_t>(bitwidth);
	} else if (bitwidth <= 64) {
		return new VariableInfoScalarInt<uint64_t>(bitwidth);
	} else {
		return new VariableInfoLongInt(bitwidth);
	}
	UNREACHABLE;
}

} // namespace fst
