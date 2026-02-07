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
#include "fstcpp/fstcpp.h"
#include "fstcpp/fstcpp_file.h"

namespace fst {

namespace platform {

// For C++14
// Can remove once C++23 is required
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
// clang-format off
template <typename U> U to_big_endian(U u) { return u; }
#else
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 1>) { return u; }
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 2>) { return __builtin_bswap16(u); }
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 4>) { return __builtin_bswap32(u); }
template<typename U> U to_big_endian(U u, std::integral_constant<size_t, 8>) { return __builtin_bswap64(u); }
// clang-format on
template <typename U>
U to_big_endian(U u) {
	return platform::to_big_endian(u, std::integral_constant<size_t, sizeof(U)>());
}
#endif

}  // namespace platform

struct StreamwriteHelper {
	std::ostream *os;

	StreamwriteHelper(std::ostream &os_) : os(&os_) {}
	StreamwriteHelper(std::ostream *os_) : os(os_) {}

	// write the entire uint, big-endian
	// We do not provide little-endian version since FST only uses big-endian
	template <typename U>
	StreamwriteHelper &writeUInt(U u) {
		u = platform::to_big_endian(u);
		os->write(reinterpret_cast<const char *>(&u), sizeof(u));
		return *this;
	}

	// write the uint, big-endian, left-aligned but only (bitwidth+7)/8 bytes
	// This is a very special case for value changes
	// For example, if the value is 10-bits (e.g. logic [9:0] in Verilog),
	// then the first byte will be [9-:8], then {[1:0], 6'b0}.
	template <typename U>
	StreamwriteHelper &writeUIntPartialForValueChange(U u, size_t bitwidth) {
		// Shift left to align the MSB to the MSB of the uint
		u <<= sizeof(u) * 8 - bitwidth;
		// write the first (bitwidth+7)/8 bytes
		u = platform::to_big_endian(u);
		os->write(reinterpret_cast<const char *>(&u), (bitwidth + 7) / 8);
		return *this;
	}

	StreamwriteHelper &writeLEB128(uint64_t v) {
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
		os->write(reinterpret_cast<const char *>(buf), len);
		return *this;
	}

	StreamwriteHelper &writeLEB128Signed(int64_t v) {
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
		os->write(reinterpret_cast<const char *>(buf), len);
		return *this;
	}

	template <typename F>
	StreamwriteHelper &writeFloat(F f) {
		// Always write in native endianness
		os->write(reinterpret_cast<const char *>(&f), sizeof(f));
		return *this;
	}

	StreamwriteHelper &writeBlockHeader(fst::BlockType block_type, uint64_t block_length) {
		return (
			this  //
				->writeUInt(static_cast<uint8_t>(block_type))
				.writeUInt(
					block_length + 8
				)  // The 8 is required by FST, which is the size of this uint64_t
		);
	}

	// write the string, non-null-terminated
	StreamwriteHelper &writeString(const fst::string_view_pair str) {
		os->write(str.first, str.second);
		return *this;
	}

	// write the string, null-terminated
	StreamwriteHelper &writeString0(const fst::string_view_pair str) {
		os->write(str.first, str.second).put('\0');
		return *this;
	}
	StreamwriteHelper &writeString(const std::string &str) {
		return writeString0(fst::make_string_view_pair(str.c_str(), str.size()));
	}
	StreamwriteHelper &writeString(const char *str) {
		return writeString0(fst::make_string_view_pair(str));
	}

	StreamwriteHelper &write(const char *ptr, size_t size) {
		os->write(ptr, size);
		return *this;
	}

	StreamwriteHelper &write(const uint8_t *ptr, size_t size) {
		os->write(reinterpret_cast<const char *>(ptr), size);
		return *this;
	}

	StreamwriteHelper &seek(std::streamoff pos, std::ios_base::seekdir dir) {
		os->seekp(pos, dir);
		return *this;
	}

