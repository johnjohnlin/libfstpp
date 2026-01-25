// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once
// direct include
// C system headers
// C++ standard library headers
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
// Other libraries' .h files.
// Your project's .h files.
#include "fstcpp/fst_file.h"
#include "fstcpp/string_view.h"

namespace fst {

namespace platform {

// For C++14
// Can remove once C++23 is required
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
template<typename U>
U to_big_endian(U u) {
	return u;
}
#else
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 1>) { return u; }
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 2>) { return __builtin_bswap16(u); }
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 4>) { return __builtin_bswap32(u); }
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 8>) { return __builtin_bswap64(u); }
template<typename U>
U to_big_endian(U u) {
	return platform::to_big_endian(u, std::integral_constant<size_t, sizeof(U)>());
}
#endif

} // namespace platform


struct StreamWriteHelper {
	std::ostream* os;

	StreamWriteHelper(std::ostream& os_) : os(&os_) {}
	StreamWriteHelper(std::ostream* os_) : os(os_) {}

	// Write the entire uint, big-endian
	// We do not provide little-endian version since FST only uses big-endian
	template<typename U>
	StreamWriteHelper& WriteUInt(U u) {
		u = platform::to_big_endian(u);
		os->write(reinterpret_cast<const char*>(&u), sizeof(u));
		return *this;
	}

	// Write the uint, big-endian, left-aligned but only (bitwidth+7)/8 bytes
	// This is a very special case for value changes
	// For example, if the value is 10-bits (e.g. logic [9:0] in Verilog),
	// then the first byte will be [9-:8], then {[1:0], 6'b0}.
	template<typename U>
	StreamWriteHelper& WriteUIntPartialForValueChange(U u, size_t bitwidth) {
		// Shift left to align the MSB to the MSB of the uint
		u <<= sizeof(u) * 8 - bitwidth;
		// Write the first (bitwidth+7)/8 bytes
		u = platform::to_big_endian(u);
		os->write(reinterpret_cast<const char*>(&u), (bitwidth + 7) / 8);
		return *this;
	}

	StreamWriteHelper& WriteLEB128(uint64_t v) {
		// Just reuse the logic from fstapi.c, is there a better way?
		uint64_t nxt;
		unsigned char buf[10]; /* ceil(64/7) = 10 */
		unsigned char *pnt = buf;
		int len;
		while ((nxt = v >> 7)) {
			*(pnt++) = ((unsigned char)v) | 0x80;
			v = nxt;
		}
		*(pnt++) = (unsigned char)v;
		len = pnt - buf;
		os->write(reinterpret_cast<const char*>(buf), len);
		return *this;
	}

	StreamWriteHelper& WriteLEB128Signed(int64_t v) {
		// Just reuse the logic from fstapi.c, is there a better way?
		unsigned char buf[15]; /* ceil(64/7) = 10 + sign byte padded way up */
		unsigned char byt;
		unsigned char *pnt = buf;
		int more = 1;
		int len;
		do {
			byt = v | 0x80;
			v >>= 7;

			if (((!v) && (!(byt & 0x40))) || ((v == -1) && (byt & 0x40))) {
				more = 0;
				byt &= 0x7f;
			}

			*(pnt++) = byt;
		} while (more);
		len = pnt - buf;
		os->write(reinterpret_cast<const char*>(buf), len);
		return *this;
	}


	template<typename F>
	StreamWriteHelper& WriteFloat(F f) {
		// Always write in native endianness
		os->write(reinterpret_cast<const char*>(&f), sizeof(f));
		return *this;
	}

	StreamWriteHelper& WriteBlockHeader(fst::BlockType block_type, uint64_t block_length) {
		return (
			this
			->WriteUInt(static_cast<uint8_t>(block_type))
			.WriteUInt(block_length + 8) // The 8 is required by FST, which is the size of this uint64_t
		);
	}

	// Write the string, non-null-terminated
	StreamWriteHelper& WriteString(const nonstd::string_view str) {
		os->write(str.data(), str.size());
		return *this;
	}

	// Write the string, null-terminated
	StreamWriteHelper& WriteString0(const nonstd::string_view str) {
		os->write(str.data(), str.size()).put('\0');
		return *this;
	}
	StreamWriteHelper& WriteString(const std::string& str) { return WriteString0(nonstd::string_view(str)); }
	StreamWriteHelper& WriteString(const char* str) { return WriteString0(nonstd::string_view(str)); }

	StreamWriteHelper& Write(const char* ptr, size_t size) {
		os->write(ptr, size);
		return *this;
	}

	StreamWriteHelper& Write(const uint8_t* ptr, size_t size) {
		os->write(reinterpret_cast<const char*>(ptr), size);
		return *this;
	}

	StreamWriteHelper& Seek(std::streamoff pos, std::ios_base::seekdir dir) {
		os->seekp(pos, dir);
		return *this;
	}

	StreamWriteHelper& Fill(char fill_char, size_t size) {
		if (size > 32) {
			// optimize large fills
			constexpr unsigned kChunkSize = 16;
			char buf[kChunkSize];
			std::memset(buf, fill_char, kChunkSize);
			for (size_t i = 0; i < size / kChunkSize; ++i) {
				os->write(buf, kChunkSize);
			}
			size %= kChunkSize;
		}
		for (size_t i = 0; i < size; ++i) {
			os->put(fill_char);
		}
		return *this;
	}

	// Handy functions for writing variable length data, you can
	// cascade multiple Write() calls after RecordOffset(), then
	// call DiffOffset() to get the total number of bytes written.

