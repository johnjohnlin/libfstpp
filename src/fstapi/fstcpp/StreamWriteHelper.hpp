#pragma once
// direct include
// C system headers
// C++ standard library headers
#include <bit>
#include <cstdint>
#include <cstring>
#include <iostream>
// Other libraries' .h files.
// Your project's .h files.
#include "fstcpp/fst_file.hpp"
#include "fstcpp/string_view.hpp"

namespace fst {

namespace platform {
// C++23 byteswap fallback for C++20 (not constexpr, using intrinsics)
template<typename U>
U byteswap(U u) {
	if constexpr (sizeof(U) == 8) {
		u = __builtin_bswap64(u);
	} else if constexpr (sizeof(U) == 4) {
		u = __builtin_bswap32(u);
	} else if constexpr (sizeof(U) == 2) {
		u = __builtin_bswap16(u);
	}
	return u;
}

} // namespace platform

// Native endianness detection
constexpr bool native_endian_is_little() {
	union { uint16_t i; uint8_t c[2]; } u = {0x0100};
	return u.c[1];
}


struct StreamWriteHelper {
	std::ostream* os;

	StreamWriteHelper(std::ostream& os_) : os(&os_) {}
	StreamWriteHelper(std::ostream* os_) : os(os_) {}

	// Write the entire uint, big-endian
	// We do not provide little-endian version since FST only uses big-endian
	template<typename U>
	StreamWriteHelper& WriteUInt(U u) {
		if (native_endian_is_little()) {
			u = platform::byteswap(u);
		}
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
		if (native_endian_is_little()) {
			u = platform::byteswap(u);
		}
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

} // namespace fst