	StreamwriteHelper &fill(char fill_char, size_t size) {
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
	// cascade multiple write() calls after RecordOffset(), then
	// call DiffOffset() to get the total number of bytes written.

	// (1)
	// std::streamoff diff;
	// h
	// .BeginOffset(diff)
	// .write(...)
	// ... do other stuff ...
	// .EndOffset(&diff); <-- diff will be set to the number of bytes written
	// (2)
	// std::streamoff pos, diff;
	// h
	// .BeginOffset(pos)
	// .write(...)
	// ... do other stuff ...
	// .EndOffset(&diff, pos); <-- diff will be set to the number of bytes written

	// The API uses pointer on purpose to prevent you pass (pos, diff) as arguments
	// to EndOffset(), which is a common mistake.

	StreamwriteHelper &BeginOffset(std::streamoff &pos) {
		pos = os->tellp();
		return *this;
	}

	StreamwriteHelper &EndOffset(std::streamoff *diff) {
		// diff shall store previous position before calling this function
		*diff = os->tellp() - *diff;
		return *this;
	}

	StreamwriteHelper &EndOffset(std::streamoff *diff, std::streamoff pos) {
		*diff = os->tellp() - pos;
		return *this;
	}
};

struct StreamVectorwriteHelper {
	std::vector<uint8_t> &vec;

	StreamVectorwriteHelper(std::vector<uint8_t> &vec_) : vec(vec_) {}

	template <typename T>
	StreamVectorwriteHelper &write(T u) {
		const size_t s = sizeof(u);
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, &u, s);
		return *this;
	}

	template <typename T>
	StreamVectorwriteHelper &fill(T u, size_t count) {
		const size_t s = sizeof(u) * count;
		vec.resize(vec.size() + s);
		for (size_t i = 0; i < count; ++i) {
			std::memcpy(vec.data() + vec.size() - s + i * sizeof(u), &u, sizeof(u));
		}
		return *this;
	}

	template <typename T>
	StreamVectorwriteHelper &write(T *u, size_t size) {
		const size_t s = sizeof(u) * size;
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, u, s);
		return *this;
	}

	template <typename E>
	StreamVectorwriteHelper &writeU8Enum(E e) {
		vec.push_back(static_cast<uint8_t>(e));
		return *this;
	}

	// write the entire uint, big-endian
	// We do not provide little-endian version since FST only uses big-endian
	template <typename U>
	StreamVectorwriteHelper &writeUIntBE(U u) {
		u = platform::to_big_endian(u);
		const size_t s = sizeof(u);
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, &u, s);
		return *this;
	}

	// write the uint, big-endian, left-aligned but only (bitwidth+7)/8 bytes
	// This is a very special case for value changes
	// For example, if the value is 10-bits (e.g. logic [9:0] in Verilog),
	// then the first byte will be [9-:8], then {[1:0], 6'b0}.
	template <typename U>
	StreamVectorwriteHelper &writeUIntPartialForValueChange(U u, size_t bitwidth) {
		// Shift left to align the MSB to the MSB of the uint
		u <<= sizeof(u) * 8 - bitwidth;
		// write the first (bitwidth+7)/8 bytes
		u = platform::to_big_endian(u);
		const size_t s = (bitwidth + 7) / 8;
		vec.resize(vec.size() + s);
		std::memcpy(vec.data() + vec.size() - s, &u, s);
		return *this;
	}

	StreamVectorwriteHelper &writeLEB128(uint64_t v) {
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

	StreamVectorwriteHelper &writeLEB128Signed(int64_t v) {
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

	StreamVectorwriteHelper &writeBlockHeader(fst::BlockType block_type, uint64_t block_length) {
		return (
			this  //
				->writeUIntBE(static_cast<uint8_t>(block_type))
				.writeUIntBE(
					block_length + 8
				)  // The 8 is required by FST, which is the size of this uint64_t
		);
	}

	// write the string, non-null-terminated
	StreamVectorwriteHelper &writeString(const fst::string_view_pair str) {
		if (str.second != 0) {
			const size_t len = str.second;
			const size_t cur = vec.size();
			vec.resize(cur + len);
			std::memcpy(vec.data() + cur, str.first, len);
		}
		return *this;
	}

	// write the string, null-terminated
	StreamVectorwriteHelper &writeString0(const fst::string_view_pair str) {
		if (str.second != 0) {
			const size_t len = str.second;
			const size_t cur = vec.size();
			vec.resize(cur + len + 1);
			std::memcpy(vec.data() + cur, str.first, len);
			vec[cur + len] = '\0';
		} else {
			vec.push_back('\0');
		}
		return *this;
	}
	StreamVectorwriteHelper &writeString(const std::string &str) {
		return writeString0(fst::make_string_view_pair(str.c_str(), str.size()));
	}
	StreamVectorwriteHelper &writeString(const char *str) {
		return writeString0(fst::make_string_view_pair(str));
	}
};

}  // namespace fst