	// (1)
	// std::streamoff diff;
	// h
	// .BeginOffset(diff)
	// .Write(...)
	// ... do other stuff ...
	// .EndOffset(&diff); <-- diff will be set to the number of bytes written
	// (2)
	// std::streamoff pos, diff;
	// h
	// .BeginOffset(pos)
	// .Write(...)
	// ... do other stuff ...
	// .EndOffset(&diff, pos); <-- diff will be set to the number of bytes written

	// The API uses pointer on purpose to prevent you pass (pos, diff) as arguments
	// to EndOffset(), which is a common mistake.

	StreamWriteHelper& BeginOffset(std::streamoff& pos) {
		pos = os->tellp();
		return *this;
	}

	StreamWriteHelper& EndOffset(std::streamoff* diff) {
		// diff shall store previous position before calling this function
		*diff = os->tellp() - *diff;
		return *this;
	}

	StreamWriteHelper& EndOffset(std::streamoff* diff, std::streamoff pos) {
		*diff = os->tellp() - pos;
		return *this;
	}
};

struct StreamVectorWriteHelper {
	std::vector<uint8_t>& vec;

	StreamVectorWriteHelper(std::vector<uint8_t>& vec_) : vec(vec_) {}

	template<typename T>
	StreamVectorWriteHelper& Write(T u) {
		const size_t s = sizeof(u);
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, &u, s);
		return *this;
	}

	template<typename T>
	StreamVectorWriteHelper& Fill(T u, size_t count) {
		const size_t s = sizeof(u) * count;
		vec.resize(vec.size() + s);
		for (size_t i = 0; i < count; ++i) {
			std::memcpy(vec.data() + vec.size() - s + i * sizeof(u), &u, sizeof(u));
		}
		return *this;
	}

	template<typename T>
	StreamVectorWriteHelper& Write(T* u, size_t size) {
		const size_t s = sizeof(u) * size;
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, u, s);
		return *this;
	}

	// Write the entire uint, big-endian
	// We do not provide little-endian version since FST only uses big-endian
	template<typename U>
	StreamVectorWriteHelper& WriteUIntBE(U u) {
		u = platform::to_big_endian(u);
		const size_t s = sizeof(u);
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, &u, s);
		return *this;
	}

	// Write the uint, big-endian, left-aligned but only (bitwidth+7)/8 bytes
	// This is a very special case for value changes
	// For example, if the value is 10-bits (e.g. logic [9:0] in Verilog),
	// then the first byte will be [9-:8], then {[1:0], 6'b0}.
	template<typename U>
	StreamVectorWriteHelper& WriteUIntPartialForValueChange(U u, size_t bitwidth) {
		// Shift left to align the MSB to the MSB of the uint
		u <<= sizeof(u) * 8 - bitwidth;
		// Write the first (bitwidth+7)/8 bytes
		u = platform::to_big_endian(u);
		const size_t s = (bitwidth + 7) / 8;
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, &u, s);
		return *this;
	}

	StreamVectorWriteHelper& WriteLEB128(uint64_t v) {
		// Just reuse the logic from fstapi.c, is there a better way?
		uint64_t nxt;
		unsigned char buf[10]; /* ceil(64/7) = 10 */
		unsigned char *pnt = buf;
		int len;
		while ((nxt = v >> 7)) {
			*(pnt++) = ((unsigned char)v) | 0x80;
			v = nxt;
		}
		*(pnt++) = (unsigned char)v;
		len = pnt - buf;

		const size_t cur = vec.size();
		vec.resize(cur + len);
		std::memcpy(vec.data() + cur, buf, len);
		return *this;
	}

	StreamVectorWriteHelper& WriteLEB128Signed(int64_t v) {
		// Just reuse the logic from fstapi.c, is there a better way?
		unsigned char buf[15]; /* ceil(64/7) = 10 + sign byte padded way up */
		unsigned char byt;
		unsigned char *pnt = buf;
		int more = 1;
		int len;
		do {
			byt = v | 0x80;
			v >>= 7;

			if (((!v) && (!(byt & 0x40))) || ((v == -1) && (byt & 0x40))) {
				more = 0;
				byt &= 0x7f;
			}

			*(pnt++) = byt;
		} while (more);
		len = pnt - buf;

		const size_t cur = vec.size();
		vec.resize(cur + len);
		std::memcpy(vec.data() + cur, buf, len);
		return *this;
	}

	StreamVectorWriteHelper& WriteBlockHeader(fst::BlockType block_type, uint64_t block_length) {
		return (
			this
			->WriteUIntBE(static_cast<uint8_t>(block_type))
			.WriteUIntBE(block_length + 8) // The 8 is required by FST, which is the size of this uint64_t
		);
	}

	// Write the string, non-null-terminated
	StreamVectorWriteHelper& WriteString(const nonstd::string_view str) {
		const size_t len = str.size();
		const size_t cur = vec.size();
		vec.resize(cur + len);
		std::memcpy(vec.data() + cur, str.data(), len);
		return *this;
	}

	// Write the string, null-terminated
	StreamVectorWriteHelper& WriteString0(const nonstd::string_view str) {
		const size_t len = str.size();
		const size_t cur = vec.size();
		vec.resize(cur + len + 1);
		std::memcpy(vec.data() + cur, str.data(), len);
		vec[cur + len] = '\0';
		return *this;
	}
	StreamVectorWriteHelper& WriteString(const std::string& str) { return WriteString0(nonstd::string_view(str)); }
	StreamVectorWriteHelper& WriteString(const char* str) { return WriteString0(nonstd::string_view(str)); }
};

} // namespace fst
