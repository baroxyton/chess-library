/*
MIT License

Copyright (c) 2023 disservin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

THIS FILE IS AUTO GENERATED DO NOT CHANGE MANUALLY.

Source: https://github.com/Disservin/chess-library

VERSION: 0.8.7
*/

#ifndef CHESS_HPP
#define CHESS_HPP


#include <functional>
#include <utility>


#include <cstdint>


#if __cplusplus >= 202002L
#    include <bit>
#endif
#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <string>

#if defined(_MSC_VER)
#    include <intrin.h>
#    include <nmmintrin.h>
#endif


#include <string_view>


#include <ostream>

namespace chess {

class Color {
   public:
    enum class underlying : std::int8_t { WHITE = 0, BLACK = 1, NONE = -1 };

    constexpr Color() : color(underlying::NONE) {}
    constexpr Color(underlying c) : color(c) { assert(isValid(int(c))); }
    constexpr Color(int c) : Color(static_cast<underlying>(c)) { assert(isValid(c)); }
    constexpr Color(std::string_view str)
        : color(str == "w"   ? underlying::WHITE
                : str == "b" ? underlying::BLACK
                             : underlying::NONE) {}

    /**
     * @brief Gets the long string representation of the color
     * @return "White" for WHITE, "Black" for BLACK
     * "None" for NONE
     */
    [[nodiscard]] std::string longStr() const {
        switch (color) {
            case underlying::WHITE:
                return "White";
            case underlying::BLACK:
                return "Black";
            default:
                return "None";
        }
    }

    constexpr Color operator~() const noexcept {
        assert(color != underlying::NONE);
        return Color(static_cast<underlying>(static_cast<int>(color) ^ 1));
    }

    constexpr bool operator==(const Color& rhs) const noexcept { return color == rhs.color; }
    constexpr bool operator!=(const Color& rhs) const noexcept { return color != rhs.color; }

    constexpr operator int() const noexcept { return static_cast<int>(color); }

    explicit operator std::string() const {
        return color == underlying::WHITE ? "w" : color == underlying::BLACK ? "b" : "NONE";
    }

    [[nodiscard]] constexpr underlying internal() const noexcept { return color; }

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        return os << static_cast<std::string>(color);
    }

    static constexpr underlying WHITE = underlying::WHITE;
    static constexpr underlying BLACK = underlying::BLACK;
    static constexpr underlying NONE  = underlying::NONE;

   private:
    underlying color;

    static constexpr bool isValid(int c) { return c == 0 || c == 1 || c == -1; }
};

constexpr Color::underlying operator~(Color::underlying color) {
    return color == Color::underlying::WHITE   ? Color::underlying::BLACK
           : color == Color::underlying::BLACK ? Color::underlying::WHITE
                                               : Color::underlying::NONE;
}

}  // namespace chess

#include <vector>

namespace chess {
namespace utils {

// Split a string by a delimiter
[[nodiscard]] inline std::vector<std::string_view> splitString(std::string_view string, const char &delimiter) {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end   = string.find(delimiter);

    while (end != std::string_view::npos) {
        result.push_back(string.substr(start, end - start));
        start = end + 1;
        end   = string.find(delimiter, start);
    }

    // Add the last chunk (or the only chunk if there are no delimiters)
    result.push_back(string.substr(start));

    return result;
}

constexpr char tolower(char c) { return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c; }

}  // namespace utils

}  // namespace chess

namespace chess {

#define CHESS_DECLARE_RANK(N)                            \
    static constexpr auto SQ_A##N = underlying::SQ_A##N; \
    static constexpr auto SQ_B##N = underlying::SQ_B##N; \
    static constexpr auto SQ_C##N = underlying::SQ_C##N; \
    static constexpr auto SQ_D##N = underlying::SQ_D##N; \
    static constexpr auto SQ_E##N = underlying::SQ_E##N; \
    static constexpr auto SQ_F##N = underlying::SQ_F##N; \
    static constexpr auto SQ_G##N = underlying::SQ_G##N; \
    static constexpr auto SQ_H##N = underlying::SQ_H##N;

class File {
   public:
    enum class underlying : std::uint8_t { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, NO_FILE };

    constexpr File() : file(underlying::NO_FILE) {}
    constexpr File(underlying file) : file(file) {}
    constexpr File(int file) : file(static_cast<underlying>(file)) {}
    constexpr File(std::string_view sw)
        : file(static_cast<underlying>(static_cast<char>(utils::tolower(static_cast<unsigned char>(sw[0]))) - 'a')) {}

    [[nodiscard]] constexpr underlying internal() const noexcept { return file; }

    constexpr bool operator==(const File& rhs) const noexcept { return file == rhs.file; }
    constexpr bool operator!=(const File& rhs) const noexcept { return file != rhs.file; }

    constexpr bool operator==(const underlying& rhs) const noexcept { return file == rhs; }
    constexpr bool operator!=(const underlying& rhs) const noexcept { return file != rhs; }

    constexpr bool operator>=(const File& rhs) const noexcept {
        return static_cast<int>(file) >= static_cast<int>(rhs.file);
    }
    constexpr bool operator<=(const File& rhs) const noexcept {
        return static_cast<int>(file) <= static_cast<int>(rhs.file);
    }

    constexpr bool operator>(const File& rhs) const noexcept {
        return static_cast<int>(file) > static_cast<int>(rhs.file);
    }

    constexpr bool operator<(const File& rhs) const noexcept {
        return static_cast<int>(file) < static_cast<int>(rhs.file);
    }

    constexpr operator int() const noexcept { return static_cast<int>(file); }

    explicit operator std::string() const { return std::string(1, static_cast<char>(static_cast<int>(file) + 'a')); }

    static constexpr underlying FILE_A  = underlying::FILE_A;
    static constexpr underlying FILE_B  = underlying::FILE_B;
    static constexpr underlying FILE_C  = underlying::FILE_C;
    static constexpr underlying FILE_D  = underlying::FILE_D;
    static constexpr underlying FILE_E  = underlying::FILE_E;
    static constexpr underlying FILE_F  = underlying::FILE_F;
    static constexpr underlying FILE_G  = underlying::FILE_G;
    static constexpr underlying FILE_H  = underlying::FILE_H;
    static constexpr underlying NO_FILE = underlying::NO_FILE;

   private:
    underlying file;
};

class Rank {
   public:
    enum class underlying { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, NO_RANK };

    constexpr Rank() : rank_(underlying::NO_RANK) {}
    constexpr Rank(underlying rank) : rank_(rank) {}
    constexpr Rank(int rank) : rank_(static_cast<underlying>(rank)) {}
    constexpr Rank(std::string_view sw)
        : rank_(static_cast<underlying>(static_cast<char>(utils::tolower(static_cast<unsigned char>(sw[0]))) - '1')) {}

    [[nodiscard]] constexpr underlying internal() const noexcept { return rank_; }

    constexpr bool operator==(const Rank& rhs) const noexcept { return rank_ == rhs.rank_; }
    constexpr bool operator!=(const Rank& rhs) const noexcept { return rank_ != rhs.rank_; }

    constexpr bool operator==(const underlying& rhs) const noexcept { return rank_ == rhs; }
    constexpr bool operator!=(const underlying& rhs) const noexcept { return rank_ != rhs; }

    constexpr bool operator>=(const Rank& rhs) const noexcept {
        return static_cast<int>(rank_) >= static_cast<int>(rhs.rank_);
    }
    constexpr bool operator<=(const Rank& rhs) const noexcept {
        return static_cast<int>(rank_) <= static_cast<int>(rhs.rank_);
    }

    operator std::string() const { return std::string(1, static_cast<char>(static_cast<int>(rank_) + '1')); }

    constexpr operator int() const noexcept { return static_cast<int>(rank_); }

    constexpr std::uint64_t bb() const noexcept { return 0xffULL << (8 * static_cast<int>(rank_)); }

    [[nodiscard]] static constexpr bool back_rank(Rank r, Color color) noexcept {
        if (color == Color::WHITE) return r == Rank::RANK_1;
        return r == Rank::RANK_8;
    }

    [[nodiscard]] static constexpr Rank rank(Rank r, Color color) noexcept {
        if (color == Color::WHITE) return r;
        return Rank(static_cast<underlying>(static_cast<int>(RANK_8) - static_cast<int>(r)));
    }

    static constexpr underlying RANK_1  = underlying::RANK_1;
    static constexpr underlying RANK_2  = underlying::RANK_2;
    static constexpr underlying RANK_3  = underlying::RANK_3;
    static constexpr underlying RANK_4  = underlying::RANK_4;
    static constexpr underlying RANK_5  = underlying::RANK_5;
    static constexpr underlying RANK_6  = underlying::RANK_6;
    static constexpr underlying RANK_7  = underlying::RANK_7;
    static constexpr underlying RANK_8  = underlying::RANK_8;
    static constexpr underlying NO_RANK = underlying::NO_RANK;

   private:
    underlying rank_;
};

class Square {
   public:
    // clang-format off
    enum class underlying {
        SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
        SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
        SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
        SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
        SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
        SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
        SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
        SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
        NO_SQ
    };
    // clang-format on

// when c++20
#if __cplusplus >= 202002L
    using enum underlying;
#else

    CHESS_DECLARE_RANK(1)
    CHESS_DECLARE_RANK(2)
    CHESS_DECLARE_RANK(3)
    CHESS_DECLARE_RANK(4)
    CHESS_DECLARE_RANK(5)
    CHESS_DECLARE_RANK(6)
    CHESS_DECLARE_RANK(7)
    CHESS_DECLARE_RANK(8)

    static constexpr auto NO_SQ = underlying::NO_SQ;

#endif

    constexpr Square() : sq(underlying::NO_SQ) {}

    constexpr Square(int sq) : sq(static_cast<underlying>(sq)) { assert(sq <= 64 && sq >= 0); }
    constexpr Square(File file, Rank rank) : sq(static_cast<underlying>(file + rank * 8)) {}
    constexpr Square(Rank rank, File file) : sq(static_cast<underlying>(file + rank * 8)) {}
    constexpr Square(underlying sq) : sq(sq) {}
    constexpr Square(std::string_view str) : sq(static_cast<underlying>((str[0] - 'a') + (str[1] - '1') * 8)) {
        assert(str.size() >= 2);
    }

    constexpr Square operator^(const Square& s) const noexcept {
        return Square(static_cast<underlying>(static_cast<int>(sq) ^ s.index()));
    };

    constexpr bool operator==(const Square& rhs) const noexcept { return sq == rhs.sq; }

    constexpr bool operator!=(const Square& rhs) const noexcept { return sq != rhs.sq; }

    constexpr bool operator>(const Square& rhs) const noexcept {
        return static_cast<int>(sq) > static_cast<int>(rhs.sq);
    }

    constexpr bool operator>=(const Square& rhs) const noexcept {
        return static_cast<int>(sq) >= static_cast<int>(rhs.sq);
    }

    constexpr bool operator<(const Square& rhs) const noexcept {
        return static_cast<int>(sq) < static_cast<int>(rhs.sq);
    }

    constexpr bool operator<=(const Square& rhs) const noexcept {
        return static_cast<int>(sq) <= static_cast<int>(rhs.sq);
    }

    constexpr Square operator+(const Square& rhs) const noexcept {
        return Square(static_cast<underlying>(static_cast<int>(sq) + static_cast<int>(rhs.sq)));
    }

    constexpr Square operator-(const Square& rhs) const noexcept {
        return Square(static_cast<underlying>(static_cast<int>(sq) - static_cast<int>(rhs.sq)));
    }

    constexpr Square& operator++() noexcept {
        sq = static_cast<underlying>(static_cast<int>(sq) + 1);
        return *this;
    }

    constexpr Square operator++(int) noexcept {
        Square tmp(*this);
        operator++();
        return tmp;
    }

    constexpr Square& operator--() noexcept {
        sq = static_cast<underlying>(static_cast<int>(sq) - 1);
        return *this;
    }

    constexpr Square operator--(int) noexcept {
        Square tmp(*this);
        operator--();
        return tmp;
    }

    /**
     * @brief Get a string representation of the square.
     */
    [[nodiscard]] operator std::string() const {
        std::string str;
        str += static_cast<std::string>(file());
        str += static_cast<std::string>(rank());
        return str;
    }

    [[nodiscard]] constexpr int index() const noexcept { return static_cast<int>(sq); }

    [[nodiscard]] constexpr File file() const noexcept { return File(index() & 7); }
    [[nodiscard]] constexpr Rank rank() const noexcept { return Rank(index() >> 3); }

    /**
     * @brief Check if the square is light.
     * @return
     */
    [[nodiscard]] constexpr bool is_light() const noexcept {
        return (static_cast<std::int8_t>(sq) / 8 + static_cast<std::int8_t>(sq) % 8) % 2 == 0;
    }

    /**
     * @brief Check if the square is dark.
     * @return
     */
    [[nodiscard]] constexpr bool is_dark() const noexcept { return !is_light(); }

    /**
     * @brief Check if the square is vali.d
     * @return
     */
    [[nodiscard]] constexpr bool is_valid() const noexcept { return static_cast<std::int8_t>(sq) < 64; }

    /**
     * @brief Check if the square is valid.
     * @param r
     * @param f
     * @return
     */
    [[nodiscard]] constexpr static bool is_valid(Rank r, File f) noexcept {
        return r >= Rank::RANK_1 && r <= Rank::RANK_8 && f >= File::FILE_A && f <= File::FILE_H;
    }

    /**
     * @brief Get the chebyshev distance between two squares.
     * @param sq
     * @param sq2
     * @return
     */
    [[nodiscard]] static int distance(Square sq, Square sq2) noexcept {
        return std::max(std::abs(sq.file() - sq2.file()), std::abs(sq.rank() - sq2.rank()));
    }

    /**
     * @brief Absolute value of sq - sq2.
     * @param sq
     * @param sq2
     * @return
     */
    [[nodiscard]] static int value_distance(Square sq, Square sq2) noexcept {
        return std::abs(sq.index() - sq2.index());
    }

    /**
     * @brief Check if the squares share the same color. I.e. if they are both light or dark.
     * @param sq
     * @param sq2
     * @return
     */
    [[nodiscard]] static constexpr bool same_color(Square sq, Square sq2) noexcept {
        return ((9 * (sq ^ sq2).index()) & 8) == 0;
    }

    /**
     * @brief Check if the square is on the back rank.
     * @param sq
     * @param color
     * @return
     */
    [[nodiscard]] static constexpr bool back_rank(Square sq, Color color) noexcept {
        if (color == Color::WHITE)
            return sq.rank() == Rank::RANK_1;
        else
            return sq.rank() == Rank::RANK_8;
    }

    /**
     * @brief Flips the square vertically.
     * @return
     */
    constexpr Square& flip() noexcept {
        sq = static_cast<underlying>(static_cast<int>(sq) ^ 56);
        return *this;
    }

    /**
     * @brief Flips the square vertically, depending on the color.
     * @param c
     * @return
     */
    [[nodiscard]] constexpr Square relative_square(Color c) const noexcept {
        return Square(static_cast<int>(sq) ^ (c * 56));
    }

    [[nodiscard]] constexpr int diagonal_of() const noexcept { return 7 + rank() - file(); }

    [[nodiscard]] constexpr int antidiagonal_of() const noexcept { return rank() + file(); }

    /**
     * @brief Get the en passant square. Should only be called for valid ep positions.
     * @return
     */
    [[nodiscard]] constexpr Square ep_square() const noexcept {
        assert(rank() == Rank::RANK_3     // capture
               || rank() == Rank::RANK_4  // push
               || rank() == Rank::RANK_5  // push
               || rank() == Rank::RANK_6  // capture
        );
        return Square(static_cast<int>(sq) ^ 8);
    }

    /**
     * @brief Get the destination square of the king after castling.
     * @param is_king_side
     * @param c
     * @return
     */
    [[nodiscard]] static constexpr Square castling_king_square(bool is_king_side, Color c) noexcept {
        return Square(is_king_side ? Square::SQ_G1 : Square::SQ_C1).relative_square(c);
    }

    /**
     * @brief Get the destination square of the rook after castling.
     * @param is_king_side
     * @param c
     * @return
     */
    [[nodiscard]] static constexpr Square castling_rook_square(bool is_king_side, Color c) noexcept {
        return Square(is_king_side ? Square::SQ_F1 : Square::SQ_D1).relative_square(c);
    }

    /**
     * @brief Maximum number of squares.
     * @return
     */
    [[nodiscard]] static constexpr int max() noexcept { return 64; }

   private:
    underlying sq;
};

inline std::ostream& operator<<(std::ostream& os, const Square& sq) {
    os << static_cast<std::string>(sq);
    return os;
}

enum class Direction : int8_t {
    NORTH      = 8,
    WEST       = -1,
    SOUTH      = -8,
    EAST       = 1,
    NORTH_EAST = 9,
    NORTH_WEST = 7,
    SOUTH_WEST = -9,
    SOUTH_EAST = -7
};

[[nodiscard]] constexpr Direction make_direction(Direction dir, Color c) noexcept {
    if (c == Color::BLACK) return static_cast<Direction>(-static_cast<int8_t>(dir));
    return dir;
}

constexpr Square operator+(Square sq, Direction dir) {
    return static_cast<Square>(sq.index() + static_cast<int8_t>(dir));
}

#undef CHESS_DECLARE_RANK

}  // namespace chess

namespace chess {

class Bitboard {
   public:
    constexpr Bitboard() : bits(0) {}
    constexpr Bitboard(std::uint64_t bits) : bits(bits) {}
    constexpr Bitboard(File file) : bits(0) {
        assert(file != File::NO_FILE);
        bits = 0x0101010101010101ULL << static_cast<int>(file.internal());
    }
    constexpr Bitboard(Rank rank) : bits(0) {
        assert(rank != Rank::NO_RANK);
        bits = 0xFFULL << (8 * static_cast<int>(rank.internal()));
    }

    explicit operator bool() const noexcept { return bits != 0; }

    explicit operator std::string() const {
        std::bitset<64> b(bits);
        std::string str_bitset = b.to_string();

        std::string str;

        for (int i = 0; i < 64; i += 8) {
            std::string x = str_bitset.substr(i, 8);
            std::reverse(x.begin(), x.end());
            str += x + '\n';
        }
        return str;
    }

    constexpr Bitboard operator&&(bool rhs) const noexcept { return Bitboard(bits && rhs); }

    constexpr Bitboard operator&(std::uint64_t rhs) const noexcept { return Bitboard(bits & rhs); }
    constexpr Bitboard operator|(std::uint64_t rhs) const noexcept { return Bitboard(bits | rhs); }
    constexpr Bitboard operator^(std::uint64_t rhs) const noexcept { return Bitboard(bits ^ rhs); }
    constexpr Bitboard operator<<(std::uint64_t rhs) const noexcept { return Bitboard(bits << rhs); }
    constexpr Bitboard operator>>(std::uint64_t rhs) const noexcept { return Bitboard(bits >> rhs); }
    constexpr bool operator==(std::uint64_t rhs) const noexcept { return bits == rhs; }
    constexpr bool operator!=(std::uint64_t rhs) const noexcept { return bits != rhs; }

    constexpr Bitboard operator&(const Bitboard& rhs) const noexcept { return Bitboard(bits & rhs.bits); }
    constexpr Bitboard operator|(const Bitboard& rhs) const noexcept { return Bitboard(bits | rhs.bits); }
    constexpr Bitboard operator^(const Bitboard& rhs) const noexcept { return Bitboard(bits ^ rhs.bits); }
    constexpr Bitboard operator~() const noexcept { return Bitboard(~bits); }

    constexpr Bitboard& operator&=(const Bitboard& rhs) noexcept {
        bits &= rhs.bits;
        return *this;
    }

    constexpr Bitboard& operator|=(const Bitboard& rhs) noexcept {
        bits |= rhs.bits;
        return *this;
    }

    constexpr Bitboard& operator^=(const Bitboard& rhs) noexcept {
        bits ^= rhs.bits;
        return *this;
    }

    constexpr bool operator==(const Bitboard& rhs) const noexcept { return bits == rhs.bits; }
    constexpr bool operator!=(const Bitboard& rhs) const noexcept { return bits != rhs.bits; }
    constexpr bool operator||(const Bitboard& rhs) const noexcept { return bits || rhs.bits; }
    constexpr bool operator&&(const Bitboard& rhs) const noexcept { return bits && rhs.bits; }

    constexpr Bitboard& set(int index) noexcept {
        assert(index >= 0 && index < 64);
        bits |= (1ULL << index);
        return *this;
    }

    [[nodiscard]] constexpr bool check(int index) const noexcept {
        assert(index >= 0 && index < 64);
        return bits & (1ULL << index);
    }

    constexpr Bitboard& clear(int index) noexcept {
        assert(index >= 0 && index < 64);
        bits &= ~(1ULL << index);
        return *this;
    }

    constexpr Bitboard& clear() noexcept {
        bits = 0;
        return *this;
    }

    [[nodiscard]] static constexpr Bitboard fromSquare(int index) noexcept {
        assert(index >= 0 && index < 64);
        return Bitboard(1ULL << index);
    }

    [[nodiscard]] static constexpr Bitboard fromSquare(Square sq) noexcept {
        assert(sq.index() >= 0 && sq.index() < 64);
        return Bitboard(1ULL << sq.index());
    }

    [[nodiscard]] constexpr bool empty() const noexcept { return bits == 0; }

    [[nodiscard]]
#if !defined(_MSC_VER)
    constexpr
#endif
        int lsb() const noexcept {
        assert(bits != 0);
#if __cplusplus >= 202002L
        return std::countr_zero(bits);
#else
#    if defined(__GNUC__)
        return __builtin_ctzll(bits);
#    elif defined(_MSC_VER)
        unsigned long idx;
        _BitScanForward64(&idx, bits);
        return static_cast<int>(idx);
#    else
#        error "Compiler not supported."
#    endif
#endif
    }

    [[nodiscard]]
#if !defined(_MSC_VER)
    constexpr
#endif
        int msb() const noexcept {
        assert(bits != 0);

#if __cplusplus >= 202002L
        return std::countl_zero(bits) ^ 63;
#else
#    if defined(__GNUC__)
        return 63 ^ __builtin_clzll(bits);
#    elif defined(_MSC_VER)
        unsigned long idx;
        _BitScanReverse64(&idx, bits);
        return static_cast<int>(idx);
#    else
#        error "Compiler not supported."
#    endif
#endif
    }

    [[nodiscard]]
#if !defined(_MSC_VER)
    constexpr
#endif
        int count() const noexcept {
#if __cplusplus >= 202002L
        return std::popcount(bits);
#else
#    if defined(_MSC_VER) || defined(__INTEL_COMPILER)
        return static_cast<int>(_mm_popcnt_u64(bits));
#    else
        return __builtin_popcountll(bits);
#    endif
#endif
    }

    [[nodiscard]]
#if !defined(_MSC_VER)
    constexpr
#endif
        std::uint8_t pop() noexcept {
        assert(bits != 0);
        std::uint8_t index = lsb();
        bits &= bits - 1;
        return index;
    }

    [[nodiscard]] constexpr std::uint64_t getBits() const noexcept { return bits; }

    friend std::ostream& operator<<(std::ostream& os, const Bitboard& bb);

   private:
    std::uint64_t bits;
};

inline std::ostream& operator<<(std::ostream& os, const Bitboard& bb) {
    os << std::string(bb);
    return os;
}

constexpr Bitboard operator&(std::uint64_t lhs, const Bitboard& rhs) { return rhs & lhs; }
constexpr Bitboard operator|(std::uint64_t lhs, const Bitboard& rhs) { return rhs | lhs; }
}  // namespace chess

namespace chess {
class Board;
}  // namespace chess

namespace chess {
class attacks {
    using U64 = std::uint64_t;
    struct Magic {
        U64 mask;
        U64 magic;
        Bitboard *attacks;
        U64 shift;

        U64 operator()(Bitboard b) const { return (((b & mask)).getBits() * magic) >> shift; }
    };

    // Slow function to calculate bishop attacks
    [[nodiscard]] static Bitboard bishopAttacks(Square sq, Bitboard occupied);

    // Slow function to calculate rook attacks
    [[nodiscard]] static Bitboard rookAttacks(Square sq, Bitboard occupied);

    // Initializes the magic bitboard tables for sliding pieces
    static void initSliders(Square sq, Magic table[], U64 magic,
                            const std::function<Bitboard(Square, Bitboard)> &attacks);

    // clang-format off
    // pre-calculated lookup table for pawn attacks
    static constexpr Bitboard PawnAttacks[2][64] = {
        // white pawn attacks
        { 0x200, 0x500, 0xa00, 0x1400,
        0x2800, 0x5000, 0xa000, 0x4000,
        0x20000, 0x50000, 0xa0000, 0x140000,
        0x280000, 0x500000, 0xa00000, 0x400000,
        0x2000000, 0x5000000, 0xa000000, 0x14000000,
        0x28000000, 0x50000000, 0xa0000000, 0x40000000,
        0x200000000, 0x500000000, 0xa00000000, 0x1400000000,
        0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000,
        0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000,
        0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000,
        0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000,
        0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000,
        0x200000000000000, 0x500000000000000, 0xa00000000000000, 0x1400000000000000,
        0x2800000000000000, 0x5000000000000000, 0xa000000000000000, 0x4000000000000000,
        0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0 },

        // black pawn attacks
        { 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0x0,
            0x2, 0x5, 0xa, 0x14,
            0x28, 0x50, 0xa0, 0x40,
            0x200, 0x500, 0xa00, 0x1400,
            0x2800, 0x5000, 0xa000, 0x4000,
            0x20000, 0x50000, 0xa0000, 0x140000,
            0x280000, 0x500000, 0xa00000, 0x400000,
            0x2000000, 0x5000000, 0xa000000, 0x14000000,
            0x28000000, 0x50000000, 0xa0000000, 0x40000000,
            0x200000000, 0x500000000, 0xa00000000, 0x1400000000,
            0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000,
            0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000,
            0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000,
            0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000,
            0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000
        }
    };

    // clang-format on

    // pre-calculated lookup table for knight attacks
    static constexpr Bitboard KnightAttacks[64] = {
        0x0000000000020400, 0x0000000000050800, 0x00000000000A1100, 0x0000000000142200, 0x0000000000284400,
        0x0000000000508800, 0x0000000000A01000, 0x0000000000402000, 0x0000000002040004, 0x0000000005080008,
        0x000000000A110011, 0x0000000014220022, 0x0000000028440044, 0x0000000050880088, 0x00000000A0100010,
        0x0000000040200020, 0x0000000204000402, 0x0000000508000805, 0x0000000A1100110A, 0x0000001422002214,
        0x0000002844004428, 0x0000005088008850, 0x000000A0100010A0, 0x0000004020002040, 0x0000020400040200,
        0x0000050800080500, 0x00000A1100110A00, 0x0000142200221400, 0x0000284400442800, 0x0000508800885000,
        0x0000A0100010A000, 0x0000402000204000, 0x0002040004020000, 0x0005080008050000, 0x000A1100110A0000,
        0x0014220022140000, 0x0028440044280000, 0x0050880088500000, 0x00A0100010A00000, 0x0040200020400000,
        0x0204000402000000, 0x0508000805000000, 0x0A1100110A000000, 0x1422002214000000, 0x2844004428000000,
        0x5088008850000000, 0xA0100010A0000000, 0x4020002040000000, 0x0400040200000000, 0x0800080500000000,
        0x1100110A00000000, 0x2200221400000000, 0x4400442800000000, 0x8800885000000000, 0x100010A000000000,
        0x2000204000000000, 0x0004020000000000, 0x0008050000000000, 0x00110A0000000000, 0x0022140000000000,
        0x0044280000000000, 0x0088500000000000, 0x0010A00000000000, 0x0020400000000000};

    // pre-calculated lookup table for king attacks
    static constexpr Bitboard KingAttacks[64] = {
        0x0000000000000302, 0x0000000000000705, 0x0000000000000E0A, 0x0000000000001C14, 0x0000000000003828,
        0x0000000000007050, 0x000000000000E0A0, 0x000000000000C040, 0x0000000000030203, 0x0000000000070507,
        0x00000000000E0A0E, 0x00000000001C141C, 0x0000000000382838, 0x0000000000705070, 0x0000000000E0A0E0,
        0x0000000000C040C0, 0x0000000003020300, 0x0000000007050700, 0x000000000E0A0E00, 0x000000001C141C00,
        0x0000000038283800, 0x0000000070507000, 0x00000000E0A0E000, 0x00000000C040C000, 0x0000000302030000,
        0x0000000705070000, 0x0000000E0A0E0000, 0x0000001C141C0000, 0x0000003828380000, 0x0000007050700000,
        0x000000E0A0E00000, 0x000000C040C00000, 0x0000030203000000, 0x0000070507000000, 0x00000E0A0E000000,
        0x00001C141C000000, 0x0000382838000000, 0x0000705070000000, 0x0000E0A0E0000000, 0x0000C040C0000000,
        0x0003020300000000, 0x0007050700000000, 0x000E0A0E00000000, 0x001C141C00000000, 0x0038283800000000,
        0x0070507000000000, 0x00E0A0E000000000, 0x00C040C000000000, 0x0302030000000000, 0x0705070000000000,
        0x0E0A0E0000000000, 0x1C141C0000000000, 0x3828380000000000, 0x7050700000000000, 0xE0A0E00000000000,
        0xC040C00000000000, 0x0203000000000000, 0x0507000000000000, 0x0A0E000000000000, 0x141C000000000000,
        0x2838000000000000, 0x5070000000000000, 0xA0E0000000000000, 0x40C0000000000000};

    static constexpr U64 RookMagics[64] = {
        0x8a80104000800020ULL, 0x140002000100040ULL,  0x2801880a0017001ULL,  0x100081001000420ULL,
        0x200020010080420ULL,  0x3001c0002010008ULL,  0x8480008002000100ULL, 0x2080088004402900ULL,
        0x800098204000ULL,     0x2024401000200040ULL, 0x100802000801000ULL,  0x120800800801000ULL,
        0x208808088000400ULL,  0x2802200800400ULL,    0x2200800100020080ULL, 0x801000060821100ULL,
        0x80044006422000ULL,   0x100808020004000ULL,  0x12108a0010204200ULL, 0x140848010000802ULL,
        0x481828014002800ULL,  0x8094004002004100ULL, 0x4010040010010802ULL, 0x20008806104ULL,
        0x100400080208000ULL,  0x2040002120081000ULL, 0x21200680100081ULL,   0x20100080080080ULL,
        0x2000a00200410ULL,    0x20080800400ULL,      0x80088400100102ULL,   0x80004600042881ULL,
        0x4040008040800020ULL, 0x440003000200801ULL,  0x4200011004500ULL,    0x188020010100100ULL,
        0x14800401802800ULL,   0x2080040080800200ULL, 0x124080204001001ULL,  0x200046502000484ULL,
        0x480400080088020ULL,  0x1000422010034000ULL, 0x30200100110040ULL,   0x100021010009ULL,
        0x2002080100110004ULL, 0x202008004008002ULL,  0x20020004010100ULL,   0x2048440040820001ULL,
        0x101002200408200ULL,  0x40802000401080ULL,   0x4008142004410100ULL, 0x2060820c0120200ULL,
        0x1001004080100ULL,    0x20c020080040080ULL,  0x2935610830022400ULL, 0x44440041009200ULL,
        0x280001040802101ULL,  0x2100190040002085ULL, 0x80c0084100102001ULL, 0x4024081001000421ULL,
        0x20030a0244872ULL,    0x12001008414402ULL,   0x2006104900a0804ULL,  0x1004081002402ULL};

    static constexpr U64 BishopMagics[64] = {
        0x40040844404084ULL,   0x2004208a004208ULL,   0x10190041080202ULL,   0x108060845042010ULL,
        0x581104180800210ULL,  0x2112080446200010ULL, 0x1080820820060210ULL, 0x3c0808410220200ULL,
        0x4050404440404ULL,    0x21001420088ULL,      0x24d0080801082102ULL, 0x1020a0a020400ULL,
        0x40308200402ULL,      0x4011002100800ULL,    0x401484104104005ULL,  0x801010402020200ULL,
        0x400210c3880100ULL,   0x404022024108200ULL,  0x810018200204102ULL,  0x4002801a02003ULL,
        0x85040820080400ULL,   0x810102c808880400ULL, 0xe900410884800ULL,    0x8002020480840102ULL,
        0x220200865090201ULL,  0x2010100a02021202ULL, 0x152048408022401ULL,  0x20080002081110ULL,
        0x4001001021004000ULL, 0x800040400a011002ULL, 0xe4004081011002ULL,   0x1c004001012080ULL,
        0x8004200962a00220ULL, 0x8422100208500202ULL, 0x2000402200300c08ULL, 0x8646020080080080ULL,
        0x80020a0200100808ULL, 0x2010004880111000ULL, 0x623000a080011400ULL, 0x42008c0340209202ULL,
        0x209188240001000ULL,  0x400408a884001800ULL, 0x110400a6080400ULL,   0x1840060a44020800ULL,
        0x90080104000041ULL,   0x201011000808101ULL,  0x1a2208080504f080ULL, 0x8012020600211212ULL,
        0x500861011240000ULL,  0x180806108200800ULL,  0x4000020e01040044ULL, 0x300000261044000aULL,
        0x802241102020002ULL,  0x20906061210001ULL,   0x5a84841004010310ULL, 0x4010801011c04ULL,
        0xa010109502200ULL,    0x4a02012000ULL,       0x500201010098b028ULL, 0x8040002811040900ULL,
        0x28000010020204ULL,   0x6000020202d0240ULL,  0x8918844842082200ULL, 0x4010011029020020ULL};

    static inline Bitboard RookAttacks[0x19000]  = {};
    static inline Bitboard BishopAttacks[0x1480] = {};

    static inline Magic RookTable[64]   = {};
    static inline Magic BishopTable[64] = {};

   public:
    static constexpr Bitboard MASK_RANK[8] = {0xff,         0xff00,         0xff0000,         0xff000000,
                                              0xff00000000, 0xff0000000000, 0xff000000000000, 0xff00000000000000};

    static constexpr Bitboard MASK_FILE[8] = {
        0x101010101010101,  0x202020202020202,  0x404040404040404,  0x808080808080808,
        0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080,
    };

    /**
     * @brief  Shifts a bitboard in a given direction
     * @tparam direction
     * @param b
     * @return
     */
    template <Direction direction>
    [[nodiscard]] static constexpr Bitboard shift(const Bitboard b);

    /**
     * @brief
     * @tparam c
     * @param pawns
     * @return
     */
    template <Color::underlying c>
    [[nodiscard]] static Bitboard pawnLeftAttacks(const Bitboard pawns);

    /**
     * @brief Generate the right side pawn attacks.
     * @tparam c
     * @param pawns
     * @return
     */
    template <Color::underlying c>
    [[nodiscard]] static Bitboard pawnRightAttacks(const Bitboard pawns);

    /**
     * @brief Returns the pawn attacks for a given color and square
     * @param c
     * @param sq
     * @return
     */
    [[nodiscard]] static Bitboard pawn(Color c, Square sq) noexcept;

    /**
     * @brief Returns the knight attacks for a given square
     * @param sq
     * @return
     */
    [[nodiscard]] static Bitboard knight(Square sq) noexcept;

    /**
     * @brief Returns the bishop attacks for a given square
     * @param sq
     * @param occupied
     * @return
     */
    [[nodiscard]] static Bitboard bishop(Square sq, Bitboard occupied) noexcept;

    /**
     * @brief Returns the rook attacks for a given square
     * @param sq
     * @param occupied
     * @return
     */
    [[nodiscard]] static Bitboard rook(Square sq, Bitboard occupied) noexcept;

    /**
     * @brief Returns the queen attacks for a given square
     * @param sq
     * @param occupied
     * @return
     */
    [[nodiscard]] static Bitboard queen(Square sq, Bitboard occupied) noexcept;

    /**
     * @brief Returns the king attacks for a given square
     * @param sq
     * @return
     */
    [[nodiscard]] static Bitboard king(Square sq) noexcept;

    /**
     * @brief Returns the attacks for a given piece on a given square
     * @param board
     * @param color
     * @param square
     * @return
     */
    [[nodiscard]] static Bitboard attackers(const Board &board, Color color, Square square) noexcept;

    /**
     * @brief [Internal Usage] Initializes the attacks for the bishop and rook. Called once at startup.
     */
    static inline void initAttacks();
};
}  // namespace chess

#include <array>
#include <cctype>
#include <iomanip>
#include <optional>



namespace chess::constants {

constexpr Bitboard DEFAULT_CHECKMASK = Bitboard(0xFFFFFFFFFFFFFFFFull);
constexpr auto STARTPOS              = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
constexpr auto MAX_MOVES             = 256;
}  // namespace chess::constants





namespace chess {

class PieceType {
   public:
    enum class underlying : std::uint8_t {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING,
        NONE,
    };

    constexpr PieceType() : pt(underlying::NONE) {}
    constexpr PieceType(underlying pt) : pt(pt) {}
    constexpr explicit PieceType(std::string_view type) : pt(underlying::NONE) {
        assert(type.size() > 0);

        char c = type[0];

        if (c == 'P' || c == 'p')
            pt = underlying::PAWN;
        else if (c == 'N' || c == 'n')
            pt = underlying::KNIGHT;
        else if (c == 'B' || c == 'b')
            pt = underlying::BISHOP;
        else if (c == 'R' || c == 'r')
            pt = underlying::ROOK;
        else if (c == 'Q' || c == 'q')
            pt = underlying::QUEEN;
        else if (c == 'K' || c == 'k')
            pt = underlying::KING;
        else
            pt = underlying::NONE;
    }

    explicit operator std::string() const {
        if (pt == underlying::NONE) return " ";
        constexpr static const char* pieceTypeStr[] = {"p", "n", "b", "r", "q", "k"};
        return pieceTypeStr[static_cast<int>(pt)];
    }

    constexpr bool operator==(const PieceType& rhs) const noexcept { return pt == rhs.pt; }
    constexpr bool operator!=(const PieceType& rhs) const noexcept { return pt != rhs.pt; }

    constexpr operator int() const noexcept { return static_cast<int>(pt); }

    [[nodiscard]] constexpr underlying internal() const noexcept { return pt; }

    static constexpr underlying PAWN   = underlying::PAWN;
    static constexpr underlying KNIGHT = underlying::KNIGHT;
    static constexpr underlying BISHOP = underlying::BISHOP;
    static constexpr underlying ROOK   = underlying::ROOK;
    static constexpr underlying QUEEN  = underlying::QUEEN;
    static constexpr underlying KING   = underlying::KING;
    static constexpr underlying NONE   = underlying::NONE;

   private:
    underlying pt;
};

inline std::ostream& operator<<(std::ostream& os, const PieceType& pt) {
    os << static_cast<std::string>(pt);
    return os;
}

class Piece {
   public:
    enum class underlying : std::uint8_t {
        WHITEPAWN,
        WHITEKNIGHT,
        WHITEBISHOP,
        WHITEROOK,
        WHITEQUEEN,
        WHITEKING,
        BLACKPAWN,
        BLACKKNIGHT,
        BLACKBISHOP,
        BLACKROOK,
        BLACKQUEEN,
        BLACKKING,
        NONE
    };

    constexpr Piece() : piece(underlying::NONE) {}
    constexpr Piece(underlying piece) : piece(piece) {}
    constexpr Piece(PieceType type, Color color)
        : piece(color == Color::NONE      ? Piece::NONE
                : type == PieceType::NONE ? Piece::NONE
                                          : static_cast<underlying>(static_cast<int>(color.internal()) * 6 + type)) {}
    constexpr Piece(Color color, PieceType type)
        : piece(color == Color::NONE      ? Piece::NONE
                : type == PieceType::NONE ? Piece::NONE
                                          : static_cast<underlying>(static_cast<int>(color.internal()) * 6 + type)) {}
    constexpr Piece(std::string_view p) : piece(underlying::NONE) { piece = convertCharToUnderlying(p[0]); }

    constexpr bool operator<(const Piece& rhs) const noexcept { return piece < rhs.piece; }
    constexpr bool operator>(const Piece& rhs) const noexcept { return piece > rhs.piece; }
    constexpr bool operator==(const Piece& rhs) const noexcept { return piece == rhs.piece; }
    constexpr bool operator!=(const Piece& rhs) const noexcept { return piece != rhs.piece; }

    constexpr bool operator==(const underlying& rhs) const noexcept { return piece == rhs; }
    constexpr bool operator!=(const underlying& rhs) const noexcept { return piece != rhs; }

    constexpr bool operator==(const PieceType& rhs) const noexcept { return type() == rhs; }
    constexpr bool operator!=(const PieceType& rhs) const noexcept { return type() != rhs; }

    explicit operator std::string() const {
        constexpr static const char* pieceStr[] = {"P", "N", "B", "R", "Q", "K",  //
                                                   "p", "n", "b", "r", "q", "k"};
        if (piece == NONE) return ".";
        return pieceStr[static_cast<int>(piece)];
    }

    constexpr operator int() const noexcept { return static_cast<int>(piece); }

    [[nodiscard]] constexpr PieceType type() const noexcept {
        if (piece == NONE) return PieceType::NONE;
        // return static_cast<PieceType::underlying>(int(piece) % 6);
        return static_cast<PieceType::underlying>(static_cast<int>(piece) > 5 ? static_cast<int>(piece) - 6
                                                                              : static_cast<int>(piece));
    }

    [[nodiscard]] constexpr Color color() const noexcept {
        if (piece == NONE) return Color::NONE;
        return static_cast<Color>(static_cast<int>(piece) / 6);
    }

    [[nodiscard]] constexpr underlying internal() const noexcept { return piece; }

    static constexpr underlying NONE        = underlying::NONE;
    static constexpr underlying WHITEPAWN   = underlying::WHITEPAWN;
    static constexpr underlying WHITEKNIGHT = underlying::WHITEKNIGHT;
    static constexpr underlying WHITEBISHOP = underlying::WHITEBISHOP;
    static constexpr underlying WHITEROOK   = underlying::WHITEROOK;
    static constexpr underlying WHITEQUEEN  = underlying::WHITEQUEEN;
    static constexpr underlying WHITEKING   = underlying::WHITEKING;
    static constexpr underlying BLACKPAWN   = underlying::BLACKPAWN;
    static constexpr underlying BLACKKNIGHT = underlying::BLACKKNIGHT;
    static constexpr underlying BLACKBISHOP = underlying::BLACKBISHOP;
    static constexpr underlying BLACKROOK   = underlying::BLACKROOK;
    static constexpr underlying BLACKQUEEN  = underlying::BLACKQUEEN;
    static constexpr underlying BLACKKING   = underlying::BLACKKING;

   private:
    underlying piece;

    [[nodiscard]] constexpr static underlying convertCharToUnderlying(char c) {
        switch (c) {
            case 'P':
                return WHITEPAWN;
            case 'N':
                return WHITEKNIGHT;
            case 'B':
                return WHITEBISHOP;
            case 'R':
                return WHITEROOK;
            case 'Q':
                return WHITEQUEEN;
            case 'K':
                return WHITEKING;
            case 'p':
                return BLACKPAWN;
            case 'n':
                return BLACKKNIGHT;
            case 'b':
                return BLACKBISHOP;
            case 'r':
                return BLACKROOK;
            case 'q':
                return BLACKQUEEN;
            case 'k':
                return BLACKKING;
            default:
                return NONE;
        }
    }
};
}  // namespace chess

namespace chess {

class Move {
   public:
    Move() = default;
    constexpr Move(std::uint16_t move) : move_(move), score_(0) {}

    /**
     * @brief Creates a move from a source and target square.
     * @tparam MoveType
     * @param source
     * @param target
     * @param pt leave this empty if it is not a promotion move, otherwise pass the piece type of the new piece.
     * @return
     */
    template <std::uint16_t MoveType = 0>
    [[nodiscard]] static constexpr Move make(Square source, Square target, PieceType pt = PieceType::KNIGHT) noexcept {
        assert(pt >= PieceType(PieceType::KNIGHT) && pt <= PieceType(PieceType::QUEEN));

        std::uint16_t bits_promotion = static_cast<std::uint16_t>(pt - PieceType(PieceType::KNIGHT));

        return Move(MoveType + (bits_promotion << 12) + (source.index() << 6) + target.index());
    }

    /**
     * @brief Get the source square of the move.
     * @return
     */
    [[nodiscard]] constexpr Square from() const noexcept { return static_cast<Square>((move_ >> 6) & 0x3F); }

    /**
     * @brief Get the target square of the move.
     * @return
     */
    [[nodiscard]] constexpr Square to() const noexcept { return static_cast<Square>(move_ & 0x3F); }

    /**
     * @brief Get the type of the move. Can be NORMAL, PROMOTION, ENPASSANT or CASTLING.
     * @return
     */
    [[nodiscard]] constexpr std::uint16_t typeOf() const noexcept {
        return static_cast<std::uint16_t>(move_ & (3 << 14));
    }

    /**
     * @brief Get the promotion piece of the move, should only be used if typeOf() returns PROMOTION.
     * @return
     */
    [[nodiscard]] constexpr PieceType promotionType() const noexcept {
        return static_cast<PieceType::underlying>(((move_ >> 12) & 3) + PieceType(PieceType::KNIGHT));
    }

    /**
     * @brief Set the score for a move. Useful if you later want to sort the moves.
     * @param score
     */
    constexpr void setScore(std::int16_t score) noexcept { score_ = score; }

    [[nodiscard]] constexpr std::uint16_t move() const noexcept { return move_; }
    [[nodiscard]] constexpr std::int16_t score() const noexcept { return score_; }

    constexpr bool operator==(const Move &rhs) const noexcept { return move_ == rhs.move_; }
    constexpr bool operator!=(const Move &rhs) const noexcept { return move_ != rhs.move_; }

    static constexpr std::uint16_t NO_MOVE   = 0;
    static constexpr std::uint16_t NULL_MOVE = 65;
    static constexpr std::uint16_t NORMAL    = 0;
    static constexpr std::uint16_t PROMOTION = 1 << 14;
    static constexpr std::uint16_t ENPASSANT = 2 << 14;
    static constexpr std::uint16_t CASTLING  = 3 << 14;

   private:
    std::uint16_t move_;
    std::int16_t score_;
};

inline std::ostream &operator<<(std::ostream &os, const Move &move) {
    Square from_sq = move.from();
    Square to_sq   = move.to();

    os << from_sq << to_sq;

    if (move.typeOf() == Move::PROMOTION) {
        os << static_cast<std::string>(move.promotionType());
    }

    return os;
}
}  // namespace chess



#include <cstddef>
#include <iterator>
#include <stdexcept>


namespace chess {
class Movelist {
   public:
    using value_type      = Move;
    using size_type       = int;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;

    using iterator       = value_type*;
    using const_iterator = const value_type*;

    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Element access

    [[nodiscard]] constexpr reference at(size_type pos) {
#ifndef CHESS_NO_EXCEPTIONS
        if (pos >= size_) {
            throw std::out_of_range("Movelist::at: pos (which is " + std::to_string(pos) + ") >= size (which is " +
                                    std::to_string(size_) + ")");
        }
#endif
        return moves_[pos];
    }

    [[nodiscard]] constexpr const_reference at(size_type pos) const {
#ifndef CHESS_NO_EXCEPTIONS
        if (pos >= size_) {
            throw std::out_of_range("Movelist::at: pos (which is " + std::to_string(pos) + ") >= size (which is " +
                                    std::to_string(size_) + ")");
        }
#endif
        return moves_[pos];
    }

    [[nodiscard]] constexpr reference operator[](size_type pos) noexcept { return moves_[pos]; }
    [[nodiscard]] constexpr const_reference operator[](size_type pos) const noexcept { return moves_[pos]; }

    [[nodiscard]] constexpr reference front() noexcept { return moves_[0]; }
    [[nodiscard]] constexpr const_reference front() const noexcept { return moves_[0]; }

    [[nodiscard]] constexpr reference back() noexcept { return moves_[size_ - 1]; }
    [[nodiscard]] constexpr const_reference back() const noexcept { return moves_[size_ - 1]; }

    // Iterators

    [[nodiscard]] constexpr iterator begin() noexcept { return &moves_[0]; }
    [[nodiscard]] constexpr const_iterator begin() const noexcept { return &moves_[0]; }

    [[nodiscard]] constexpr iterator end() noexcept { return &moves_[0] + size_; }
    [[nodiscard]] constexpr const_iterator end() const noexcept { return &moves_[0] + size_; }

    // Capacity

    /**
     * @brief Checks if the movelist is empty.
     * @return
     */
    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }

    /**
     * @brief Return the number of moves in the movelist.
     * @return
     */
    [[nodiscard]] constexpr size_type size() const noexcept { return size_; }

    // Modifiers

    /**
     * @brief Clears the movelist.
     */
    constexpr void clear() noexcept { size_ = 0; }

    /**
     * @brief Add a move to the end of the movelist.
     * @param move
     */
    constexpr void add(const_reference move) noexcept {
        assert(size_ < constants::MAX_MOVES);
        moves_[size_++] = move;
    }

    /**
     * @brief Add a move to the end of the movelist.
     * @param move
     */
    constexpr void add(value_type&& move) noexcept {
        assert(size_ < constants::MAX_MOVES);
        moves_[size_++] = move;
    }

    // Other

    /**
     * @brief Checks if a move is in the movelist, returns the index of the move if it is found, otherwise -1.
     * @param move
     * @return
     */
    [[nodiscard]] [[deprecated("Use std::find() instead.")]] constexpr size_type find(value_type move) const noexcept {
        for (size_type i = 0; i < size_; ++i) {
            if (moves_[i] == move) {
                return i;
            }
        }

        return -1;
    }

   private:
    std::array<value_type, constants::MAX_MOVES> moves_;
    size_type size_ = 0;
};
}  // namespace chess

namespace chess {
enum PieceGenType {
    PAWN   = 1,
    KNIGHT = 2,
    BISHOP = 4,
    ROOK   = 8,
    QUEEN  = 16,
    KING   = 32,
};

class Board;

class movegen {
   public:
    enum class MoveGenType : std::uint8_t { ALL, CAPTURE, QUIET };

    /**
     * @brief Generates all legal moves for a position.
     * @tparam mt
     * @param movelist
     * @param board
     * @param pieces
     */
    template <MoveGenType mt = MoveGenType::ALL>
    void static legalmoves(Movelist &movelist, const Board &board,
                           int pieces = PieceGenType::PAWN | PieceGenType::KNIGHT | PieceGenType::BISHOP |
                                        PieceGenType::ROOK | PieceGenType::QUEEN | PieceGenType::KING);

   private:
    static auto init_squares_between();
    static const std::array<std::array<Bitboard, 64>, 64> SQUARES_BETWEEN_BB;

    // Generate the checkmask. Returns a bitboard where the attacker path between the king and enemy piece is set.
    template <Color::underlying c>
    [[nodiscard]] static std::pair<Bitboard, int> checkMask(const Board &board, Square sq);

    // Generate the pin mask for horizontal and vertical pins. Returns a bitboard where the ray between the king and the
    // pinner is set.
    template <Color::underlying c>
    [[nodiscard]] static Bitboard pinMaskRooks(const Board &board, Square sq, Bitboard occ_enemy, Bitboard occ_us);

    // Generate the pin mask for diagonal pins. Returns a bitboard where the ray between the king and the pinner is set.
    template <Color::underlying c>
    [[nodiscard]] static Bitboard pinMaskBishops(const Board &board, Square sq, Bitboard occ_enemy, Bitboard occ_us);

    // Returns the squares that are attacked by the enemy
    template <Color::underlying c>
    [[nodiscard]] static Bitboard seenSquares(const Board &board, Bitboard enemy_empty);

    // Generate pawn moves.
    template <Color::underlying c, MoveGenType mt>
    static void generatePawnMoves(const Board &board, Movelist &moves, Bitboard pin_d, Bitboard pin_hv,
                                  Bitboard checkmask, Bitboard occ_enemy);

    [[nodiscard]] static std::array<Move, 2> generateEPMove(const Board &board, Bitboard checkmask, Bitboard pin_d,
                                                            Bitboard pawns_lr, Square ep, Color c);

    [[nodiscard]] static Bitboard generateKnightMoves(Square sq);

    [[nodiscard]] static Bitboard generateBishopMoves(Square sq, Bitboard pin_d, Bitboard occ_all);

    [[nodiscard]] static Bitboard generateRookMoves(Square sq, Bitboard pin_hv, Bitboard occ_all);

    [[nodiscard]] static Bitboard generateQueenMoves(Square sq, Bitboard pin_d, Bitboard pin_hv, Bitboard occ_all);

    [[nodiscard]] static Bitboard generateKingMoves(Square sq, Bitboard seen, Bitboard movable_square);

    template <Color::underlying c, MoveGenType mt>
    [[nodiscard]] static Bitboard generateCastleMoves(const Board &board, Square sq, Bitboard seen, Bitboard pinHV);

    template <typename T>
    static void whileBitboardAdd(Movelist &movelist, Bitboard mask, T func);

    template <Color::underlying c, MoveGenType mt>
    static void legalmoves(Movelist &movelist, const Board &board, int pieces);

    template <Color::underlying c>
    static bool isEpSquareValid(const Board &board, Square ep);

    friend class Board;
};

}  // namespace chess



namespace chess {
class Zobrist {
    using U64                               = std::uint64_t;
    using U128                              = __uint128_t;
    static constexpr U128 RANDOM_ARRAY[781] = {
        (U128(0x3797a0abc005e436) << 64) | 0x4f8df6eea13920bd, (U128(0x2796fb714ce2d11f) << 64) | 0xc1852bfa866ffff3,
        (U128(0x324b8fc0ae2786a1) << 64) | 0xbf1ab77d421965eb, (U128(0x650c52cf897937d3) << 64) | 0x2cbb0475ddfb08ef,
        (U128(0xee11b4caea6c1736) << 64) | 0x3daabe1a8b9631ef, (U128(0x9a2745274a04b7e3) << 64) | 0x7e02b0033b37d4ce,
        (U128(0xc0faed14ba013d1f) << 64) | 0xe648906feb4ace3b, (U128(0x358dd83aea505c34) << 64) | 0x63601e81c3e16391,
        (U128(0x45afd5838afd45d4) << 64) | 0xfa238e0c29936b17, (U128(0x6c3080312ec802e1) << 64) | 0x5fb35a37080b76e8,
        (U128(0xea13514509bf8b95) << 64) | 0x1d83092c523a7042, (U128(0x1177212fde58d502) << 64) | 0x2fe1f27073491e35,
        (U128(0x3fdd782c52b6c077) << 64) | 0xb6138808c1ad13bd, (U128(0x451daef8f631e217) << 64) | 0x20079111d2b70885,
        (U128(0xc7856e0a9fef42cf) << 64) | 0x3c96f11139c93238, (U128(0x435acd3dd63475b3) << 64) | 0xaa6c019ee9dfed4e,
        (U128(0x7ef3c9bcd340ccbb) << 64) | 0x661e1a406b35b30a, (U128(0x9236325df5475f6a) << 64) | 0xc594639273ad614b,
        (U128(0x8fc384a3d71efea3) << 64) | 0x030a9e344b529db5, (U128(0xc4a96e1c39c9c7e2) << 64) | 0xd2803749e84b850f,
        (U128(0xb3e76c0b33caef77) << 64) | 0x54f62f996a548d2b, (U128(0x5b5152544be6b132) << 64) | 0xf3b19206d4a8a635,
        (U128(0x83d0fbb3cc7273fd) << 64) | 0x392dc1efe0f23fdc, (U128(0x332bda5373900cb5) << 64) | 0x0cac8f8138cb9b25,
        (U128(0x1b5d79c3a01339c1) << 64) | 0x7466fab980d0a81d, (U128(0x7eecb6d9630e2043) << 64) | 0x8d79f74a3caf05c2,
        (U128(0x43874bf83fb4a694) << 64) | 0xe1198563dd9b8d5f, (U128(0x94291f3590a740d8) << 64) | 0x6846a149520888cb,
        (U128(0x4bb3442f16fcbffe) << 64) | 0x698b3c1067ac546d, (U128(0x0a5031c22db7c010) << 64) | 0xfe8af91ee34b419c,
        (U128(0x5fee5169209c4b80) << 64) | 0x32e9f5f173039f89, (U128(0xa118656645ca4130) << 64) | 0x88dc91d116b650a8,
        (U128(0xb56d6b63940dce1e) << 64) | 0xdc501d4d0a864eb9, (U128(0x0b88c8b844abeb4f) << 64) | 0xff8a2de599667046,
        (U128(0x958d9281d2d04353) << 64) | 0xe503a6d2342aefb8, (U128(0x77198e05fa0033ff) << 64) | 0xb3586285163a348d,
        (U128(0x367c884d3fb76a68) << 64) | 0x19fc4626cb4950c0, (U128(0x4cdac34ea5599194) << 64) | 0xa57975c39a935337,
        (U128(0x88ffb59f5067af5c) << 64) | 0xa66a1ac172fe3040, (U128(0xb0d617d0cfdbe39f) << 64) | 0xfdee1f06683c8326,
        (U128(0x9aef93b5a080d6bd) << 64) | 0xf3c23a192181b947, (U128(0xe277daa205a33f5f) << 64) | 0xd135335f7869020a,
        (U128(0xe95ef06583c4e9f7) << 64) | 0x7d92a19e2d9fcbe6, (U128(0xa85e72710f8c06a3) << 64) | 0xc3164f165bc4063d,
        (U128(0xae93b2d8ad984221) << 64) | 0x625827068b6bc326, (U128(0xbe9b1a286ba5bac8) << 64) | 0x16e2194ece65ad44,
        (U128(0x380d6e5fd3bf3865) << 64) | 0x2f2ea2a9ff471f18, (U128(0xeeb7a720c2308555) << 64) | 0x38fee3aa2ad92439,
        (U128(0xf85e50425ccd60c8) << 64) | 0x40b2cf730160d514, (U128(0x6dd4f37582f56b12) << 64) | 0x586fdb85f8c716c7,
        (U128(0xe74b9681b974c48b) << 64) | 0xa615f50705ebe2cc, (U128(0xa0e367af1cd1a81e) << 64) | 0x65571f42c4e7f31c,
        (U128(0x42bdaefdb7bd7b52) << 64) | 0x0b0badb1c761e3a0, (U128(0x1980d5e4af2c61fc) << 64) | 0xa46dd2e5d745d61a,
        (U128(0x0833866ff935cf0f) << 64) | 0x707cd455310b1b2f, (U128(0x27a9ece088fff537) << 64) | 0xb54c04a8e211a181,
        (U128(0xd27cbd603cdf0913) << 64) | 0xe8177193a257597b, (U128(0xd66dfec76fd3e1e2) << 64) | 0xc6db0bc5256e66d9,
        (U128(0xe59c49955f4610fc) << 64) | 0xa955828cb49c6b83, (U128(0x040d710441628bd7) << 64) | 0x096ab66bdb8a72b5,
        (U128(0x25ba594d3da1818c) << 64) | 0x53982e78aae4b6b5, (U128(0xe49709e32a0c5322) << 64) | 0x1a76df15ada4738b,
        (U128(0xc272e05573be5f1f) << 64) | 0x1d5141a8c3b869a3, (U128(0xb7682c54fe0f6099) << 64) | 0xd86143218dc2daa8,
        (U128(0xbb2f67cc655c79de) << 64) | 0x3017bf268358a8a2, (U128(0x6b09ac8559185051) << 64) | 0xf931f7170d33d0a5,
        (U128(0xb5c78ea01a92abdc) << 64) | 0x7c0eef67546d5598, (U128(0x4708c14805644070) << 64) | 0x5cb5871c42d9acd1,
        (U128(0x85c1d80fb8b5f6a7) << 64) | 0xb235d3df0f900f35, (U128(0x887d9fdaadba51b7) << 64) | 0x2c911c2ae6fc42a3,
        (U128(0xe7b167c464c51d9f) << 64) | 0x32df1682abda17dd, (U128(0xf136721f7ca52ae4) << 64) | 0xe32cbe09ffb7ec63,
        (U128(0xee47760a3eb686c5) << 64) | 0x70c2c193de03bcf6, (U128(0x1316286bee0fc9cc) << 64) | 0x3a91a4c41e2b2326,
        (U128(0x9cf5dd012ed6f05c) << 64) | 0x5123ceca39de3d61, (U128(0x1b9d7a4ad264d5eb) << 64) | 0x000dafc7498e9ac9,
        (U128(0x698a7108fc2774d6) << 64) | 0xdc2be56039ecbc58, (U128(0x98820760bbb949e1) << 64) | 0xcee7d0de0a72132a,
        (U128(0xfc6a148967454fbd) << 64) | 0xd2a2c07491d2d6ad, (U128(0x1472231f3a3342ce) << 64) | 0xb4b3525c92c9797a,
        (U128(0x8d68ac94ff6d34ed) << 64) | 0x60d959b6adccd128, (U128(0x8f25bb43c780da2f) << 64) | 0x019a94b0ca6f59aa,
        (U128(0xf218c4c058293b08) << 64) | 0x61694e9a14011e95, (U128(0x67849c32889782a9) << 64) | 0xb1bc68cfa8abcd91,
        (U128(0xbc518b20e1025109) << 64) | 0x0f7b6b82552bf55e, (U128(0xdf8c82af63c5d79c) << 64) | 0xa3c5f0afc78a3f17,
        (U128(0x5afd7210943708f6) << 64) | 0xfc9e65a506425309, (U128(0x45984483e5225085) << 64) | 0xf9a858f583cb4f34,
        (U128(0xedfd7b7b4f8705d1) << 64) | 0x0c68ae5e596a1b71, (U128(0xdb9d5c9ccd0a9ef0) << 64) | 0x349b9a06ba24e436,
        (U128(0xbe9c73038a967893) << 64) | 0x48966058e03dec9a, (U128(0x1fcc253581a95628) << 64) | 0x5f0a4152f93317a8,
        (U128(0xa264cf12cc37b512) << 64) | 0xf716473d4930fdda, (U128(0x62867854a96dd770) << 64) | 0x5d8f7d4f7575c044,
        (U128(0x0cdeeb98d8144fe1) << 64) | 0xff914d76fa1b4b87, (U128(0xfb89c628d432dfcc) << 64) | 0x6615bb55cbf8dcad,
        (U128(0x90d4b954b0bf1743) << 64) | 0xd17223b065d25270, (U128(0x9a0f859ecc74878f) << 64) | 0x7d46d9101a599b08,
        (U128(0xfddf5494cf5db425) << 64) | 0x1a7505261bb57d8e, (U128(0xa2ddd2d4bf04b6e8) << 64) | 0x02be5346a78e5d30,
        (U128(0x2d1a898c423030d7) << 64) | 0x7502ba0fbac193cd, (U128(0x7ff495b2b2190b71) << 64) | 0xf79c72c5012da88d,
        (U128(0x6d2df099e28b8469) << 64) | 0x644dace1e338a2cf, (U128(0xac81d393a66317f4) << 64) | 0x607142904dea5104,
        (U128(0x85d004a3edbd6680) << 64) | 0x17df8e377df37716, (U128(0xf69b15bfbd97cb52) << 64) | 0x24ca74808f4536e6,
        (U128(0x35ebe9867a75a942) << 64) | 0x5baa684e54f45ba8, (U128(0x735192b532742517) << 64) | 0xf24a50dd4127ca00,
        (U128(0xb7fd40a4964921ab) << 64) | 0xc26cbe9a8248a29e, (U128(0x1cfffff4a1706b5a) << 64) | 0x2bd29606d82f6100,
        (U128(0xab5cdf5cf7d96593) << 64) | 0x3f997b0924514e16, (U128(0xe97e19edf9529209) << 64) | 0xde38299d8dbb85c9,
        (U128(0x524a83c4dcb49684) << 64) | 0x5a69fa9d1da9d764, (U128(0x1d979521f175a35f) << 64) | 0xb28b567db633f043,
        (U128(0xc1e0cd83ff5deab3) << 64) | 0x4ad0da7c84934ed5, (U128(0x51a7e91a959cb519) << 64) | 0x1ae47b64831110cc,
        (U128(0x810a98a8f6f4df4f) << 64) | 0x7e624942e0f31b80, (U128(0x17ba0806e285d7ba) << 64) | 0xc68dde55194fc088,
        (U128(0xa2e44a31b46afdaf) << 64) | 0x10bc3125e6250c70, (U128(0xe911843126eebf47) << 64) | 0x79b830fe5f42910d,
        (U128(0x3f3a50387abe811a) << 64) | 0x1401a599d594839b, (U128(0xdbb33bea4553c066) << 64) | 0x8f41582c927e8c7e,
        (U128(0x58cb9dd6fb2cfae7) << 64) | 0xbddc6c3178b79365, (U128(0x25a6ee6b3e08d809) << 64) | 0x763e1e27b268b588,
        (U128(0x8985c68e45e8980d) << 64) | 0xf0c2385fc653b354, (U128(0x07048e600959568c) << 64) | 0x30c85929e1306bef,
        (U128(0x88b18eec35561fa3) << 64) | 0x38bcb7d61a9b67e2, (U128(0x6e5b330d28a721ba) << 64) | 0xfa179ea6c51971e7,
        (U128(0xf18426787f9b5377) << 64) | 0x6b7a19ce9827eb1f, (U128(0xedcbca74acd20cbb) << 64) | 0x8bdf1fa4e1feaef2,
        (U128(0xace123bc1f2c0ec5) << 64) | 0x8e6a5d4789d74268, (U128(0x4485c018bb380e7e) << 64) | 0x45d2c6a81cadce64,
        (U128(0x1e5d7387b69e275b) << 64) | 0x4d4ec20fcbc57ba3, (U128(0x8bc859af65e533e9) << 64) | 0xa9057a2f4a6d811d,
        (U128(0xfb3f984dc552838e) << 64) | 0xd439f02ff4521c8c, (U128(0xd338a95352976fda) << 64) | 0x71f7ba9866ed2d4a,
        (U128(0xff65e23bcbd77f5a) << 64) | 0xa9bc51f717f33622, (U128(0x8a69a4354d071168) << 64) | 0x0191d7510f811c21,
        (U128(0x13e5345020e7481c) << 64) | 0x7fa75a388a1622f9, (U128(0x8e1e59b193dc0627) << 64) | 0x90b33e5ce25a441c,
        (U128(0x8fb7347b138e0b24) << 64) | 0x377bc7069c8494e7, (U128(0x895da826ee54222f) << 64) | 0xb26a6d8b3557b52c,
        (U128(0x1a5023585b7919be) << 64) | 0x7613c3c439ee094f, (U128(0xcf7bf501bd8e553c) << 64) | 0x601675530edb6c7f,
        (U128(0xd33b90f95e44d1ad) << 64) | 0x69e08b84ff72fa8f, (U128(0x8d52e3feae57474c) << 64) | 0xf00b6654b7fa1602,
        (U128(0x293dd7c1e9bcba19) << 64) | 0x6d0d6372e8337694, (U128(0x4479234de97af7e8) << 64) | 0x9f24d6874ad96f43,
        (U128(0xa36dbac0eb2c1fc0) << 64) | 0x4749e017c8d7cfbd, (U128(0x113c16a52c1797d2) << 64) | 0xff11d9e3b6e50958,
        (U128(0x817b7103f5aa1823) << 64) | 0x90adafa830c777c1, (U128(0x5af96c1aab504300) << 64) | 0xfe6bb2d226b0d106,
        (U128(0x5f78a76354d44f2a) << 64) | 0xcc0b3032722293b5, (U128(0xfdaad79c1744df8f) << 64) | 0x981bb71de3d2a3a0,
        (U128(0x76b1171e6d35227a) << 64) | 0x34e7f5fd09fa7a39, (U128(0x12eb3d9956cd242e) << 64) | 0x63c6cfc1daad41de,
        (U128(0x764457d86262b095) << 64) | 0x76f4960661c60d17, (U128(0x29bfb4160dc308b9) << 64) | 0x66a87122da318d87,
        (U128(0xe66b7813a0a2e207) << 64) | 0xf43751270648db64, (U128(0x2ee900c1f8809134) << 64) | 0x3d89ad665ac6502e,
        (U128(0x328aa9098d7d9882) << 64) | 0x3e7e6e65da0868b6, (U128(0x93ef86b19cb50fe4) << 64) | 0xefd76c2b6f835268,
        (U128(0x9804b960f0143209) << 64) | 0xd1f21c4475e96976, (U128(0x5bbdd5962b9ea5be) << 64) | 0x5175b8d2710e558b,
        (U128(0x7b3acb7ea391a9b8) << 64) | 0x574af72daf5d6b93, (U128(0x0c0c822727d24471) << 64) | 0x82e481a0fddc9612,
        (U128(0xaf032138f2d3f496) << 64) | 0x1a79fde5170fda5e, (U128(0xe287af2468bcf4d4) << 64) | 0xc4f03d132cf4365f,
        (U128(0x47ef82a83a7b1748) << 64) | 0xa2520f6d06377911, (U128(0x7a9d4dcdb714fdc5) << 64) | 0x7d65c0b41053b5d2,
        (U128(0xd0d0dc19e9b88a56) << 64) | 0x2f88be33c8e0efb4, (U128(0x3c5f6f755e9fdc69) << 64) | 0x841ad9fddb6a5f99,
        (U128(0xf307c9ad56f1d686) << 64) | 0x82c92170d20a197c, (U128(0x3dc32312af327907) << 64) | 0x04937e0bd3dd5696,
        (U128(0x96287ff4a2a78228) << 64) | 0x8f2625299ed7bab8, (U128(0xcc3d938d0b705706) << 64) | 0x271f8cf3c2d45c0b,
        (U128(0xa62a6672ad0609cd) << 64) | 0x3f0d5cf4a5e7e6f2, (U128(0x88bff13e06badc18) << 64) | 0x851a6a9f3f8b408e,
        (U128(0x922f06880fafc7c7) << 64) | 0x034d3c98b3dcd9d9, (U128(0x5ead37a4c6c25558) << 64) | 0xb06f01166ad03727,
        (U128(0xff39f573c2172d0d) << 64) | 0x54a01b01378d159b, (U128(0x074ba32d0299e878) << 64) | 0x6cd5ae020ed43d99,
        (U128(0x3bad11cb134942bf) << 64) | 0xb7b551cb2b77e814, (U128(0x54ac12c90af21ea3) << 64) | 0x7cb1a3e2bd319f19,
        (U128(0x4d513365c57aa264) << 64) | 0x497c81e5881e0d9d, (U128(0x4f58e1f67e7e9ce4) << 64) | 0x10efd054e925a24e,
        (U128(0x0b92fc7257d0e33b) << 64) | 0x5de558e5885e4668, (U128(0x70e72233f7e88ea7) << 64) | 0x0f86e707295554fb,
        (U128(0x43bb577366b0b2c0) << 64) | 0x4811a27ac37b1327, (U128(0x2023131e7d78cfaa) << 64) | 0x8768ef544ccd3fe5,
        (U128(0x2d0887d2ccc93e57) << 64) | 0x46638c72ee5ac0b1, (U128(0x318a58533cfb309d) << 64) | 0x100dcda67a441d10,
        (U128(0xf64ef044e15293a0) << 64) | 0x60fd90c27105aec8, (U128(0x75190938ea2b461d) << 64) | 0x62be6ca8ad3ffbd9,
        (U128(0x993a02e6e9861f1e) << 64) | 0xad1050c62570b304, (U128(0xe47c218f2f257fd2) << 64) | 0x48aa827b57cd7d5c,
        (U128(0x77be2421411f243f) << 64) | 0x711c91d09c6df316, (U128(0xa008707b3261c7d1) << 64) | 0xda888bbeb8ad23fa,
        (U128(0x1e3d39dd7f0cfc2b) << 64) | 0x8fc51f48da7d1473, (U128(0xbce3cd0f40ac0054) << 64) | 0x73b7412d09f1625c,
        (U128(0x11471b2c8c0aa12a) << 64) | 0x5809293ec493f2f3, (U128(0x366663084b1898ff) << 64) | 0x5a39fdab93f153b2,
        (U128(0x333cd6d0414975d6) << 64) | 0x547adf023de18c56, (U128(0x9fcfb4e9f77afa1f) << 64) | 0xfda0b1b28de568c2,
        (U128(0x4edc928d064ee4e3) << 64) | 0x89ffddbd0392ebc5, (U128(0x8add9a0d99b5c076) << 64) | 0xd92dff576026bfca,
        (U128(0x1515b6e729f86eb4) << 64) | 0x5c751e68ea511272, (U128(0x70abe4f566f5aaeb) << 64) | 0x41a0aa3431d3213c,
        (U128(0x574fee8283564491) << 64) | 0x70b3d3e61c102135, (U128(0xaa51967f0b266fff) << 64) | 0x55054785d5e5637f,
        (U128(0x5fc9c2770ddcc439) << 64) | 0x5cae6554ef5fde69, (U128(0x3f6fb9d91e1dbf30) << 64) | 0xf76d7a214d27a3b0,
        (U128(0xb304bbaf14922538) << 64) | 0x27bc672931221b33, (U128(0x3fc16be0704de6f4) << 64) | 0x987c7699bad8d1bd,
        (U128(0xcddf2b23e08a57eb) << 64) | 0x50f97521710cb4e7, (U128(0xdc973ebcc3b33def) << 64) | 0xa2d0ee9cec3e217d,
        (U128(0xc0b87aeb5463cbfb) << 64) | 0xfd4b6e340a329847, (U128(0x725408fbadaff26a) << 64) | 0x84d62b31fa5886e1,
        (U128(0x3919a7ef13d90bd1) << 64) | 0x7051bc6cf852f7b4, (U128(0x2f851b13a4c9d714) << 64) | 0xc25200dc56c6eb55,
        (U128(0x005cf1e7f4e93b00) << 64) | 0xbd9f65731a11ce13, (U128(0x7e05c32c3458e70c) << 64) | 0x21cf5aad15bc77fd,
        (U128(0x5b87fbc64bf4c338) << 64) | 0x74aa8f5aef52fbff, (U128(0x8e8dd9a0b350bba0) << 64) | 0x9661a56e8988e808,
        (U128(0x1a5e0685f89ffd94) << 64) | 0x73ac3ed51303768f, (U128(0x05f313a627d21505) << 64) | 0x1487e092975bc828,
        (U128(0xeb6dba59e3c019c7) << 64) | 0xc3074b160a02a87e, (U128(0xe3131cf50c0a0dcf) << 64) | 0xe1cb43ecffd12c8d,
        (U128(0x3e314c6db88aac4d) << 64) | 0xd0f1360fc9a9ec80, (U128(0x4e60f8bba577e3e6) << 64) | 0x4b80cc74e2342136,
        (U128(0x2fc2fa28fc86e35d) << 64) | 0x8dc3540fefc0891e, (U128(0x85523c3bea4a02b3) << 64) | 0x907e77eef9339e4e,
        (U128(0x4223ba58f2b52453) << 64) | 0xa40b59bed6fa413f, (U128(0x5869e1134eeb1ce2) << 64) | 0xf50418c3fb9fe5a3,
        (U128(0x7805e0821b6c84c3) << 64) | 0x4396aa2c5759c428, (U128(0x85c7904680ce31f1) << 64) | 0x35f3aab8901d2ebd,
        (U128(0x82a33441c8d5f114) << 64) | 0xcf339f3fb223c145, (U128(0x4b6431362ff12d84) << 64) | 0x7b13f2223427a982,
        (U128(0x50fe49eb95a33f7d) << 64) | 0x7b50f542c4411f47, (U128(0x8b11679b372304c1) << 64) | 0xb10c4e21d4dc9608,
        (U128(0x0aebe253a83e27be) << 64) | 0x8ef17b47bb933304, (U128(0x412f7009c6b61a3a) << 64) | 0xe52ce1ce55e17f6d,
        (U128(0x04c7766404c09dce) << 64) | 0xbf1cb3c8aa4af33c, (U128(0xcfa5d65b076f8cff) << 64) | 0xbb6d68fb684c6300,
        (U128(0x21a196477b9f54a6) << 64) | 0x53a720ac3e91ece0, (U128(0x3bcecd2ffd33f12c) << 64) | 0x3feb9ecf74fc2ed1,
        (U128(0xa1703e89b94e3217) << 64) | 0x547b30380b391d77, (U128(0x35931cae259fa514) << 64) | 0x584db0d755d5529e,
        (U128(0x540ef80fa27f9ae2) << 64) | 0x228a04876820d2d1, (U128(0x9225fb9606b8e143) << 64) | 0xa419c1eee93edbed,
        (U128(0xfb7d12276ead7242) << 64) | 0x620a21e72f853766, (U128(0x00bf0c0224b4e160) << 64) | 0x461d7198f7997645,
        (U128(0xc9899869eeb3c085) << 64) | 0xee665e7dc9aad0cd, (U128(0x013dc8ef2c93536d) << 64) | 0xae79612f4217ce72,
        (U128(0x0a460ed46e15aecd) << 64) | 0x7a9b6a968949871a, (U128(0x5c39019933a62203) << 64) | 0xc5bcf653e4227405,
        (U128(0x565e33a3cb217453) << 64) | 0x1c7fe6c45250be7a, (U128(0x635f02d9cd518d87) << 64) | 0x276345cbe902bf24,
        (U128(0xae5e414f20bee7d7) << 64) | 0x140094d5cd437e0c, (U128(0x71cefb7dd0bdcbe0) << 64) | 0x46f3f20e4cfe802c,
        (U128(0xb76d21a145d5100d) << 64) | 0x5040f1af2642e7e3, (U128(0x1c6382d17d0f2e35) << 64) | 0x7bfff11d5ceb6fe8,
        (U128(0x1160f1da03ad772f) << 64) | 0xbe5d92eafb53e19a, (U128(0x9d419f578910bbdf) << 64) | 0x2327cd0f9d04fc9a,
        (U128(0xfa5806abf084d3da) << 64) | 0x3ac513bbc83b3a5b, (U128(0xd90a560c88ea35ce) << 64) | 0xcd28e244141b6d7c,
        (U128(0x354b327f79304deb) << 64) | 0xc5561c5889b8d31d, (U128(0x968a7cdcc48a99fe) << 64) | 0x5d5d663e70e4458f,
        (U128(0xfa774388923859ee) << 64) | 0x0a47a2b2abad6f9b, (U128(0x67b0d816f26673d5) << 64) | 0x9a42898d06991286,
        (U128(0xbf841f41a96f6c76) << 64) | 0x5e458b8ddb81e74b, (U128(0xf1fadad2d3e2aed5) << 64) | 0x262133feacb4219c,
        (U128(0xe4de81184ec07edc) << 64) | 0x6d855b9b400dc9c6, (U128(0xbf66511233df38c6) << 64) | 0x1a474b3f3842d50d,
        (U128(0x22e1427fbf062aeb) << 64) | 0x59907f3624c05931, (U128(0xd0ce79610aae4978) << 64) | 0x003b6957d5b3a65c,
        (U128(0x17a4814e59f754f4) << 64) | 0x13862d149756c191, (U128(0xfada0fc9f2d1df0e) << 64) | 0x8e2354e2368f5200,
        (U128(0x4108d860856c944d) << 64) | 0x99f7a7716ae7ed0d, (U128(0xa639128430acd20d) << 64) | 0x71a8e6aac19a1e8b,
        (U128(0x03e313a6cc1622b1) << 64) | 0x944c5e5535d9b677, (U128(0x6c87177dd149ee99) << 64) | 0x2757548b8c844f52,
        (U128(0x68b618c3d0b1c096) << 64) | 0x328c24a987481194, (U128(0xffa25ad3d0a62426) << 64) | 0xb3ea098d0f635597,
        (U128(0xc74070759ac72bcc) << 64) | 0x4ce66ab51e6decc4, (U128(0xec52b7e19ab20907) << 64) | 0xf99d3b469d5f1a44,
        (U128(0x5efd303663bc83c7) << 64) | 0x773547381a02f23a, (U128(0x76874d8a813b8003) << 64) | 0x81b1150116af6c3a,
        (U128(0xd29de8653bff78d1) << 64) | 0x2aba0af122fbb3a8, (U128(0x6a0ab50adf5700a2) << 64) | 0x70e660c628d0cb3f,
        (U128(0x9f94a56a44b1c0ad) << 64) | 0xed9e59d2d5af4f70, (U128(0x3a19e85319012604) << 64) | 0x81e0621f0273a52e,
        (U128(0x7056fb3178a0ec27) << 64) | 0x92d6da604a03ec88, (U128(0xb9a197ddbc412427) << 64) | 0xd6518aa80341ffb0,
        (U128(0x9311c11f34216bba) << 64) | 0x3803a12aef742193, (U128(0x93587ac371b1a46a) << 64) | 0x197939234218bf61,
        (U128(0x8c190bd303a87eb7) << 64) | 0xfa90b4c748a8746d, (U128(0x0004f1c7eaecf663) << 64) | 0xc2fd881af34820e1,
        (U128(0x1f9d39edad3e28eb) << 64) | 0xd608c1a5ff08cd2e, (U128(0xf919513cc03064bf) << 64) | 0x0dc0976187570bb8,
        (U128(0x3f445922525adbb6) << 64) | 0x52ef22c864806afe, (U128(0x4243a132f0c8eac8) << 64) | 0xff0ad7af8ee27a1f,
        (U128(0x9f62dbdb0e134f1f) << 64) | 0x4280837b116b0537, (U128(0xf0ab304cd1108f78) << 64) | 0x80abe27c6d981767,
        (U128(0xcaeda51bf651c193) << 64) | 0x80ce2b4cb567f776, (U128(0xfd6cca48f87f37af) << 64) | 0xd224881639f40dc2,
        (U128(0xfc974777b91d2cb6) << 64) | 0xa1627f18609aa086, (U128(0xaa3f4bf237bd600c) << 64) | 0xf6bdc0e5a3958724,
        (U128(0x45eceb76dc99bb5c) << 64) | 0x710e2988c2949d22, (U128(0xbdbe2932b49bced6) << 64) | 0xac66a89fbf083322,
        (U128(0xaf859d1aab1b4bbf) << 64) | 0xb45684075816449f, (U128(0x939fef90827e0dc2) << 64) | 0x95c198ff16538375,
        (U128(0xd53222e71486d39b) << 64) | 0x20b386c91b80c8c1, (U128(0x09f602ab073fc487) << 64) | 0x25629a67e109cddd,
        (U128(0x4c42ad8ad9451992) << 64) | 0x8febd1feb83d09c0, (U128(0x0e7267dcfde37994) << 64) | 0xcd4e1b6884e560ee,
        (U128(0x312126ff9543d84b) << 64) | 0x750c6a222f20a407, (U128(0x919132f916ed1d2d) << 64) | 0xe43269195b462d01,
        (U128(0x687691b7f85b8c2f) << 64) | 0xfa91dc9d8f88d41c, (U128(0x7b24a1797c0da234) << 64) | 0xf7dc69dfdba45c13,
        (U128(0xb871def2facf5525) << 64) | 0xf3fd30ca61c86442, (U128(0xc29c271a197f37f0) << 64) | 0x92deaccec18b19a4,
        (U128(0x6f80aca2d23dedbd) << 64) | 0xf279c7fb9ee5a283, (U128(0xfa50fe6c3789b84d) << 64) | 0x30afe1780fead469,
        (U128(0xc555dd468a81c6b7) << 64) | 0x8cd7a7cb574ffe4f, (U128(0xee7df2303969827a) << 64) | 0x1a8213c00dee15ee,
        (U128(0x2f614b5b3f64463c) << 64) | 0x8f9e38b7bb828f55, (U128(0xb7464c1f9ae46be1) << 64) | 0x6de3c9326209316a,
        (U128(0xe8e36a8db8c86b28) << 64) | 0xe379daa7893de858, (U128(0xfe059e13a9fd1ce1) << 64) | 0x52a940639307b26c,
        (U128(0x225a960152ba8f93) << 64) | 0x8491155c7cf3bcab, (U128(0xb29a1893e5385601) << 64) | 0x87d27ab32dbaeda6,
        (U128(0x4a97dd1e2d7d1df1) << 64) | 0xfe0b915ed0674c52, (U128(0x7b87a71c1ec8db94) << 64) | 0x7f6d5e0903228dd8,
        (U128(0x74e1b88546824457) << 64) | 0xa1b720c1644015d6, (U128(0xe9cd51ebda909a08) << 64) | 0x31a5b30b84cc82b0,
        (U128(0xebb097fb61251e14) << 64) | 0xa2151867d9e2e3ec, (U128(0x733844d03d1405ed) << 64) | 0x8d15f31edd5bfb4b,
        (U128(0xe37230b9edcc25f6) << 64) | 0x15ec45c61e413814, (U128(0x729239a6050fad95) << 64) | 0x3b8804de5e8fd04e,
        (U128(0xe88c3cbf8516f826) << 64) | 0xb968ee01f7083de8, (U128(0x1bb534019043c1ec) << 64) | 0xdf0407c18e7889e5,
        (U128(0xa55c8e73a45cff29) << 64) | 0xd89ca6621ed71513, (U128(0xee294aee394cb65f) << 64) | 0x2f7dbc198da0e727,
        (U128(0xfe7df22b32e7ba1c) << 64) | 0x6adf630526dcf965, (U128(0x4e8113b15ddcd6f7) << 64) | 0x9946050545da82a7,
        (U128(0xf73ad31cad98e6a6) << 64) | 0x7ebf026341920fa7, (U128(0x64f1658a294a5bcc) << 64) | 0x312e0adbbb1434ab,
        (U128(0xa1cecef979e9cb84) << 64) | 0xf6a8e05d3a9195fd, (U128(0x45dfa73b0397707e) << 64) | 0xf8dda2fa00df3068,
        (U128(0xd9e991a3521b422e) << 64) | 0x96c094b1efbbd993, (U128(0x4c0f77a259860ebb) << 64) | 0xc1601d6e28750c16,
        (U128(0x16476437597c252d) << 64) | 0x11ba3a54ab2fc3f4, (U128(0xde4783d4841319ad) << 64) | 0x0c2d3dfb836c647f,
        (U128(0x4b7f8d6ab3c383d6) << 64) | 0xcbfd229a8e390937, (U128(0x8fcbbdb40d01e191) << 64) | 0xbfaaccf801792a99,
        (U128(0x30b6409db0ba64e3) << 64) | 0x03951d42f35caf11, (U128(0x99e42280bec94a49) << 64) | 0xb5e88b0642d8ba17,
        (U128(0x26e7e1c908bafb43) << 64) | 0xea453fa9d188bc01, (U128(0x13fb152f18fea278) << 64) | 0x35a1a71ae20ed8b5,
        (U128(0xb4bcf421db3ee3fd) << 64) | 0xcb1c720a4a098afc, (U128(0xb138574bfc4a8d26) << 64) | 0xde70c91fa3f85746,
        (U128(0x48f96c3a34299c01) << 64) | 0x7be315adba96be89, (U128(0x9f166215388a4a96) << 64) | 0x459d4af4bf0ae5e5,
        (U128(0x51a8c6271da13ab4) << 64) | 0x8d10b8cce62653a6, (U128(0xf262bf2750862899) << 64) | 0x1f4a25fa2a32726c,
        (U128(0xe809aca4dcdc4fa1) << 64) | 0x26930d3a286b582a, (U128(0xdb891237974d9de0) << 64) | 0x06cd6418b58c5b0c,
        (U128(0xd0113029267cd0df) << 64) | 0xc7b209bf4474aa71, (U128(0x459499a83a517a7e) << 64) | 0xfef30db5bdeca85d,
        (U128(0xbc73cc23359e949b) << 64) | 0xef5f4c72e4537f64, (U128(0x21a1c1536b30b193) << 64) | 0x194ecfd1232c4492,
        (U128(0xbdec34061b8a83c9) << 64) | 0xca0083dd67a515a8, (U128(0x6a72f8d56ed5f7fc) << 64) | 0x73366d1667e46a9a,
        (U128(0x4aff767a0f805ca0) << 64) | 0x50cd37bf73a9558a, (U128(0x6b6c44e35e57fd8f) << 64) | 0xa5446dfb72af23ff,
        (U128(0x9eed930b0a0eb9cb) << 64) | 0x6ba2fd0b471330af, (U128(0xf5ca5c61f8fffc8e) << 64) | 0xa89d303cbdf7bfa7,
        (U128(0x7ccc32f591b4ac83) << 64) | 0xf903e3046027c548, (U128(0x6b3590f0b4a447aa) << 64) | 0xcf2f290af51c3bd9,
        (U128(0x94ba90841c241631) << 64) | 0xa81a32b04734e001, (U128(0x983858640e585268) << 64) | 0x16cef39caf401137,
        (U128(0x3f765b94589b3f48) << 64) | 0x30dcfd4c6161305a, (U128(0x889fdc3a68eb31a8) << 64) | 0x595d9cdd3b031896,
        (U128(0xf5de6234466e89e5) << 64) | 0x31cfec9515c77ae2, (U128(0xe5b6cf37de2eaf26) << 64) | 0x3fa5a36e07bea9dc,
        (U128(0x888251369c608a66) << 64) | 0xf296ac4cb385be57, (U128(0x60e811bb62b72404) << 64) | 0xc29a4a82cb85a668,
        (U128(0xaf843a418015f558) << 64) | 0x871dff7726ed12eb, (U128(0x51c30c1fcb83669f) << 64) | 0xf686f8a38366290d,
        (U128(0x3f30aad773488fe7) << 64) | 0x39c54212f3bbe551, (U128(0x47d9c09a0df7139b) << 64) | 0xab1d07511bd7acbb,
        (U128(0xdf3130dd753ce4e3) << 64) | 0x9dd202083d65afcb, (U128(0x16bbbe1156fc25d6) << 64) | 0xd94e6a7bd857c904,
        (U128(0x8e5a204d1f77d160) << 64) | 0x325aae74716d0902, (U128(0xbef41ea0a720238b) << 64) | 0xd6cfcff258327f00,
        (U128(0xe8607f31dce82f45) << 64) | 0xd921054fe2868220, (U128(0x93095ea71fcba1cf) << 64) | 0xa63d75aef172444c,
        (U128(0xfe28a02cbc53d312) << 64) | 0x22e34bf201f95fb9, (U128(0xa2d14c59155de963) << 64) | 0xd3486d7e7eadf1b7,
        (U128(0xbadbbe13ba8ab911) << 64) | 0x5e013aecffa8f607, (U128(0xceffb6bb1f17de9f) << 64) | 0xa953b688819ffc0f,
        (U128(0x6f972a5aa88be150) << 64) | 0x9df0f9def1251147, (U128(0x3f8db0e8a894e9db) << 64) | 0xb9a909535180ebce,
        (U128(0x595940174fd28d8d) << 64) | 0xe8c08fd025f820bc, (U128(0x37e9776f1db36ba9) << 64) | 0x7ba4a221e4a628aa,
        (U128(0x8b9af8c381c8e90b) << 64) | 0x2b6443bf2a4bf3ad, (U128(0x40796e865c251f86) << 64) | 0xd56226961314f542,
        (U128(0x3a64c05422b199c8) << 64) | 0x567d989181fa46ba, (U128(0x8e7f30d652dbb940) << 64) | 0xd1bf9b79d5b8a24c,
        (U128(0x08a36f5779684834) << 64) | 0xd5398743a9f4a295, (U128(0x9495b65c77060cff) << 64) | 0x39e28eab9b1e183c,
        (U128(0x2d74832941f64568) << 64) | 0x6be55fa5bfdebd81, (U128(0xceee6ab4d4d2f503) << 64) | 0x135487b1297d4078,
        (U128(0x000ba52865fac9a2) << 64) | 0xcd105d4347edaa2d, (U128(0x8a565c134a6e1da5) << 64) | 0xfb20bccbb1f8b41f,
        (U128(0x0d0dc69d53039fac) << 64) | 0xfc8f9291da4376b4, (U128(0xf4a2fcb72d9a9585) << 64) | 0x80743014fcbe25da,
        (U128(0x23d574bd07c860b6) << 64) | 0xa62a8415cefebb8b, (U128(0xd2804fed63b54e63) << 64) | 0xfe7073d3b92e6334,
        (U128(0xc46226c340b2b1eb) << 64) | 0x1f09bd022fb59e7b, (U128(0xe41590d56ef4e857) << 64) | 0xf169777c1efdb530,
        (U128(0x18e9c018a8cb8a12) << 64) | 0xcc676fb27aed9e1c, (U128(0x9f4eaf04e10c0a93) << 64) | 0xea0e237b2a3dcee5,
        (U128(0xa13852b234a2277e) << 64) | 0x53d41f3f181e9b7d, (U128(0x357c2a6cb412e01d) << 64) | 0x36dca2510ebbdc7a,
        (U128(0x18b89c0f39f963aa) << 64) | 0xea67c42544fee838, (U128(0x51a630db5907af28) << 64) | 0x364b2571419f3230,
        (U128(0xe5b4e8abb2a2450d) << 64) | 0xee43ff799d7fa769, (U128(0x778466c275ad29b3) << 64) | 0x9ff9148d0e57a8d6,
        (U128(0xffd4f30d62714e76) << 64) | 0x979683b9963fe134, (U128(0x862aa8b54a4e047f) << 64) | 0xdcb6cc0de456da75,
        (U128(0x4039033df7ff2854) << 64) | 0x18839877e2b7e0f4, (U128(0xb3012ac0565dc458) << 64) | 0xca22149ddd63338e,
        (U128(0x6ad61c8b7eabc761) << 64) | 0x7fb3171f2e584542, (U128(0x285d64007d053acb) << 64) | 0x6106237584d5b111,
        (U128(0x9538de7b2d96883e) << 64) | 0x1b8ddcf325527fb6, (U128(0x023ae68393e1d735) << 64) | 0x6cd2f7a9966ec602,
        (U128(0x6d11a9a1480d81d7) << 64) | 0x17db579c3e5d3874, (U128(0xebcd798303fcdfa2) << 64) | 0x8886f7c15bfc88ff,
        (U128(0xdb29665967915b22) << 64) | 0xe6883c87fe1a3d83, (U128(0x3be4255e0e7007e5) << 64) | 0x4b4a00f0128edbdc,
        (U128(0x2efbbcc95e77e70a) << 64) | 0xb64565e1f097f5d1, (U128(0x211704c75d9e31ed) << 64) | 0x25db902769c0bc26,
        (U128(0x13e51fec45ecc61b) << 64) | 0xcb0e69b4a085b2a3, (U128(0x76778d84201b2e62) << 64) | 0xd863053e2891f72b,
        (U128(0x1e5e60710a405a78) << 64) | 0xcbcbce0d8ff4dae5, (U128(0x5afb96bda2216bb9) << 64) | 0xbbc93ce5b774794d,
        (U128(0x19ff015d2ad43402) << 64) | 0x5459887ef6e17a04, (U128(0xf4aede9dc279735c) << 64) | 0x60dcdc890cddb4d5,
        (U128(0x5fb5d9ce7867038b) << 64) | 0x3a1f747e513a023a, (U128(0x90b89a88be6ef343) << 64) | 0x165bdbe1b46eb84e,
        (U128(0x74eb502bd74050ae) << 64) | 0x30f30c1164f59e8d, (U128(0x7360f1f7f5bca46c) << 64) | 0x4e0f8cd9b25cca82,
        (U128(0x6f563d2d6b1a2a6f) << 64) | 0xc67a2a38edc7e1ca, (U128(0x131773ff8e65824b) << 64) | 0x5a3fcc10b03f010d,
        (U128(0x4922beb65c909139) << 64) | 0xddcaf4d62bebf4af, (U128(0xf4bb18b0f7221d3c) << 64) | 0x1faac7a4b1274c53,
        (U128(0x04fb0a70b03b2282) << 64) | 0x6077b683355f8ca6, (U128(0xf047d22164966260) << 64) | 0x94b32b8985500b5d,
        (U128(0x23f0b8683deb13a1) << 64) | 0xa248e1e6788e942c, (U128(0x4f79760d888b6a2a) << 64) | 0x6fc4b819e20203a6,
        (U128(0xf114979323e30f8d) << 64) | 0x5e19e67bfb1a2ce7, (U128(0x74822eed969fe735) << 64) | 0x00fbf23f9fd715ff,
        (U128(0xc54461e5113bf3d9) << 64) | 0x429817dddd0d6ea8, (U128(0xc3c87f5456b13846) << 64) | 0x20e7c1ec619fb52a,
        (U128(0x96c2a321cff1e708) << 64) | 0xce4d87d0717aa341, (U128(0x81fc51d4bb83dbe4) << 64) | 0xb357cc1cf19a116c,
        (U128(0xe40714788becf297) << 64) | 0x8516a2ef08af8983, (U128(0x030288c0627aa501) << 64) | 0xbcd1c8854ea172ab,
        (U128(0x44758aa91e86f02a) << 64) | 0x181a0110228fa68c, (U128(0xa8b461227d354d0e) << 64) | 0xc0a27a82cafeb12c,
        (U128(0x2dc1f7f5b13e1f1b) << 64) | 0xd6b67597cc3127b6, (U128(0xe4a8f0e950e85fea) << 64) | 0xa09ddfc960846d90,
        (U128(0x624a995b99dc1ff4) << 64) | 0x880349bf9a8f3ebf, (U128(0x00dc7f5020594786) << 64) | 0x55b1c773214b5290,
        (U128(0x3c8b7fd75bf1ac46) << 64) | 0x5ca244a4ab06189d, (U128(0xdf74de0655014405) << 64) | 0xdc739285b34f3b26,
        (U128(0x355377b3f1bd9e9e) << 64) | 0x4d0b95f851e90ee7, (U128(0x4682904df8c5a46f) << 64) | 0x484e2124e0d6e6f7,
        (U128(0x27d34fcdc91dbd10) << 64) | 0xc4be017d64b8ff29, (U128(0xebfff8b1e75dee3c) << 64) | 0xb93cca09f61d64fd,
        (U128(0x85c834810c2b51f1) << 64) | 0x959395cfe5021a47, (U128(0x916ec6c7f7fae6b8) << 64) | 0x1b95199dadf9f92e,
        (U128(0xc07d723f89fd769e) << 64) | 0x1ea80d8784d3c4ab, (U128(0xa474c31c9b75961b) << 64) | 0xac21fc628a2f5c46,
        (U128(0x3dfd5de9256e38f3) << 64) | 0xfc4f2b155abda3e0, (U128(0xb1389682109b2acd) << 64) | 0x26ae1926812b0f3c,
        (U128(0xfa1f311fbc28d861) << 64) | 0x5e89a399f32c2585, (U128(0x1cafe15730ea4bfe) << 64) | 0x7be06cc0de517daa,
        (U128(0xf9e1b4e41aeb4a6d) << 64) | 0x1fe1a10ccd4ab811, (U128(0x18a199c6d98934d9) << 64) | 0x89f085e1799444ee,
        (U128(0x75cf7d96b2f271e0) << 64) | 0xf91578e85be35874, (U128(0x88eaea28406417ea) << 64) | 0x6026b606fbf4ed49,
        (U128(0x7d8b923752871a97) << 64) | 0xa524d4864a8e0669, (U128(0xa130bed9f898dec2) << 64) | 0xde5d47a8f687b29c,
        (U128(0xd5c78bc07129ac3d) << 64) | 0xb99de54b9d56a658, (U128(0xd81449a97c5d3abb) << 64) | 0x9a3debb742020da5,
        (U128(0x15b94a34aefccfc3) << 64) | 0xe2b48f0210a2ba21, (U128(0xadeac1c56bfe4c3a) << 64) | 0xdbfa9b6f04aae339,
        (U128(0x967b77fd12b156bd) << 64) | 0xf7f31c2d92cdb8f2, (U128(0x8d2d542c4826781d) << 64) | 0x1802d1a04ab7d839,
        (U128(0x61aa208ccc24e0f9) << 64) | 0xd9dd06f3de8ffb63, (U128(0x420afdfec9d61301) << 64) | 0x6d000ee7387700e3,
        (U128(0xa05bc24514dcd6f1) << 64) | 0xe798eda8d35dc0b2, (U128(0x5632bb59552e0d06) << 64) | 0x23e38ac261345a03,
        (U128(0x955090e583c991a1) << 64) | 0x9243314fd58cc91d, (U128(0x5a1e1a8d340a7931) << 64) | 0x895a072923e82918,
        (U128(0xb062a0fa607a7feb) << 64) | 0x1d034be8acdf3394, (U128(0x91f18e3c4c79b56d) << 64) | 0xf37c18fca6d38ae1,
        (U128(0x6a18449e36506221) << 64) | 0x93b623fd70e83212, (U128(0xa0c03d517558e50d) << 64) | 0x2b8edf62e15316fb,
        (U128(0xc78d92a64fea6e98) << 64) | 0x221c493a5509dd87, (U128(0x949139cf37636a53) << 64) | 0xca1f8fee6a8c4270,
        (U128(0x9faddb81a376e57b) << 64) | 0xc5d41477a01bf39d, (U128(0x56ac3b549d3d25e0) << 64) | 0x6bb57782815e9239,
        (U128(0xafc3276ae1f52e03) << 64) | 0xbcfd7263bf041042, (U128(0x7fe065c88267cccf) << 64) | 0xe1f4a5f5d222827d,
        (U128(0x317c52ad621ec356) << 64) | 0x4d78265a17358386, (U128(0x7707331cafa4039e) << 64) | 0x039cdd81a036e5b0,
        (U128(0x8dbe7ef47be0a01a) << 64) | 0xa87003603069d3df, (U128(0x4ba1cff4e32fb129) << 64) | 0x66c6dc7aee22f0ae,
        (U128(0x836248795f0a6ffe) << 64) | 0x582ff763decc8ce0, (U128(0x668b301e2f230a73) << 64) | 0xa6bed8cb4bcc89ec,
        (U128(0x99a7729b147a0aaa) << 64) | 0x4487d8859558ed76, (U128(0xce8b38d0e5519442) << 64) | 0xc7a46370e1f70293,
        (U128(0x6a1fa6c430d6186a) << 64) | 0x412a9c2b0a50c2fe, (U128(0xb13e19bc64cb0adb) << 64) | 0x0d69d4be1ce0d126,
        (U128(0x5a8b4369f5c2d3c8) << 64) | 0x2b97a7ba3a08bc8f, (U128(0x5ad54afd5d58aab7) << 64) | 0x3de12f01cfd11fe3,
        (U128(0x7bc8190d68f1a594) << 64) | 0xd6a5d49066ca1e9a, (U128(0x9f85401f16e2a76d) << 64) | 0xf901f64e0cc1625a,
        (U128(0x7d29d1fb42b69992) << 64) | 0xbe6bb8e786b8d880, (U128(0xbdf6a668aaaa0e16) << 64) | 0x0a85804a0fb2f9ad,
        (U128(0xc18dd9787dfe448e) << 64) | 0x82880c10e1def705, (U128(0x1fd2059945fe83c6) << 64) | 0x590a547bc8a1fcfb,
        (U128(0x7673ff288d904595) << 64) | 0x94dbfbf44dbc0183, (U128(0x9fe7ea02070ab507) << 64) | 0xb354f6fdc53853cb,
        (U128(0xb44e90bf3accd699) << 64) | 0x5544dac4853ec174, (U128(0x9bec0fa21a28c937) << 64) | 0x6f376d3644f89119,
        (U128(0x89f2bf3a7dd477c1) << 64) | 0x492a98b356bbc325, (U128(0x3e2740d6a6520419) << 64) | 0x8ffee74123ae000c,
        (U128(0x2977751698e8b030) << 64) | 0xa12a93b3cde2b426, (U128(0x685becc82eab1dbc) << 64) | 0x37087f37f806cb5c,
        (U128(0xa6bf9442a9552500) << 64) | 0x922b40c66126cb9c, (U128(0xf9c4001934b2620a) << 64) | 0x3cb3baf1d43aa334,
        (U128(0x514a5bb696dc20cf) << 64) | 0x39736d4213df3d77, (U128(0x6872b45e4fa3fd8b) << 64) | 0x51e1e95cb6187839,
        (U128(0xe1f13871abba8781) << 64) | 0x4c1c046acc030e6a, (U128(0x3956230d7cca3a81) << 64) | 0x4b9c6fcfd6285533,
        (U128(0xe4938d2118b44e5b) << 64) | 0xe3d50c517dd3d88a, (U128(0x27d10e801ee4f722) << 64) | 0xcc4d08c4307ee9f9,
        (U128(0x6c71a2193608d1c3) << 64) | 0xf024385ba60374b5, (U128(0x7f85fce7cb480811) << 64) | 0x25794777b889635e,
        (U128(0x485c8b59545b4ce9) << 64) | 0xed87e14e1803ef54, (U128(0xa9fa20926d7f2a7a) << 64) | 0xaa6d35fd43a437d9,
        (U128(0x3327b3f5cc99cdc2) << 64) | 0xc6776041a86e9d75, (U128(0xe5f9f1a4783a1aa6) << 64) | 0xda5b09e3d1523ba2,
        (U128(0xde0ced14440bb37a) << 64) | 0x190a002679275b71, (U128(0xb766920f57169266) << 64) | 0x8eb4396b908a3e33,
        (U128(0x16e6b9dde6a64fb5) << 64) | 0xce1eb4c6bd781809, (U128(0x62611ec0e0906a7d) << 64) | 0x6121b9e5cd58897c,
        (U128(0xb357e9a8c054da92) << 64) | 0x857bf4a65c0ae80b, (U128(0xb5b40eed91d5dfc1) << 64) | 0xc627d014970b487a,
        (U128(0x246b12a8de3f4da3) << 64) | 0x4973f7dd150fa73b, (U128(0x43ac1a838bc557f7) << 64) | 0xd4572cd267ac1201,
        (U128(0x5216ec59216f6964) << 64) | 0xc10b71cfea4633bd, (U128(0xddce982eb0f11291) << 64) | 0xaf1e016dfb14b835,
        (U128(0x7b638f876e5557ce) << 64) | 0xb4269a984afee5d9, (U128(0x91ba019fffae04a0) << 64) | 0x216638e0ee08b7c4,
        (U128(0x59426cf2bd74a9a3) << 64) | 0x1a133c61f5dc96dd, (U128(0x9479eb2b3af2395c) << 64) | 0xf186bbd882abb120,
        (U128(0x2763f32886f84d67) << 64) | 0xe48872722f24dcff, (U128(0x23faf711f6471404) << 64) | 0x566d811daadf5faf,
        (U128(0xb465f02d2d10df50) << 64) | 0x19055efc74b946e0, (U128(0xf82e89b42e3f199b) << 64) | 0x6f329f930494f68f,
        (U128(0xc9c9e079864d852a) << 64) | 0xfb3c179b9d021746, (U128(0x6882cddc89a2df1b) << 64) | 0xb8d291a33597c80a,
        (U128(0x93aa650c393aed8a) << 64) | 0x9575a1e6110f671d, (U128(0x90ba7845400a2908) << 64) | 0x862fa196149694b1,
        (U128(0xf9826caab630044e) << 64) | 0xcc22e7519cb97666, (U128(0x15f4f7993c4524ba) << 64) | 0x3cd5024d052533d7,
        (U128(0xd5d584bd85e54f5b) << 64) | 0x3615b6305787406f, (U128(0xbf25e105e5af6eb8) << 64) | 0xfde78fd25bed162b,
        (U128(0xf34efef69632dc55) << 64) | 0x6cb6a01f5b4fee4a, (U128(0x0612c30edd0337da) << 64) | 0xe3bfad72943f6d29,
        (U128(0x09c6f9a086aef2d6) << 64) | 0x7508335674877b76, (U128(0x243cb0099e2a092a) << 64) | 0x03678d07fad33f54,
        (U128(0x66f45778255a5eb8) << 64) | 0x356ab8d378bf2cca, (U128(0x7f2e22a924a9449b) << 64) | 0xef5ede862b787ea0,
        (U128(0x8802f92966c74b72) << 64) | 0x67b214bc9225eb92, (U128(0x8ee0ee9a6773b745) << 64) | 0x45936d99261ba0e7,
        (U128(0x8488d30bec6929ad) << 64) | 0x47566348386d7063, (U128(0x07e17505d250512f) << 64) | 0x0de618677c25b2c5,
        (U128(0xb8e28103396e0392) << 64) | 0x2286d5c709febcab, (U128(0x07f374d0d423a055) << 64) | 0x6a8a0d2f821028a8,
        (U128(0x221bcc72700499d1) << 64) | 0x9f16add206f5c9dd, (U128(0x336a9dc7be63eecd) << 64) | 0x23f05e34c4d86f17,
        (U128(0x11f010c019afef4f) << 64) | 0xaa2b2fc558ca6ab4, (U128(0xfa162619290ed3c9) << 64) | 0x12487414f6e6ebe1,
        (U128(0x0f054f53ef29f097) << 64) | 0x19f2f693ee48191c, (U128(0x7afeb009cd3062ed) << 64) | 0x39d98b11384c6f05,
        (U128(0x5d49209ac70a45d9) << 64) | 0x172fabd049814402, (U128(0x784d85726acfb596) << 64) | 0xcd5f2ebe72cad367,
        (U128(0x2d359556efda8bec) << 64) | 0x90aed8d381e74be9, (U128(0x72306a0f4ef4daa2) << 64) | 0x30e670376e3f433d,
        (U128(0x9c51df0044e6f3b0) << 64) | 0x9a903c17e9b23331, (U128(0xa31862f8f79cff31) << 64) | 0x6292dff71f8034f6,
        (U128(0x320807fdc6bd215a) << 64) | 0x2e8e414e87adb36a, (U128(0x5db4bb8c053d7254) << 64) | 0x68acea2b82526aa2,
        (U128(0xd441df0cc89afe5c) << 64) | 0xe16d128c1b28f9f9, (U128(0xef6103cbbf0b4191) << 64) | 0xb035d19bb9d0c99d,
        (U128(0x2e2908691dbc667c) << 64) | 0xfa9dbc85f0092bb6, (U128(0xdee671be0e109ebe) << 64) | 0xd92a309d565b35ed,
        (U128(0x990a8377d94f2aae) << 64) | 0xb69c8f499b203e3b, (U128(0xab36541bee991a29) << 64) | 0x04cbefa87a6743a6,
        (U128(0xdf2581c4ea8bf83e) << 64) | 0x070d1ccdf4af1e57, (U128(0x08d24c07fbb9b1ea) << 64) | 0xcaee35ea5fe4b94c,
        (U128(0xf3b68f28acbc0d1c) << 64) | 0x89fc8edc2b300edf, (U128(0x686856debeb7a276) << 64) | 0x3040f6170dae0fd3,
        (U128(0x82732502403336d6) << 64) | 0x3395495a76a85603, (U128(0x1b79e2320a738234) << 64) | 0xc31da49e279f5dcc,
        (U128(0x46d69bd530d6941c) << 64) | 0x7238bef2a209dba4, (U128(0x0ed92892d60f6803) << 64) | 0x421fca3a32a77849,
        (U128(0x2b71f8b2ca537735) << 64) | 0x41a98ab8a1dafec0, (U128(0xb2b45e3c85d72163) << 64) | 0x31af5b3fe8c5e771,
        (U128(0x4ff06816af087ba0) << 64) | 0x1e3d07c189a654db, (U128(0xc958d048bc5b11f3) << 64) | 0x6639d3d8fca00818,
        (U128(0xf4529cba99821757) << 64) | 0x05e87a30ce0998a6, (U128(0xde801eff80f23ba4) << 64) | 0x6d35f3356c180768,
        (U128(0x076112bec3c00af2) << 64) | 0x96cb5026c40c88d3, (U128(0x9592dee06cd7553b) << 64) | 0x328dce361c2f4630,
        (U128(0x539f2712e2d62a30) << 64) | 0x730e2a43dc552ec5, (U128(0xdf447ab01125f66f) << 64) | 0xe85b920444167b94,
        (U128(0x8531c8ba23d87bb9) << 64) | 0xe67009d7371488c6, (U128(0xc23426930f6a5b8a) << 64) | 0x98371d66cc8fc3c3,
        (U128(0xa4765d2102dfd380) << 64) | 0x08fb895f27bc855b, (U128(0xe5e2aeecf81b4922) << 64) | 0x41515feac7cd8609,
        (U128(0xf5d8409901eb71ee) << 64) | 0xf3aca2fdafdcf61a, (U128(0x18c664a785efc4fd) << 64) | 0x57eb47fbae4696d1,
        (U128(0xa174abab649cabb2) << 64) | 0xc4fe0195f6a0a155, (U128(0xa78f1feb17c947de) << 64) | 0x9cd9370cc7d639f2,
        (U128(0x6d4a6277cb897ca3) << 64) | 0x610c680df2cef7e4, (U128(0x10998da8c549a6e5) << 64) | 0x209681a4f6fe1aad,
        (U128(0x13c09e8ae88560eb) << 64) | 0x8dc9dbeedfc899b8, (U128(0x48b88678fa169e7e) << 64) | 0x838625ed79114b98,
        (U128(0x170232173f5e07b2) << 64) | 0x7423e31224b30207, (U128(0xe5dec319fc09525c) << 64) | 0x1d67d807b6d0e323,
        (U128(0x329276065b21a791) << 64) | 0x169dd0907f28c921, (U128(0x3b0d4ca3450383e0) << 64) | 0xdfa8af2dfab63af7,
        (U128(0x530200cad093f333) << 64) | 0x054b3b3b82b8c1de, (U128(0xbc0a06e8b87fcf2e) << 64) | 0x3bb49f1f01e548c0,
        (U128(0x466fbe29239eaed3) << 64) | 0x965d807879e87028, (U128(0x823b01eb27329bee) << 64) | 0x221376821ba9f328,
        (U128(0x78ece23d3b7fb9a6) << 64) | 0x95bf5e4daaeb6e65, (U128(0x1d2dfa3a1dd26b57) << 64) | 0x8f7e25902a501d53,
        (U128(0x0994e0a1bfeba697) << 64) | 0x0ec5823ab58a4c05, (U128(0x9d899014c04d6bbb) << 64) | 0x2b3a24d0cfe4158f,
        (U128(0x22d2316059d89d33) << 64) | 0x3ab19fbc98061a24, (U128(0x9c4d2bb4b464e426) << 64) | 0x28fbe6d615cee87b,
        (U128(0x2d24507e57199a07) << 64) | 0x9de8903c63ea7eb4, (U128(0xef11d580ab3423b5) << 64) | 0xc8d6bf496e24ffa5,
        (U128(0x583677216c0bae50) << 64) | 0xb9644b2feabd4cc7, (U128(0x8f0d94448c0b08da) << 64) | 0xb8b00f356de86eb6,
        (U128(0x62712ef70e64e21f) << 64) | 0xcf8b4ac76ab153ab, (U128(0x22245dab6bdad4a9) << 64) | 0x36fdf2b34e6063a4,
        (U128(0xa16249fc803172a8) << 64) | 0xa32a214b86fb9636, (U128(0xe6d0fe36383196e0) << 64) | 0x0ac7536f553a1519,
        (U128(0xf5a6c73d550158f8) << 64) | 0x7b2c16a9c70ea1cb, (U128(0x5a174aba069441ba) << 64) | 0x456a56053c202bde,
        (U128(0x33f181f17cd56ace) << 64) | 0xd7ff72dfbc1fae98, (U128(0xa510fe339fac5d28) << 64) | 0x43b08486340d609a,
        (U128(0xcb33578ac4be387d) << 64) | 0x3eb16dd531a2195c, (U128(0xe691b1bd6fcb9ce7) << 64) | 0xa9470b666a72fc1f,
        (U128(0x6423e3cc729d9424) << 64) | 0x1eb764486ec4922b, (U128(0x2c89b938250dede1) << 64) | 0xbb3921068cde6dee,
        (U128(0x4cd5a1c6b7dede77) << 64) | 0x788a2141d47f86a6, (U128(0x0018a80dad0b501b) << 64) | 0x497e88f442b9b27d,
        (U128(0x0a0f0ca34572c9a0) << 64) | 0x43f674021bb23a01, (U128(0x793106bccb2c4175) << 64) | 0x12a3509c96dea679,
        (U128(0x2a4dad9bf7715548) << 64) | 0xc512d35702d757da, (U128(0x9c0a57be9d65d947) << 64) | 0xc79ce74de6478e4f,
        (U128(0x7834d37947418da0) << 64) | 0x05693ea31c882e06, (U128(0x52028ebf22833573) << 64) | 0x8852768b66888b1e,
        (U128(0xcc29feac0ded1b40) << 64) | 0x64a3a9d8100d6d3a, (U128(0x506296abd22a2b00) << 64) | 0x142c328c4e04c4b7,
        (U128(0x1ba38244b69e8f8e) << 64) | 0xa607508444dcb0da, (U128(0x9b97878052591cc6) << 64) | 0xb0a38749c0a77573,
        (U128(0x882676b9968fe076) << 64) | 0xac734c4d5405616a, (U128(0x5a0f472bc54cf625) << 64) | 0x12a1fc3aec04d434,
        (U128(0x6685ba42c6ecec97) << 64) | 0xd36cb745f269ae51, (U128(0x8eff36605141c5d0) << 64) | 0x3b34edd7e3e6d0a7,
        (U128(0x8f199f706188d226) << 64) | 0x8996550d71072d82, (U128(0xa1211626125bca97) << 64) | 0x51d38c61906bca6f,
        (U128(0x59d1a24aaac15fbb) << 64) | 0x26071a3019e46b4d, (U128(0x40c346f5b7a7e5a3) << 64) | 0x547f9b5c46c3281b,
        (U128(0x810b7445a7dc5442) << 64) | 0x9db50ef8536fcaaf, (U128(0xa05de37681a871f3) << 64) | 0x5b16f3d691cc5b06,
        (U128(0x84ff30cf2e6927be) << 64) | 0x744ac1f2825de458, (U128(0xeff820468aaa9560) << 64) | 0xda11f64e3eb55bd9,
        (U128(0xf439d4d9ced2e8c5) << 64) | 0x516ba44e7a1a3421, (U128(0xa6d355e1fa28a3c4) << 64) | 0xf390cd74221d7fb5,
        (U128(0x9aca4a8667210625) << 64) | 0x71eb37744a7536d7, (U128(0x0e84de4a32d17cc2) << 64) | 0x8b6de54f35e044f0,
        (U128(0xdf08dd3504375a25) << 64) | 0xcd2f7162afe75318, (U128(0x3d92954159bf2e61) << 64) | 0xf53f0746b2de5a5d,
        (U128(0x2f4ee1d079627233) << 64) | 0x2f9175b667733249, (U128(0x6563923b42780f67) << 64) | 0xb92a4099c102c202,
        (U128(0xe12478ec8f9e6286) << 64) | 0xfe5180c58ceaa461, (U128(0x9e88a68344dc0e86) << 64) | 0xc7509a41fe74c06f,
        (U128(0xe23d23c85f762b9f) << 64) | 0x75e07e65053bbb9f, (U128(0x3211cc3d9a3d33b6) << 64) | 0x72595a3d7ecab2a3,
        (U128(0x8e43edc5918e9ec5) << 64) | 0x7c95b57454e0ce99, (U128(0xc7e3f912ddb9d00e) << 64) | 0x28d17c44e8e08c00,
        (U128(0x53d501980e4f0927) << 64) | 0x21ec9eefef360fe1, (U128(0x7d279c2aa729ef3c) << 64) | 0x8593a1306798b415,
        (U128(0x5f24241283956b70) << 64) | 0xdba2c1d95edb1df7, (U128(0x788be5cab9873733) << 64) | 0xc4ca76d612712a4c,
        (U128(0x4b9ebe53da1f473d) << 64) | 0x174d7828b7ef367b, (U128(0xe5cb8182c543f4f5) << 64) | 0x6071e8dd70eaccc2,
        (U128(0xa01d1c75c659b201) << 64) | 0xc2187a011e0e4153, (U128(0xc8c80f983032f21a) << 64) | 0x1e48c85e8f4387d6,
        (U128(0x5cfa0a878aa03ee4) << 64) | 0x51a8076a35c913f8, (U128(0xe92bcd67c4a5a72a) << 64) | 0xd462f1aaed570f01,
        (U128(0x85fe339d669c634a) << 64) | 0xfacae1fa69585400, (U128(0x9503e98acfdf871b) << 64) | 0x4b0c321e1ba4cfde,
        (U128(0x720de01011c398d7) << 64) | 0x147b3bfe27571ff1, (U128(0x90e26fba807db201) << 64) | 0xc514274e9fb06f50,
        (U128(0x34ce33c25bb0d5aa) << 64) | 0x88e67ad6f27d0c14, (U128(0xbc4515f5ec157874) << 64) | 0x1532dd9490dead8d,
        (U128(0x7e5150129e9c0c24) << 64) | 0x2d7ee340dc656279, (U128(0x8896757fe4f9d5e5) << 64) | 0xe20f3c0a9c4ce650,
        (U128(0xcec2ce37490d699c) << 64) | 0xd2b8db595c378c26, (U128(0x7ae3584469866b25) << 64) | 0x80e9d1c3cd2c1623,
        (U128(0xdefbf3d05bbb32df) << 64) | 0x2980a49239178f3a, (U128(0xe192430e58980ef3) << 64) | 0x37225c787ec34b48,
        (U128(0x26af3742748fc97f) << 64) | 0x65460e8ed381ebf1, (U128(0x15faacaeb1b6cb17) << 64) | 0xc231850d22763032,
        (U128(0xbc42b25cd0f0ec64) << 64) | 0x15c544fe58068578, (U128(0x50b17e9ceea520bb) << 64) | 0x1a6a65c309c53854,
        (U128(0xf45e2cf4ea0ce8ee) << 64) | 0xf793fdd2aa78ba51, (U128(0x591d92d330775537) << 64) | 0x4a077b3e23f13782,
        (U128(0x57054cdce017931e) << 64) | 0xd747ebecdd38c78a, (U128(0xef59febe1f414b36) << 64) | 0x2039957776fc029c,
        (U128(0x3a73880130de9b70) << 64) | 0xff1565e27d097bee, (U128(0x927848e6abe4ed31) << 64) | 0xdd7acd5a3e786e27,
        (U128(0xc0d60e0eaaac7ed7) << 64) | 0x5740be4e3061736b, (U128(0x7ec654d3428f9d51) << 64) | 0x3fdb01d6c98dc78a,
        (U128(0x3e0e99a66d048a83) << 64) | 0x5d8797337eb515f0, (U128(0xac947a73e543f791) << 64) | 0x8f4342c0bea210cf,
        (U128(0xa4709c777b31ceb6) << 64) | 0x254e91f682f45ad2, (U128(0x8f83e67bc926a0a8) << 64) | 0xd3fa2b5226eb508d,
        (U128(0x4c9e1f4ae5d46583) << 64) | 0x8e2e08609903c8c8, (U128(0x9edd92482f037209) << 64) | 0x5248fccd976d172a,
        (U128(0xcb055c6baf90c7db) << 64) | 0x0f533a96db45f5ec, (U128(0x42e874092c4b33ac) << 64) | 0xdf2417a82507cc62,
        (U128(0x35fe879aee14a2f4) << 64) | 0x851906627da66b5d, (U128(0x9a8de2203d064904) << 64) | 0x887299fd71f6171a,
        (U128(0x0a871441294f9de2) << 64) | 0xb8fe78f575f11f21, (U128(0x352240412649051f) << 64) | 0xd06a406c7ceee281,
        (U128(0x9816de3d9968107c) << 64) | 0xe44fc0a1c2bcb547, (U128(0xe8983d22ac68fa6c) << 64) | 0xfab5b1835e876a0f,
        (U128(0x00fe77a1fe8d5c8c) << 64) | 0x1dc39b339186cab8, (U128(0x13d43fb7d6022255) << 64) | 0xb57ec0961ea3bbda,
        (U128(0x0814adc51638f692) << 64) | 0x7c0395c3d941b1fc, (U128(0x8a86ce0ae763e204) << 64) | 0x0dd34a11d33ff39e,
        (U128(0x545451397e976e8a) << 64) | 0xc4f8817b338127de, (U128(0x8864bc9bb2445a56) << 64) | 0xd13d8be445b5e93b,
        (U128(0x28117d589d6d3ed3) << 64) | 0x133890f78e7faca5, (U128(0x848152e8a0f1e4aa) << 64) | 0x0a7f6f6dcced8fc1,
        (U128(0x4f5d31eddf4415a8) << 64) | 0x7cb96b70dd59fc98, (U128(0x7b427f9d06a11e2e) << 64) | 0x026adb29c5d0a164,
        (U128(0xbd267f12261ba5ea) << 64) | 0xed7eecaed9c1ac6a, (U128(0xff22e298e414d44e) << 64) | 0xe3fd20a107418109,
        (U128(0xe286097df6d1cefe) << 64) | 0xde12c44608761b68, (U128(0x511b7c63da1e5818) << 64) | 0xc41d07d97a91ead5,
        (U128(0x219e192bc30f6f7c) << 64) | 0x0831b50dddce28ad, (U128(0xa4363d187ca0e02c) << 64) | 0xc0f85bfd1735646f,
        (U128(0x17a54c5ab1094cd8) << 64) | 0x47745ed620798bec, (U128(0x297f78d0669dd88c) << 64) | 0x450dc3cf4ba734be,
        (U128(0xb708dd340375c20e) << 64) | 0xa9ab83b0efe006a3,
    };

    static constexpr std::array<U128, 16> castlingKey = []() constexpr {
        auto generateCastlingKey = [](int index) constexpr -> U128 {
            constexpr int RANDOM_OFFSET = 768;
            constexpr int RANDOM_COUNT  = 4;

            U128 key = 0;

            for (int i = 0; i < RANDOM_COUNT; ++i) {
                if (index & (1 << i)) {
                    key ^= RANDOM_ARRAY[RANDOM_OFFSET + i];
                }
            }

            return key;
        };

        std::array<U128, 16> arr{};

        for (int i = 0; i < 16; ++i) arr[i] = generateCastlingKey(i);

        return arr;
    }();

    static constexpr int MAP_HASH_PIECE[12] = {1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10};

    [[nodiscard]] static U128 piece(Piece piece, Square square) noexcept {
        assert(piece < 12);
#if __cplusplus >= 202207L
        [[assume(piece < 12)]];
#endif
        return RANDOM_ARRAY[64 * MAP_HASH_PIECE[piece] + square.index()];
    }

    [[nodiscard]] static U128 enpassant(File file) noexcept {
        assert(int(file) < 8);
#if __cplusplus >= 202207L
        [[assume(int(file) < 8)]];
#endif
        return RANDOM_ARRAY[772 + file];
    }

    [[nodiscard]] static U128 castling(int castling) noexcept {
        assert(castling >= 0 && castling < 16);
#if __cplusplus >= 202207L
        [[assume(castling < 16)]];
#endif
        return castlingKey[castling];
    }

    [[nodiscard]] static U128 castlingIndex(int idx) noexcept {
        assert(idx >= 0 && idx < 4);
#if __cplusplus >= 202207L
        [[assume(idx < 4)]];
#endif
        return RANDOM_ARRAY[768 + idx];
    }

    [[nodiscard]] static U128 sideToMove() noexcept { return RANDOM_ARRAY[780]; }

   public:
    friend class Board;
};

}  // namespace chess

namespace chess {

enum class GameResult { WIN, LOSE, DRAW, NONE };

enum class GameResultReason {
    CHECKMATE,
    STALEMATE,
    INSUFFICIENT_MATERIAL,
    FIFTY_MOVE_RULE,
    THREEFOLD_REPETITION,
    NONE
};

// A compact representation of the board in 24 bytes,
// does not include the half-move clock or full move number.
using PackedBoard = std::array<std::uint8_t, 24>;

class Board {
    using U64  = std::uint64_t;
    using U128 = __uint128_t;

   public:
    class CastlingRights {
       public:
        enum class Side : uint8_t { KING_SIDE, QUEEN_SIDE };

        constexpr void setCastlingRight(Color color, Side castle, File rook_file) {
            rooks[color][static_cast<int>(castle)] = rook_file;
        }

        constexpr void clear() { rooks[0][0] = rooks[0][1] = rooks[1][0] = rooks[1][1] = File::NO_FILE; }

        constexpr int clear(Color color, Side castle) {
            rooks[color][static_cast<int>(castle)] = File::NO_FILE;
            return color * 2 + static_cast<int>(castle);
        }

        constexpr void clear(Color color) { rooks[color][0] = rooks[color][1] = File::NO_FILE; }

        constexpr bool has(Color color, Side castle) const {
            return rooks[color][static_cast<int>(castle)] != File::NO_FILE;
        }

        constexpr bool has(Color color) const { return has(color, Side::KING_SIDE) || has(color, Side::QUEEN_SIDE); }

        constexpr File getRookFile(Color color, Side castle) const { return rooks[color][static_cast<int>(castle)]; }

        constexpr int hashIndex() const {
            return has(Color::WHITE, Side::KING_SIDE) + 2 * has(Color::WHITE, Side::QUEEN_SIDE) +
                   4 * has(Color::BLACK, Side::KING_SIDE) + 8 * has(Color::BLACK, Side::QUEEN_SIDE);
        }

        constexpr bool isEmpty() const { return !has(Color::WHITE) && !has(Color::BLACK); }

        template <typename T>
        static constexpr Side closestSide(T sq, T pred) {
            return sq > pred ? Side::KING_SIDE : Side::QUEEN_SIDE;
        }

       private:
        std::array<std::array<File, 2>, 2> rooks;
    };

   private:
    struct State {
        U128 hash;
        CastlingRights castling;
        Square enpassant;
        uint8_t half_moves;
        Piece captured_piece;

        State(const U128 &hash, const CastlingRights &castling, const Square &enpassant, const uint8_t &half_moves,
              const Piece &captured_piece)
            : hash(hash),
              castling(castling),
              enpassant(enpassant),
              half_moves(half_moves),
              captured_piece(captured_piece) {}
    };

    enum class PrivateCtor { CREATE };

    // private constructor to avoid initialization
    Board(PrivateCtor) {}

   public:
    explicit Board(std::string_view fen = constants::STARTPOS, bool chess960 = false) {
        prev_states_.reserve(256);
        chess960_ = chess960;
        setFenInternal<true>(fen);
    }

    virtual void setFen(std::string_view fen) { setFenInternal(fen); }

    static Board fromFen(std::string_view fen) { return Board(fen); }
    static Board fromEpd(std::string_view epd) {
        Board board;
        board.setEpd(epd);
        return board;
    }

    void setEpd(const std::string_view epd) {
        auto parts = utils::splitString(epd, ' ');

#ifndef CHESS_NO_EXCEPTIONS
        if (parts.size() < 1) throw std::runtime_error("Invalid EPD");
#else
        if (parts.size() < 1) return;
#endif

        int hm = 0;
        int fm = 1;

        static auto parseStringViewToInt = [](std::string_view sv) -> std::optional<int> {
            if (!sv.empty() && sv.back() == ';') sv.remove_suffix(1);
#ifndef CHESS_NO_EXCEPTIONS
            try {
                size_t pos;
                int value = std::stoi(std::string(sv), &pos);
                if (pos == sv.size()) return value;
            } catch (...) {
            }
#else
            size_t pos;
            int value = std::stoi(std::string(sv), &pos);
            if (pos == sv.size()) return value;
#endif
            return std::nullopt;
        };

        if (auto it = std::find(parts.begin(), parts.end(), "hmvc"); it != parts.end()) {
            auto num = *(it + 1);

            hm = parseStringViewToInt(num).value_or(0);
        }

        if (auto it = std::find(parts.begin(), parts.end(), "fmvn"); it != parts.end()) {
            auto num = *(it + 1);

            fm = parseStringViewToInt(num).value_or(1);
        }

        auto fen = std::string(parts[0]) + " " + std::string(parts[1]) + " " + std::string(parts[2]) + " " +
                   std::string(parts[3]) + " " + std::to_string(hm) + " " + std::to_string(fm);

        setFen(fen);
    }

    /**
     * @brief  Get the current FEN string.
     * @param move_counters
     * @return
     */
    [[nodiscard]] std::string getFen(bool move_counters = true) const {
        std::string ss;
        ss.reserve(100);

        // Loop through the ranks of the board in reverse order
        for (int rank = 7; rank >= 0; rank--) {
            std::uint32_t free_space = 0;

            // Loop through the files of the board
            for (int file = 0; file < 8; file++) {
                // Calculate the square index
                const int sq = rank * 8 + file;

                // If there is a piece at the current square
                if (Piece piece = at(Square(sq)); piece != Piece::NONE) {
                    // If there were any empty squares before this piece,
                    // append the number of empty squares to the FEN string
                    if (free_space) {
                        ss += std::to_string(free_space);
                        free_space = 0;
                    }

                    // Append the character representing the piece to the FEN string
                    ss += static_cast<std::string>(piece);
                } else {
                    // If there is no piece at the current square, increment the
                    // counter for the number of empty squares
                    free_space++;
                }
            }

            // If there are any empty squares at the end of the rank,
            // append the number of empty squares to the FEN string
            if (free_space != 0) {
                ss += std::to_string(free_space);
            }

            // Append a "/" character to the FEN string, unless this is the last rank
            ss += (rank > 0 ? "/" : "");
        }

        // Append " w " or " b " to the FEN string, depending on which player's turn it is
        ss += ' ';
        ss += (stm_ == Color::WHITE ? 'w' : 'b');

        // Append the appropriate characters to the FEN string to indicate
        // whether castling is allowed for each player
        if (cr_.isEmpty())
            ss += " -";
        else {
            ss += ' ';
            ss += getCastleString();
        }

        // Append information about the en passant square (if any)
        // and the half-move clock and full move number to the FEN string
        if (ep_sq_ == Square::NO_SQ)
            ss += " -";
        else {
            ss += ' ';
            ss += static_cast<std::string>(ep_sq_);
        }

        if (move_counters) {
            ss += ' ';
            ss += std::to_string(halfMoveClock());
            ss += ' ';
            ss += std::to_string(fullMoveNumber());
        }

        // Return the resulting FEN string
        return ss;
    }

    [[nodiscard]] std::string getEpd() const {
        std::string ss;
        ss.reserve(100);

        ss += getFen(false);
        ss += " hmvc ";
        ss += std::to_string(halfMoveClock()) + ";";
        ss += " fmvn ";
        ss += std::to_string(fullMoveNumber()) + ";";

        return ss;
    }

    /**
     * @brief Make a move on the board. The move must be legal otherwise the
     * behavior is undefined. EXACT can be set to true to only record
     * the enpassant square if the enemy can legally capture the pawn on their
     * next move.
     * @tparam EXACT
     * @param move
     */
    template <bool EXACT = false>
    void makeMove(const Move move) {
        const auto capture  = at(move.to()) != Piece::NONE && move.typeOf() != Move::CASTLING;
        const auto captured = at(move.to());
        const auto pt       = at<PieceType>(move.from());

        // Validate side to move
        assert((at(move.from()) < Piece::BLACKPAWN) == (stm_ == Color::WHITE));

        prev_states_.emplace_back(key_, cr_, ep_sq_, hfm_, captured);

        hfm_++;
        plies_++;

        if (ep_sq_ != Square::NO_SQ) key_ ^= Zobrist::enpassant(ep_sq_.file());
        ep_sq_ = Square::NO_SQ;

        if (capture) {
            removePiece(captured, move.to());

            hfm_ = 0;
            key_ ^= Zobrist::piece(captured, move.to());

            // remove castling rights if rook is captured
            if (captured.type() == PieceType::ROOK && Rank::back_rank(move.to().rank(), ~stm_)) {
                const auto king_sq = kingSq(~stm_);
                const auto file    = CastlingRights::closestSide(move.to(), king_sq);

                if (cr_.getRookFile(~stm_, file) == move.to().file()) {
                    key_ ^= Zobrist::castlingIndex(cr_.clear(~stm_, file));
                }
            }
        }

        // remove castling rights if king moves
        if (pt == PieceType::KING && cr_.has(stm_)) {
            key_ ^= Zobrist::castling(cr_.hashIndex());
            cr_.clear(stm_);
            key_ ^= Zobrist::castling(cr_.hashIndex());
        } else if (pt == PieceType::ROOK && Square::back_rank(move.from(), stm_)) {
            const auto king_sq = kingSq(stm_);
            const auto file    = CastlingRights::closestSide(move.from(), king_sq);

            // remove castling rights if rook moves from back rank
            if (cr_.getRookFile(stm_, file) == move.from().file()) {
                key_ ^= Zobrist::castlingIndex(cr_.clear(stm_, file));
            }
        } else if (pt == PieceType::PAWN) {
            hfm_ = 0;

            // double push
            if (Square::value_distance(move.to(), move.from()) == 16) {
                // imaginary attacks from the ep square from the pawn which moved
                Bitboard ep_mask = attacks::pawn(stm_, move.to().ep_square());

                // add enpassant hash if enemy pawns are attacking the square
                if (static_cast<bool>(ep_mask & pieces(PieceType::PAWN, ~stm_))) {
                    int found = -1;

                    // check if the enemy can legally capture the pawn on the next move
                    if constexpr (EXACT) {
                        const auto piece = at(move.from());

                        found = 0;

                        removePieceInternal(piece, move.from());
                        placePieceInternal(piece, move.to());

                        stm_ = ~stm_;

                        bool valid;

                        if (stm_ == Color::WHITE) {
                            valid = movegen::isEpSquareValid<Color::WHITE>(*this, move.to().ep_square());
                        } else {
                            valid = movegen::isEpSquareValid<Color::BLACK>(*this, move.to().ep_square());
                        }

                        if (valid) found = 1;

                        // undo
                        stm_ = ~stm_;

                        removePieceInternal(piece, move.to());
                        placePieceInternal(piece, move.from());
                    }

                    if (found != 0) {
                        assert(at(move.to().ep_square()) == Piece::NONE);
                        ep_sq_ = move.to().ep_square();
                        key_ ^= Zobrist::enpassant(move.to().ep_square().file());
                    }
                }
            }
        }

        if (move.typeOf() == Move::CASTLING) {
            assert(at<PieceType>(move.from()) == PieceType::KING);
            assert(at<PieceType>(move.to()) == PieceType::ROOK);

            const bool king_side = move.to() > move.from();
            const auto rookTo    = Square::castling_rook_square(king_side, stm_);
            const auto kingTo    = Square::castling_king_square(king_side, stm_);

            const auto king = at(move.from());
            const auto rook = at(move.to());

            removePiece(king, move.from());
            removePiece(rook, move.to());

            assert(king == Piece(PieceType::KING, stm_));
            assert(rook == Piece(PieceType::ROOK, stm_));

            placePiece(king, kingTo);
            placePiece(rook, rookTo);

            key_ ^= Zobrist::piece(king, move.from()) ^ Zobrist::piece(king, kingTo);
            key_ ^= Zobrist::piece(rook, move.to()) ^ Zobrist::piece(rook, rookTo);
        } else if (move.typeOf() == Move::PROMOTION) {
            const auto piece_pawn = Piece(PieceType::PAWN, stm_);
            const auto piece_prom = Piece(move.promotionType(), stm_);

            removePiece(piece_pawn, move.from());
            placePiece(piece_prom, move.to());

            key_ ^= Zobrist::piece(piece_pawn, move.from()) ^ Zobrist::piece(piece_prom, move.to());
        } else {
            assert(at(move.from()) != Piece::NONE);
            assert(at(move.to()) == Piece::NONE);

            const auto piece = at(move.from());

            removePiece(piece, move.from());
            placePiece(piece, move.to());

            key_ ^= Zobrist::piece(piece, move.from()) ^ Zobrist::piece(piece, move.to());
        }

        if (move.typeOf() == Move::ENPASSANT) {
            assert(at<PieceType>(move.to().ep_square()) == PieceType::PAWN);

            const auto piece = Piece(PieceType::PAWN, ~stm_);

            removePiece(piece, move.to().ep_square());

            key_ ^= Zobrist::piece(piece, move.to().ep_square());
        }

        key_ ^= Zobrist::sideToMove();
        stm_ = ~stm_;
    }

    void unmakeMove(const Move move) {
        const auto prev = prev_states_.back();
        prev_states_.pop_back();

        ep_sq_ = prev.enpassant;
        cr_    = prev.castling;
        hfm_   = prev.half_moves;
        stm_   = ~stm_;
        plies_--;

        if (move.typeOf() == Move::CASTLING) {
            const bool king_side    = move.to() > move.from();
            const auto rook_from_sq = Square(king_side ? File::FILE_F : File::FILE_D, move.from().rank());
            const auto king_to_sq   = Square(king_side ? File::FILE_G : File::FILE_C, move.from().rank());

            assert(at<PieceType>(rook_from_sq) == PieceType::ROOK);
            assert(at<PieceType>(king_to_sq) == PieceType::KING);

            const auto rook = at(rook_from_sq);
            const auto king = at(king_to_sq);

            removePiece(rook, rook_from_sq);
            removePiece(king, king_to_sq);

            assert(king == Piece(PieceType::KING, stm_));
            assert(rook == Piece(PieceType::ROOK, stm_));

            placePiece(king, move.from());
            placePiece(rook, move.to());

            key_ = prev.hash;

            return;
        } else if (move.typeOf() == Move::PROMOTION) {
            const auto pawn  = Piece(PieceType::PAWN, stm_);
            const auto piece = at(move.to());

            assert(piece.type() == move.promotionType());
            assert(piece.type() != PieceType::PAWN);
            assert(piece.type() != PieceType::KING);
            assert(piece.type() != PieceType::NONE);

            removePiece(piece, move.to());
            placePiece(pawn, move.from());

            if (prev.captured_piece != Piece::NONE) {
                assert(at(move.to()) == Piece::NONE);
                placePiece(prev.captured_piece, move.to());
            }

            key_ = prev.hash;
            return;
        } else {
            assert(at(move.to()) != Piece::NONE);
            assert(at(move.from()) == Piece::NONE);

            const auto piece = at(move.to());

            removePiece(piece, move.to());
            placePiece(piece, move.from());
        }

        if (move.typeOf() == Move::ENPASSANT) {
            const auto pawn   = Piece(PieceType::PAWN, ~stm_);
            const auto pawnTo = static_cast<Square>(ep_sq_ ^ 8);

            assert(at(pawnTo) == Piece::NONE);

            placePiece(pawn, pawnTo);
        } else if (prev.captured_piece != Piece::NONE) {
            assert(at(move.to()) == Piece::NONE);

            placePiece(prev.captured_piece, move.to());
        }

        key_ = prev.hash;
    }

    /**
     * @brief Make a null move. (Switches the side to move)
     */
    void makeNullMove() {
        prev_states_.emplace_back(key_, cr_, ep_sq_, hfm_, Piece::NONE);

        key_ ^= Zobrist::sideToMove();
        if (ep_sq_ != Square::NO_SQ) key_ ^= Zobrist::enpassant(ep_sq_.file());
        ep_sq_ = Square::NO_SQ;

        stm_ = ~stm_;

        plies_++;
    }

    /**
     * @brief Unmake a null move. (Switches the side to move)
     */
    void unmakeNullMove() {
        const auto &prev = prev_states_.back();

        ep_sq_ = prev.enpassant;
        cr_    = prev.castling;
        hfm_   = prev.half_moves;
        key_   = prev.hash;

        plies_--;

        stm_ = ~stm_;

        prev_states_.pop_back();
    }

    /**
     * @brief Get the occupancy bitboard for the color.
     * @param color
     * @return
     */
    [[nodiscard]] Bitboard us(Color color) const { return occ_bb_[color]; }

    /**
     * @brief Get the occupancy bitboard for the opposite color.
     * @param color
     * @return
     */
    [[nodiscard]] Bitboard them(Color color) const { return us(~color); }

    /**
     * @brief Get the occupancy bitboard for both colors.
     * Faster than calling all() or us(Color::WHITE) | us(Color::BLACK).
     * @return
     */
    [[nodiscard]] Bitboard occ() const { return occ_bb_[0] | occ_bb_[1]; }

    /**
     * @brief Get the occupancy bitboard for all pieces, should be only used internally.
     * @return
     */
    [[nodiscard]] Bitboard all() const { return us(Color::WHITE) | us(Color::BLACK); }

    /**
     * @brief Returns the square of the king for a certain color
     * @param color
     * @return
     */
    [[nodiscard]] Square kingSq(Color color) const {
        assert(pieces(PieceType::KING, color) != Bitboard(0));
        return pieces(PieceType::KING, color).lsb();
    }

    /**
     * @brief Returns all pieces of a certain type and color
     * @param type
     * @param color
     * @return
     */
    [[nodiscard]] Bitboard pieces(PieceType type, Color color) const { return pieces_bb_[type] & occ_bb_[color]; }

    /**
     * @brief Returns all pieces of a certain type
     * @param type
     * @return
     */
    [[nodiscard]] Bitboard pieces(PieceType type) const {
        return pieces(type, Color::WHITE) | pieces(type, Color::BLACK);
    }

    /**
     * @brief Returns either the piece or the piece type on a square
     * @tparam T
     * @param sq
     * @return
     */
    template <typename T = Piece>
    [[nodiscard]] T at(Square sq) const {
        assert(sq.index() < 64 && sq.index() >= 0);

        if constexpr (std::is_same_v<T, PieceType>) {
            return board_[sq.index()].type();
        } else {
            return board_[sq.index()];
        }
    }

    /**
     * @brief Checks if a move is a capture, enpassant moves are also considered captures.
     * @param move
     * @return
     */
    bool isCapture(const Move move) const {
        return (at(move.to()) != Piece::NONE && move.typeOf() != Move::CASTLING) || move.typeOf() == Move::ENPASSANT;
    }

    /**
     * @brief Get the current zobrist hash key of the board
     * @return
     */
    [[nodiscard]] U128 hash() const { return key_; }
    [[nodiscard]] Color sideToMove() const { return stm_; }
    [[nodiscard]] Square enpassantSq() const { return ep_sq_; }
    [[nodiscard]] CastlingRights castlingRights() const { return cr_; }
    [[nodiscard]] std::uint32_t halfMoveClock() const { return hfm_; }
    [[nodiscard]] std::uint32_t fullMoveNumber() const { return 1 + plies_ / 2; }

    void set960(bool is960) {
        chess960_ = is960;
        if (!original_fen_.empty()) setFen(original_fen_);
    }

    /**
     * @brief Checks if the current position is a chess960, aka. FRC/DFRC position.
     * @return
     */
    [[nodiscard]] bool chess960() const { return chess960_; }

    /**
     * @brief Get the castling rights as a string
     * @return
     */
    [[nodiscard]] std::string getCastleString() const {
        static const auto get_file = [](const CastlingRights &cr, Color c, CastlingRights::Side side) {
            auto file = static_cast<std::string>(cr.getRookFile(c, side));
            return c == Color::WHITE ? std::toupper(file[0]) : file[0];
        };

        if (chess960_) {
            std::string ss;

            for (auto color : {Color::WHITE, Color::BLACK})
                for (auto side : {CastlingRights::Side::KING_SIDE, CastlingRights::Side::QUEEN_SIDE})
                    if (cr_.has(color, side)) ss += get_file(cr_, color, side);

            return ss;
        }

        std::string ss;

        if (cr_.has(Color::WHITE, CastlingRights::Side::KING_SIDE)) ss += 'K';
        if (cr_.has(Color::WHITE, CastlingRights::Side::QUEEN_SIDE)) ss += 'Q';
        if (cr_.has(Color::BLACK, CastlingRights::Side::KING_SIDE)) ss += 'k';
        if (cr_.has(Color::BLACK, CastlingRights::Side::QUEEN_SIDE)) ss += 'q';

        return ss;
    }

    /**
     * @brief Checks if the current position is a repetition, set this to 1 if
     * you are writing a chess engine.
     * @param count
     * @return
     */
    [[nodiscard]] bool isRepetition(int count = 2) const {
        uint8_t c = 0;

        // We start the loop from the back and go forward in moves, at most to the
        // last move which reset the half-move counter because repetitions cant
        // be across half-moves.
        const auto size = static_cast<int>(prev_states_.size());

        for (int i = size - 2; i >= 0 && i >= size - hfm_ - 1; i -= 2) {
            if (prev_states_[i].hash == key_) c++;
            if (c == count) return true;
        }

        return false;
    }

    /**
     * @brief Checks if the current position is a draw by 50 move rule.
     * Keep in mind that by the rules of chess, if the position has 50 half
     * moves it's not necessarily a draw, since checkmate has higher priority,
     * call getHalfMoveDrawType,
     * to determine whether the position is a draw or checkmate.
     * @return
     */
    [[nodiscard]] bool isHalfMoveDraw() const { return hfm_ >= 100; }

    /**
     * @brief Only call this function if isHalfMoveDraw() returns true.
     * @return
     */
    [[nodiscard]] std::pair<GameResultReason, GameResult> getHalfMoveDrawType() const {
        Movelist movelist;
        movegen::legalmoves(movelist, *this);

        if (movelist.empty() && inCheck()) {
            return {GameResultReason::CHECKMATE, GameResult::LOSE};
        }

        return {GameResultReason::FIFTY_MOVE_RULE, GameResult::DRAW};
    }

    /**
     * @brief Basic check if the current position is a draw by insufficient material.
     * @return
     */
    [[nodiscard]] bool isInsufficientMaterial() const {
        const auto count = occ().count();

        // only kings, draw
        if (count == 2) return true;

        // only bishop + knight, cant mate
        if (count == 3) {
            if (pieces(PieceType::BISHOP, Color::WHITE) || pieces(PieceType::BISHOP, Color::BLACK)) return true;
            if (pieces(PieceType::KNIGHT, Color::WHITE) || pieces(PieceType::KNIGHT, Color::BLACK)) return true;
        }

        // same colored bishops, cant mate
        if (count == 4) {
            if (pieces(PieceType::BISHOP, Color::WHITE) && pieces(PieceType::BISHOP, Color::BLACK) &&
                Square::same_color(pieces(PieceType::BISHOP, Color::WHITE).lsb(),
                                   pieces(PieceType::BISHOP, Color::BLACK).lsb()))
                return true;

            // one side with two bishops which have the same color
            auto white_bishops = pieces(PieceType::BISHOP, Color::WHITE);
            auto black_bishops = pieces(PieceType::BISHOP, Color::BLACK);

            if (white_bishops.count() == 2) {
                if (Square::same_color(white_bishops.lsb(), white_bishops.msb())) return true;
            } else if (black_bishops.count() == 2) {
                if (Square::same_color(black_bishops.lsb(), black_bishops.msb())) return true;
            }
        }

        return false;
    }

    /**
     * @brief Checks if the game is over. Returns GameResultReason::NONE if the game is not over.
     * This function calculates all legal moves for the current position to check if the game is over.
     * If you are writing a chess engine you should not use this function.
     * @return
     */
    [[nodiscard]] std::pair<GameResultReason, GameResult> isGameOver() const {
        if (isHalfMoveDraw()) return getHalfMoveDrawType();
        if (isInsufficientMaterial()) return {GameResultReason::INSUFFICIENT_MATERIAL, GameResult::DRAW};
        if (isRepetition()) return {GameResultReason::THREEFOLD_REPETITION, GameResult::DRAW};

        Movelist movelist;
        movegen::legalmoves(movelist, *this);

        if (movelist.empty()) {
            if (inCheck()) return {GameResultReason::CHECKMATE, GameResult::LOSE};
            return {GameResultReason::STALEMATE, GameResult::DRAW};
        }

        return {GameResultReason::NONE, GameResult::NONE};
    }

    /**
     * @brief Checks if a square is attacked by the given color.
     * @param square
     * @param color
     * @return
     */
    [[nodiscard]] bool isAttacked(Square square, Color color) const {
        // cheap checks first
        if (attacks::pawn(~color, square) & pieces(PieceType::PAWN, color)) return true;
        if (attacks::knight(square) & pieces(PieceType::KNIGHT, color)) return true;
        if (attacks::king(square) & pieces(PieceType::KING, color)) return true;

        if (attacks::bishop(square, occ()) & (pieces(PieceType::BISHOP, color) | pieces(PieceType::QUEEN, color)))
            return true;

        if (attacks::rook(square, occ()) & (pieces(PieceType::ROOK, color) | pieces(PieceType::QUEEN, color)))
            return true;

        return false;
    }

    /**
     * @brief Checks if the current side to move is in check
     * @return
     */
    [[nodiscard]] bool inCheck() const { return isAttacked(kingSq(stm_), ~stm_); }

    /**
     * @brief Checks if the given color has at least 1 piece thats not pawn and not king
     * @param color
     * @return
     */
    [[nodiscard]] bool hasNonPawnMaterial(Color color) const {
        return bool(pieces(PieceType::KNIGHT, color) | pieces(PieceType::BISHOP, color) |
                    pieces(PieceType::ROOK, color) | pieces(PieceType::QUEEN, color));
    }

    /**
     * @brief Calculates the zobrist hash key of the board, expensive! Prefer using hash().
     * @return
     */
    [[nodiscard]] U128 zobrist() const {
        U128 hash_key = 0ULL;

        auto wPieces = us(Color::WHITE);
        auto bPieces = us(Color::BLACK);

        while (wPieces.getBits()) {
            const Square sq = wPieces.pop();
            hash_key ^= Zobrist::piece(at(sq), sq);
        }

        while (bPieces.getBits()) {
            const Square sq = bPieces.pop();
            hash_key ^= Zobrist::piece(at(sq), sq);
        }

        U128 ep_hash = 0ULL;
        if (ep_sq_ != Square::NO_SQ) ep_hash ^= Zobrist::enpassant(ep_sq_.file());

        U128 stm_hash = 0ULL;
        if (stm_ == Color::WHITE) stm_hash ^= Zobrist::sideToMove();

        U128 castling_hash = 0ULL;
        castling_hash ^= Zobrist::castling(cr_.hashIndex());

        return hash_key ^ ep_hash ^ stm_hash ^ castling_hash;
    }

    friend std::ostream &operator<<(std::ostream &os, const Board &board);

    /**
     * @brief Compresses the board into a PackedBoard.
     */
    class Compact {
        friend class Board;
        Compact() = default;

       public:
        /**
         * @brief Compresses the board into a PackedBoard
         * @param board
         * @return
         */
        static PackedBoard encode(const Board &board) { return encodeState(board); }

        static PackedBoard encode(std::string_view fen, bool chess960 = false) { return encodeState(fen, chess960); }

        /**
         * @brief Creates a Board object from a PackedBoard
         * @param compressed
         * @param chess960 If the board is a chess960 position, set this to true
         * @return
         */
        static Board decode(const PackedBoard &compressed, bool chess960 = false) {
            Board board     = Board(PrivateCtor::CREATE);
            board.chess960_ = chess960;
            decode(board, compressed);
            return board;
        }

       private:
        /**
         * A compact board representation can be achieved in 24 bytes,
         * we use 8 bytes (64bit) to store the occupancy bitboard,
         * and 16 bytes (128bit) to store the pieces (plus some special information).
         *
         * Each of the 16 bytes can store 2 pieces, since chess only has 12 different pieces,
         * we can represent the pieces from 0 to 11 in 4 bits (a nibble) and use the other 4 bit for
         * the next piece.
         * Since we need to store information about enpassant, castling rights and the side to move,
         * we can use the remaining 4 bits to store this information.
         *
         * However we need to store the information and the piece information together.
         * This means in our case that
         * 12 -> enpassant + a pawn, we can deduce the color of the pawn from the rank of the square
         * 13 -> white rook with castling rights, we later use the file to deduce if it's a short or long castle
         * 14 -> black rook with castling rights, we later use the file to deduce if it's a short or long castle
         * 15 -> black king and black is side to move
         *
         * We will later deduce the square of the pieces from the occupancy bitboard.
         */
        static PackedBoard encodeState(const Board &board) {
            PackedBoard packed{};

            packed[0] = board.occ().getBits() >> 56;
            packed[1] = (board.occ().getBits() >> 48) & 0xFF;
            packed[2] = (board.occ().getBits() >> 40) & 0xFF;
            packed[3] = (board.occ().getBits() >> 32) & 0xFF;
            packed[4] = (board.occ().getBits() >> 24) & 0xFF;
            packed[5] = (board.occ().getBits() >> 16) & 0xFF;
            packed[6] = (board.occ().getBits() >> 8) & 0xFF;
            packed[7] = board.occ().getBits() & 0xFF;

            auto offset = 8 * 2;
            auto occ    = board.occ();

            while (occ) {
                // we now fill the packed array, since our convertedpiece only actually needs 4 bits,
                // we can store 2 pieces in one byte.
                const auto sq      = Square(occ.pop());
                const auto shift   = (offset % 2 == 0 ? 4 : 0);
                const auto meaning = convertMeaning(board.cr_, board.sideToMove(), board.ep_sq_, sq, board.at(sq));
                const auto nibble  = meaning << shift;

                packed[offset / 2] |= nibble;
                offset++;
            }

            return packed;
        }

        static PackedBoard encodeState(std::string_view fen, bool chess960 = false) {
            // fallback to slower method
            if (chess960) {
                Board board = Board(fen, true);
                return encodeState(board);
            }

            PackedBoard packed{};

            while (fen[0] == ' ') fen.remove_prefix(1);

            const auto params     = split_string_view<6>(fen);
            const auto position   = params[0].has_value() ? *params[0] : "";
            const auto move_right = params[1].has_value() ? *params[1] : "w";
            const auto castling   = params[2].has_value() ? *params[2] : "-";
            const auto en_passant = params[3].has_value() ? *params[3] : "-";

            const auto ep  = en_passant == "-" ? Square::NO_SQ : Square(en_passant);
            const auto stm = (move_right == "w") ? Color::WHITE : Color::BLACK;

            CastlingRights cr;

            for (char i : castling) {
                if (i == '-') break;

                const auto king_side  = CastlingRights::Side::KING_SIDE;
                const auto queen_side = CastlingRights::Side::QUEEN_SIDE;

                if (i == 'K') cr.setCastlingRight(Color::WHITE, king_side, File::FILE_H);
                if (i == 'Q') cr.setCastlingRight(Color::WHITE, queen_side, File::FILE_A);
                if (i == 'k') cr.setCastlingRight(Color::BLACK, king_side, File::FILE_H);
                if (i == 'q') cr.setCastlingRight(Color::BLACK, queen_side, File::FILE_A);

                assert(i == 'K' || i == 'Q' || i == 'k' || i == 'q');

                continue;
            }

            const auto parts = split_string_view<8>(position, '/');

            auto offset = 8 * 2;
            auto square = 0;
            auto occ    = Bitboard(0);

            for (auto i = parts.rbegin(); i != parts.rend(); i++) {
                auto part = *i;

                for (char curr : *part) {
                    if (isdigit(curr)) {
                        square += (curr - '0');
                    } else if (curr == '/') {
                        square++;
                    } else {
                        const auto p     = Piece(std::string_view(&curr, 1));
                        const auto shift = (offset % 2 == 0 ? 4 : 0);

                        packed[offset / 2] |= convertMeaning(cr, stm, ep, Square(square), p) << shift;
                        offset++;

                        occ.set(square);
                        ++square;
                    }
                }
            }

            packed[0] = occ.getBits() >> 56;
            packed[1] = (occ.getBits() >> 48) & 0xFF;
            packed[2] = (occ.getBits() >> 40) & 0xFF;
            packed[3] = (occ.getBits() >> 32) & 0xFF;
            packed[4] = (occ.getBits() >> 24) & 0xFF;
            packed[5] = (occ.getBits() >> 16) & 0xFF;
            packed[6] = (occ.getBits() >> 8) & 0xFF;
            packed[7] = occ.getBits() & 0xFF;

            return packed;
        }

        static void decode(Board &board, const PackedBoard &compressed) {
            Bitboard occupied = 0ull;

            for (int i = 0; i < 8; i++) {
                occupied |= Bitboard(compressed[i]) << (56 - i * 8);
            }

            int offset           = 16;
            int white_castle_idx = 0, black_castle_idx = 0;
            File white_castle[2] = {File::NO_FILE, File::NO_FILE};
            File black_castle[2] = {File::NO_FILE, File::NO_FILE};

            // clear board state

            board.hfm_   = 0;
            board.plies_ = 0;

            board.stm_ = Color::WHITE;

            board.cr_.clear();
            board.prev_states_.clear();
            board.original_fen_.clear();

            board.occ_bb_.fill(0ULL);
            board.pieces_bb_.fill(0ULL);
            board.board_.fill(Piece::NONE);

            // place pieces back on the board
            while (occupied) {
                const auto sq     = Square(occupied.pop());
                const auto nibble = compressed[offset / 2] >> (offset % 2 == 0 ? 4 : 0) & 0b1111;
                const auto piece  = convertPiece(nibble);

                if (piece != Piece::NONE) {
                    board.placePiece(piece, sq);

                    offset++;
                    continue;
                }

                // Piece has a special meaning, interpret it from the raw integer
                // pawn with ep square behind it
                if (nibble == 12) {
                    board.ep_sq_ = sq.ep_square();
                    // depending on the rank this is a white or black pawn
                    auto color = sq.rank() == Rank::RANK_4 ? Color::WHITE : Color::BLACK;
                    board.placePiece(Piece(PieceType::PAWN, color), sq);
                }
                // castling rights for white
                else if (nibble == 13) {
                    assert(white_castle_idx < 2);
                    white_castle[white_castle_idx++] = sq.file();
                    board.placePiece(Piece(PieceType::ROOK, Color::WHITE), sq);
                }
                // castling rights for black
                else if (nibble == 14) {
                    assert(black_castle_idx < 2);
                    black_castle[black_castle_idx++] = sq.file();
                    board.placePiece(Piece(PieceType::ROOK, Color::BLACK), sq);
                }
                // black to move
                else if (nibble == 15) {
                    board.stm_ = Color::BLACK;
                    board.placePiece(Piece(PieceType::KING, Color::BLACK), sq);
                }

                offset++;
            }

            // reapply castling
            for (int i = 0; i < 2; i++) {
                if (white_castle[i] != File::NO_FILE) {
                    const auto king_sq = board.kingSq(Color::WHITE);
                    const auto file    = white_castle[i];
                    const auto side    = CastlingRights::closestSide(file, king_sq.file());

                    board.cr_.setCastlingRight(Color::WHITE, side, file);
                }

                if (black_castle[i] != File::NO_FILE) {
                    const auto king_sq = board.kingSq(Color::BLACK);
                    const auto file    = black_castle[i];
                    const auto side    = CastlingRights::closestSide(file, king_sq.file());

                    board.cr_.setCastlingRight(Color::BLACK, side, file);
                }
            }

            if (board.stm_ == Color::BLACK) {
                board.plies_++;
            }

            board.key_ = board.zobrist();
        }

        // 1:1 mapping of Piece::internal() to the compressed piece
        static std::uint8_t convertPiece(Piece piece) { return int(piece.internal()); }

        // for pieces with a special meaning return Piece::NONE since this is otherwise not used
        static Piece convertPiece(std::uint8_t piece) {
            if (piece >= 12) return Piece::NONE;
            return Piece(Piece::underlying(piece));
        }

        // 12 => theres an ep square behind the pawn, rank will be deduced from the rank
        // 13 => any white rook with castling rights, side will be deduced from the file
        // 14 => any black rook with castling rights, side will be deduced from the file
        // 15 => black king and black is side to move
        static std::uint8_t convertMeaning(const CastlingRights &cr, Color stm, Square ep, Square sq, Piece piece) {
            if (piece.type() == PieceType::PAWN && ep != Square::NO_SQ) {
                if (Square(static_cast<int>(sq.index()) ^ 8) == ep) return 12;
            }

            if (piece.type() == PieceType::ROOK) {
                if (piece.color() == Color::WHITE && Square::back_rank(sq, Color::WHITE) &&
                    (cr.getRookFile(Color::WHITE, CastlingRights::Side::KING_SIDE) == sq.file() ||
                     cr.getRookFile(Color::WHITE, CastlingRights::Side::QUEEN_SIDE) == sq.file()))
                    return 13;
                if (piece.color() == Color::BLACK && Square::back_rank(sq, Color::BLACK) &&
                    (cr.getRookFile(Color::BLACK, CastlingRights::Side::KING_SIDE) == sq.file() ||
                     cr.getRookFile(Color::BLACK, CastlingRights::Side::QUEEN_SIDE) == sq.file()))
                    return 14;
            }

            if (piece.type() == PieceType::KING && piece.color() == Color::BLACK && stm == Color::BLACK) {
                return 15;
            }

            return convertPiece(piece);
        }
    };

   protected:
    virtual void placePiece(Piece piece, Square sq) { placePieceInternal(piece, sq); }

    virtual void removePiece(Piece piece, Square sq) { removePieceInternal(piece, sq); }

    std::vector<State> prev_states_;

    std::array<Bitboard, 6> pieces_bb_ = {};
    std::array<Bitboard, 2> occ_bb_    = {};
    std::array<Piece, 64> board_       = {};

    U128 key_          = 0ULL;
    CastlingRights cr_ = {};
    uint16_t plies_    = 0;
    Color stm_         = Color::WHITE;
    Square ep_sq_      = Square::NO_SQ;
    uint8_t hfm_       = 0;

    bool chess960_ = false;

   private:
    void removePieceInternal(Piece piece, Square sq) {
        assert(board_[sq.index()] == piece && piece != Piece::NONE);

        auto type  = piece.type();
        auto color = piece.color();
        auto index = sq.index();

        assert(type != PieceType::NONE);
        assert(color != Color::NONE);
        assert(index >= 0 && index < 64);

        pieces_bb_[type].clear(index);
        occ_bb_[color].clear(index);
        board_[index] = Piece::NONE;
    }

    void placePieceInternal(Piece piece, Square sq) {
        assert(board_[sq.index()] == Piece::NONE);

        auto type  = piece.type();
        auto color = piece.color();
        auto index = sq.index();

        assert(type != PieceType::NONE);
        assert(color != Color::NONE);
        assert(index >= 0 && index < 64);

        pieces_bb_[type].set(index);
        occ_bb_[color].set(index);
        board_[index] = piece;
    }

    template <bool ctor = false>
    void setFenInternal(std::string_view fen) {
        original_fen_ = fen;

        occ_bb_.fill(0ULL);
        pieces_bb_.fill(0ULL);
        board_.fill(Piece::NONE);

        // find leading whitespaces and remove them
        while (fen[0] == ' ') fen.remove_prefix(1);

        const auto params     = split_string_view<6>(fen);
        const auto position   = params[0].has_value() ? *params[0] : "";
        const auto move_right = params[1].has_value() ? *params[1] : "w";
        const auto castling   = params[2].has_value() ? *params[2] : "-";
        const auto en_passant = params[3].has_value() ? *params[3] : "-";
        const auto half_move  = params[4].has_value() ? *params[4] : "0";
        const auto full_move  = params[5].has_value() ? *params[5] : "1";

        static auto parseStringViewToInt = [](std::string_view sv) -> std::optional<int> {
            if (!sv.empty() && sv.back() == ';') sv.remove_suffix(1);
#ifndef CHESS_NO_EXCEPTIONS
            try {
                size_t pos;
                int value = std::stoi(std::string(sv), &pos);
                if (pos == sv.size()) return value;
            } catch (...) {
            }
#else
            size_t pos;
            int value = std::stoi(std::string(sv), &pos);
            if (pos == sv.size()) return value;
#endif
            return std::nullopt;
        };

        // Half move clock
        hfm_ = parseStringViewToInt(half_move).value_or(0);

        // Full move number
        plies_ = parseStringViewToInt(full_move).value_or(1);

        plies_ = plies_ * 2 - 2;
        ep_sq_ = en_passant == "-" ? Square::NO_SQ : Square(en_passant);
        stm_   = (move_right == "w") ? Color::WHITE : Color::BLACK;
        key_   = 0ULL;
        cr_.clear();
        prev_states_.clear();

        if (stm_ == Color::BLACK) {
            plies_++;
        } else {
            key_ ^= Zobrist::sideToMove();
        }

        auto square = 56;
        for (char curr : position) {
            if (isdigit(curr)) {
                square += (curr - '0');
            } else if (curr == '/') {
                square -= 16;
            } else {
                auto p = Piece(std::string_view(&curr, 1));

                // prevent warnings about virtual method bypassing virtual dispatch
                if constexpr (ctor) {
                    placePieceInternal(p, Square(square));
                } else {
                    placePiece(p, square);
                }

                key_ ^= Zobrist::piece(p, Square(square));
                ++square;
            }
        }

        static const auto find_rook = [](const Board &board, CastlingRights::Side side, Color color) {
            const auto king_side = CastlingRights::Side::KING_SIDE;
            const auto king_sq   = board.kingSq(color);
            const auto sq_corner = Square(side == king_side ? Square::SQ_H1 : Square::SQ_A1).relative_square(color);

            const auto start = side == king_side ? king_sq + 1 : king_sq - 1;

            for (Square sq = start; (side == king_side ? sq <= sq_corner : sq >= sq_corner);
                 (side == king_side ? sq++ : sq--)) {
                if (board.at<PieceType>(sq) == PieceType::ROOK && board.at(sq).color() == color) {
                    return sq.file();
                }
            }

#ifndef CHESS_NO_EXCEPTIONS
            throw std::runtime_error("Invalid position");
#endif

            return File(File::NO_FILE);
        };

        for (char i : castling) {
            if (i == '-') break;

            const auto king_side  = CastlingRights::Side::KING_SIDE;
            const auto queen_side = CastlingRights::Side::QUEEN_SIDE;

            if (!chess960_) {
                if (i == 'K') cr_.setCastlingRight(Color::WHITE, king_side, File::FILE_H);
                if (i == 'Q') cr_.setCastlingRight(Color::WHITE, queen_side, File::FILE_A);
                if (i == 'k') cr_.setCastlingRight(Color::BLACK, king_side, File::FILE_H);
                if (i == 'q') cr_.setCastlingRight(Color::BLACK, queen_side, File::FILE_A);

                continue;
            }

            // chess960 castling detection

            const auto color   = isupper(i) ? Color::WHITE : Color::BLACK;
            const auto king_sq = kingSq(color);

            // find rook on the right side of the king
            if (i == 'K' || i == 'k') {
                cr_.setCastlingRight(color, king_side, find_rook(*this, king_side, color));
            }
            // find rook on the left side of the king
            else if (i == 'Q' || i == 'q') {
                cr_.setCastlingRight(color, queen_side, find_rook(*this, queen_side, color));
            }
            // correct frc castling encoding
            else {
                const auto file = File(std::string_view(&i, 1));
                const auto side = CastlingRights::closestSide(file, king_sq.file());
                cr_.setCastlingRight(color, side, file);
            }
        }

        // check if ep square itself is valid
        if (ep_sq_ != Square::NO_SQ && !((ep_sq_.rank() == Rank::RANK_3 && stm_ == Color::BLACK) ||
                                         (ep_sq_.rank() == Rank::RANK_6 && stm_ == Color::WHITE))) {
            ep_sq_ = Square::NO_SQ;
        }

        // check if ep square is valid, i.e. if there is a pawn that can capture it
        if (ep_sq_ != Square::NO_SQ) {
            bool valid;

            if (stm_ == Color::WHITE) {
                valid = movegen::isEpSquareValid<Color::WHITE>(*this, ep_sq_);
            } else {
                valid = movegen::isEpSquareValid<Color::BLACK>(*this, ep_sq_);
            }

            if (!valid)
                ep_sq_ = Square::NO_SQ;
            else
                key_ ^= Zobrist::enpassant(ep_sq_.file());
        }

        key_ ^= Zobrist::castling(cr_.hashIndex());

        assert(key_ == zobrist());
    }

    template <int N>
    std::array<std::optional<std::string_view>, N> static split_string_view(std::string_view fen,
                                                                            char delimiter = ' ') {
        std::array<std::optional<std::string_view>, N> arr = {};

        std::size_t start = 0;
        std::size_t end   = 0;

        for (std::size_t i = 0; i < N; i++) {
            end = fen.find(delimiter, start);
            if (end == std::string::npos) {
                arr[i] = fen.substr(start);
                break;
            }
            arr[i] = fen.substr(start, end - start);
            start  = end + 1;
        }

        return arr;
    }

    // store the original fen string
    // useful when setting up a frc position and the user called set960(true) afterwards
    std::string original_fen_;
};

inline std::string u128ToHex(__uint128_t val) {
    std::ostringstream oss;
    oss << "0x" << std::hex;
    oss << static_cast<uint64_t>(val >> 64);
    oss << std::setw(16) << std::setfill('0') << static_cast<uint64_t>(val);
    return oss.str();
}

inline std::ostream &operator<<(std::ostream &os, const Board &b) {
    for (int i = 63; i >= 0; i -= 8) {
        for (int j = 7; j >= 0; j--) {
            os << " " << static_cast<std::string>(b.board_[i - j]);
        }

        os << " \n";
    }

    os << "\n\n";
    os << "Side to move: " << static_cast<int>(b.stm_.internal()) << "\n";
    os << "Castling rights: " << b.getCastleString() << "\n";
    os << "Halfmoves: " << b.halfMoveClock() << "\n";
    os << "Fullmoves: " << b.fullMoveNumber() << "\n";
    os << "EP: " << b.ep_sq_.index() << "\n";
    os << "Hash: " << u128ToHex(b.key_) << "\n";

    os << std::endl;

    return os;
}
}  // namespace  chess

namespace chess {

template <Direction direction>
[[nodiscard]] inline constexpr Bitboard attacks::shift(const Bitboard b) {
    switch (direction) {
        case Direction::NORTH:
            return b << 8;
        case Direction::SOUTH:
            return b >> 8;
        case Direction::NORTH_WEST:
            return (b & ~MASK_FILE[0]) << 7;
        case Direction::WEST:
            return (b & ~MASK_FILE[0]) >> 1;
        case Direction::SOUTH_WEST:
            return (b & ~MASK_FILE[0]) >> 9;
        case Direction::NORTH_EAST:
            return (b & ~MASK_FILE[7]) << 9;
        case Direction::EAST:
            return (b & ~MASK_FILE[7]) << 1;
        case Direction::SOUTH_EAST:
            return (b & ~MASK_FILE[7]) >> 7;
    }

        // c++23
#if defined(__cpp_lib_unreachable) && __cpp_lib_unreachable >= 202202L
    std::unreachable();
#endif

    assert(false);

    return {};
}

template <Color::underlying c>
[[nodiscard]] inline Bitboard attacks::pawnLeftAttacks(const Bitboard pawns) {
    return c == Color::WHITE ? (pawns << 7) & ~MASK_FILE[static_cast<int>(File::FILE_H)]
                             : (pawns >> 7) & ~MASK_FILE[static_cast<int>(File::FILE_A)];
}

template <Color::underlying c>
[[nodiscard]] inline Bitboard attacks::pawnRightAttacks(const Bitboard pawns) {
    return c == Color::WHITE ? (pawns << 9) & ~MASK_FILE[static_cast<int>(File::FILE_A)]
                             : (pawns >> 9) & ~MASK_FILE[static_cast<int>(File::FILE_H)];
}

[[nodiscard]] inline Bitboard attacks::pawn(Color c, Square sq) noexcept { return PawnAttacks[c][sq.index()]; }

[[nodiscard]] inline Bitboard attacks::knight(Square sq) noexcept { return KnightAttacks[sq.index()]; }

[[nodiscard]] inline Bitboard attacks::bishop(Square sq, Bitboard occupied) noexcept {
    return BishopTable[sq.index()].attacks[BishopTable[sq.index()](occupied)];
}

[[nodiscard]] inline Bitboard attacks::rook(Square sq, Bitboard occupied) noexcept {
    return RookTable[sq.index()].attacks[RookTable[sq.index()](occupied)];
}

[[nodiscard]] inline Bitboard attacks::queen(Square sq, Bitboard occupied) noexcept {
    return bishop(sq, occupied) | rook(sq, occupied);
}

[[nodiscard]] inline Bitboard attacks::king(Square sq) noexcept { return KingAttacks[sq.index()]; }

[[nodiscard]] inline Bitboard attacks::attackers(const Board &board, Color color, Square square) noexcept {
    const auto queens   = board.pieces(PieceType::QUEEN, color);
    const auto occupied = board.occ();

    // using the fact that if we can attack PieceType from square, they can attack us back
    auto atks = (pawn(~color, square) & board.pieces(PieceType::PAWN, color));
    atks |= (knight(square) & board.pieces(PieceType::KNIGHT, color));
    atks |= (bishop(square, occupied) & (board.pieces(PieceType::BISHOP, color) | queens));
    atks |= (rook(square, occupied) & (board.pieces(PieceType::ROOK, color) | queens));
    atks |= (king(square) & board.pieces(PieceType::KING, color));

    return atks & occupied;
}

[[nodiscard]] inline Bitboard attacks::bishopAttacks(Square sq, Bitboard occupied) {
    Bitboard attacks = 0ULL;

    int r, f;

    int br = sq.rank();
    int bf = sq.file();

    for (r = br + 1, f = bf + 1; Square::is_valid(static_cast<Rank>(r), static_cast<File>(f)); r++, f++) {
        auto s = Square(static_cast<Rank>(r), static_cast<File>(f)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    for (r = br - 1, f = bf + 1; Square::is_valid(static_cast<Rank>(r), static_cast<File>(f)); r--, f++) {
        auto s = Square(static_cast<Rank>(r), static_cast<File>(f)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    for (r = br + 1, f = bf - 1; Square::is_valid(static_cast<Rank>(r), static_cast<File>(f)); r++, f--) {
        auto s = Square(static_cast<Rank>(r), static_cast<File>(f)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    for (r = br - 1, f = bf - 1; Square::is_valid(static_cast<Rank>(r), static_cast<File>(f)); r--, f--) {
        auto s = Square(static_cast<Rank>(r), static_cast<File>(f)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    return attacks;
}

[[nodiscard]] inline Bitboard attacks::rookAttacks(Square sq, Bitboard occupied) {
    Bitboard attacks = 0ULL;

    int r, f;

    int rr = sq.rank();
    int rf = sq.file();

    for (r = rr + 1; Square::is_valid(static_cast<Rank>(r), static_cast<File>(rf)); r++) {
        auto s = Square(static_cast<Rank>(r), static_cast<File>(rf)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    for (r = rr - 1; Square::is_valid(static_cast<Rank>(r), static_cast<File>(rf)); r--) {
        auto s = Square(static_cast<Rank>(r), static_cast<File>(rf)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    for (f = rf + 1; Square::is_valid(static_cast<Rank>(rr), static_cast<File>(f)); f++) {
        auto s = Square(static_cast<Rank>(rr), static_cast<File>(f)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    for (f = rf - 1; Square::is_valid(static_cast<Rank>(rr), static_cast<File>(f)); f--) {
        auto s = Square(static_cast<Rank>(rr), static_cast<File>(f)).index();
        attacks.set(s);
        if (occupied.check(s)) break;
    }

    return attacks;
}

inline void attacks::initSliders(Square sq, Magic table[], U64 magic,
                                 const std::function<Bitboard(Square, Bitboard)> &attacks) {
    // The edges of the board are not considered for the attacks
    // i.e. for the sq h7 edges will be a1-h1, a1-a8, a8-h8, ignoring the edge of the current square
    const Bitboard edges = ((Bitboard(Rank::RANK_1) | Bitboard(Rank::RANK_8)) & ~Bitboard(sq.rank())) |
                           ((Bitboard(File::FILE_A) | Bitboard(File::FILE_H)) & ~Bitboard(sq.file()));

    U64 occ = 0ULL;

    auto &table_sq = table[sq.index()];

    table_sq.magic = magic;
    table_sq.mask  = (attacks(sq, occ) & ~edges).getBits();
    table_sq.shift = 64 - Bitboard(table_sq.mask).count();

    if (sq < 64 - 1) {
        table[sq.index() + 1].attacks = table_sq.attacks + (1ull << Bitboard(table_sq.mask).count());
    }

    do {
        table_sq.attacks[table_sq(occ)] = attacks(sq, occ);
        occ                             = (occ - table_sq.mask) & table_sq.mask;
    } while (occ);
}

inline void attacks::initAttacks() {
    BishopTable[0].attacks = BishopAttacks;
    RookTable[0].attacks   = RookAttacks;

    for (int i = 0; i < 64; i++) {
        initSliders(static_cast<Square>(i), BishopTable, BishopMagics[i], bishopAttacks);
        initSliders(static_cast<Square>(i), RookTable, RookMagics[i], rookAttacks);
    }
}
}  // namespace chess



namespace chess {

inline auto movegen::init_squares_between() {
    std::array<std::array<Bitboard, 64>, 64> squares_between_bb{};
    Bitboard sqs = 0;

    for (Square sq1 = 0; sq1 < 64; ++sq1) {
        for (Square sq2 = 0; sq2 < 64; ++sq2) {
            sqs = Bitboard::fromSquare(sq1) | Bitboard::fromSquare(sq2);
            if (sq1 == sq2)
                squares_between_bb[sq1.index()][sq2.index()].clear();
            else if (sq1.file() == sq2.file() || sq1.rank() == sq2.rank())
                squares_between_bb[sq1.index()][sq2.index()] = attacks::rook(sq1, sqs) & attacks::rook(sq2, sqs);
            else if (sq1.diagonal_of() == sq2.diagonal_of() || sq1.antidiagonal_of() == sq2.antidiagonal_of())
                squares_between_bb[sq1.index()][sq2.index()] = attacks::bishop(sq1, sqs) & attacks::bishop(sq2, sqs);
        }
    }

    return squares_between_bb;
}

template <Color::underlying c>
[[nodiscard]] inline std::pair<Bitboard, int> movegen::checkMask(const Board &board, Square sq) {
    const auto opp_knight = board.pieces(PieceType::KNIGHT, ~c);
    const auto opp_bishop = board.pieces(PieceType::BISHOP, ~c);
    const auto opp_rook   = board.pieces(PieceType::ROOK, ~c);
    const auto opp_queen  = board.pieces(PieceType::QUEEN, ~c);

    const auto opp_pawns = board.pieces(PieceType::PAWN, ~c);

    int checks = 0;

    // check for knight checks
    Bitboard knight_attacks = attacks::knight(sq) & opp_knight;
    checks += bool(knight_attacks);

    Bitboard mask = knight_attacks;

    // check for pawn checks
    Bitboard pawn_attacks = attacks::pawn(board.sideToMove(), sq) & opp_pawns;
    mask |= pawn_attacks;
    checks += bool(pawn_attacks);

    // check for bishop checks
    Bitboard bishop_attacks = attacks::bishop(sq, board.occ()) & (opp_bishop | opp_queen);

    if (bishop_attacks) {
        const auto index = bishop_attacks.lsb();

        mask |= SQUARES_BETWEEN_BB[sq.index()][index] | Bitboard::fromSquare(index);
        checks++;
    }

    Bitboard rook_attacks = attacks::rook(sq, board.occ()) & (opp_rook | opp_queen);

    if (rook_attacks) {
        if (rook_attacks.count() > 1) {
            checks = 2;
            return {mask, checks};
        }

        const auto index = rook_attacks.lsb();

        mask |= SQUARES_BETWEEN_BB[sq.index()][index] | Bitboard::fromSquare(index);
        checks++;
    }

    if (!mask) {
        return {constants::DEFAULT_CHECKMASK, checks};
    }

    return {mask, checks};
}

template <Color::underlying c>
[[nodiscard]] inline Bitboard movegen::pinMaskRooks(const Board &board, Square sq, Bitboard occ_opp, Bitboard occ_us) {
    const auto opp_rook  = board.pieces(PieceType::ROOK, ~c);
    const auto opp_queen = board.pieces(PieceType::QUEEN, ~c);

    Bitboard rook_attacks = attacks::rook(sq, occ_opp) & (opp_rook | opp_queen);
    Bitboard pin_hv       = 0;

    while (rook_attacks) {
        const auto index = rook_attacks.pop();

        const Bitboard possible_pin = SQUARES_BETWEEN_BB[sq.index()][index] | Bitboard::fromSquare(index);
        if ((possible_pin & occ_us).count() == 1) pin_hv |= possible_pin;
    }

    return pin_hv;
}

template <Color::underlying c>
[[nodiscard]] inline Bitboard movegen::pinMaskBishops(const Board &board, Square sq, Bitboard occ_opp,
                                                      Bitboard occ_us) {
    const auto opp_bishop = board.pieces(PieceType::BISHOP, ~c);
    const auto opp_queen  = board.pieces(PieceType::QUEEN, ~c);

    Bitboard bishop_attacks = attacks::bishop(sq, occ_opp) & (opp_bishop | opp_queen);
    Bitboard pin_diag       = 0;

    while (bishop_attacks) {
        const auto index = bishop_attacks.pop();

        const Bitboard possible_pin = SQUARES_BETWEEN_BB[sq.index()][index] | Bitboard::fromSquare(index);
        if ((possible_pin & occ_us).count() == 1) pin_diag |= possible_pin;
    }

    return pin_diag;
}

template <Color::underlying c>
[[nodiscard]] inline Bitboard movegen::seenSquares(const Board &board, Bitboard enemy_empty) {
    auto king_sq          = board.kingSq(~c);
    Bitboard map_king_atk = attacks::king(king_sq) & enemy_empty;

    if (map_king_atk == Bitboard(0ull) && !board.chess960()) {
        return 0ull;
    }

    auto occ     = board.occ() & ~Bitboard::fromSquare(king_sq);
    auto queens  = board.pieces(PieceType::QUEEN, c);
    auto pawns   = board.pieces(PieceType::PAWN, c);
    auto knights = board.pieces(PieceType::KNIGHT, c);
    auto bishops = board.pieces(PieceType::BISHOP, c) | queens;
    auto rooks   = board.pieces(PieceType::ROOK, c) | queens;

    Bitboard seen = attacks::pawnLeftAttacks<c>(pawns) | attacks::pawnRightAttacks<c>(pawns);

    while (knights) {
        const auto index = knights.pop();
        seen |= attacks::knight(index);
    }

    while (bishops) {
        const auto index = bishops.pop();
        seen |= attacks::bishop(index, occ);
    }

    while (rooks) {
        const auto index = rooks.pop();
        seen |= attacks::rook(index, occ);
    }

    const Square index = board.kingSq(c);
    seen |= attacks::king(index);

    return seen;
}

template <Color::underlying c, movegen::MoveGenType mt>
inline void movegen::generatePawnMoves(const Board &board, Movelist &moves, Bitboard pin_d, Bitboard pin_hv,
                                       Bitboard checkmask, Bitboard occ_opp) {
    // flipped for black

    constexpr auto UP         = make_direction(Direction::NORTH, c);
    constexpr auto DOWN       = make_direction(Direction::SOUTH, c);
    constexpr auto DOWN_LEFT  = make_direction(Direction::SOUTH_WEST, c);
    constexpr auto DOWN_RIGHT = make_direction(Direction::SOUTH_EAST, c);
    constexpr auto UP_LEFT    = make_direction(Direction::NORTH_WEST, c);
    constexpr auto UP_RIGHT   = make_direction(Direction::NORTH_EAST, c);

    constexpr auto RANK_B_PROMO     = Rank::rank(Rank::RANK_7, c).bb();
    constexpr auto RANK_PROMO       = Rank::rank(Rank::RANK_8, c).bb();
    constexpr auto DOUBLE_PUSH_RANK = Rank::rank(Rank::RANK_3, c).bb();

    const auto pawns = board.pieces(PieceType::PAWN, c);

    // These pawns can maybe take Left or Right
    const Bitboard pawns_lr          = pawns & ~pin_hv;
    const Bitboard unpinned_pawns_lr = pawns_lr & ~pin_d;
    const Bitboard pinned_pawns_lr   = pawns_lr & pin_d;

    auto l_pawns = attacks::shift<UP_LEFT>(unpinned_pawns_lr) | (attacks::shift<UP_LEFT>(pinned_pawns_lr) & pin_d);
    auto r_pawns = attacks::shift<UP_RIGHT>(unpinned_pawns_lr) | (attacks::shift<UP_RIGHT>(pinned_pawns_lr) & pin_d);

    // Prune moves that don't capture a piece and are not on the checkmask.
    l_pawns &= occ_opp & checkmask;
    r_pawns &= occ_opp & checkmask;

    // These pawns can walk Forward
    const auto pawns_hv = pawns & ~pin_d;

    const auto pawns_pinned_hv   = pawns_hv & pin_hv;
    const auto pawns_unpinned_hv = pawns_hv & ~pin_hv;

    // Prune moves that are blocked by a piece
    const auto single_push_unpinned = attacks::shift<UP>(pawns_unpinned_hv) & ~board.occ();
    const auto single_push_pinned   = attacks::shift<UP>(pawns_pinned_hv) & pin_hv & ~board.occ();

    // Prune moves that are not on the checkmask.
    Bitboard single_push = (single_push_unpinned | single_push_pinned) & checkmask;

    Bitboard double_push = ((attacks::shift<UP>(single_push_unpinned & DOUBLE_PUSH_RANK) & ~board.occ()) |
                            (attacks::shift<UP>(single_push_pinned & DOUBLE_PUSH_RANK) & ~board.occ())) &
                           checkmask;

    if (pawns & RANK_B_PROMO) {
        Bitboard promo_left  = l_pawns & RANK_PROMO;
        Bitboard promo_right = r_pawns & RANK_PROMO;
        Bitboard promo_push  = single_push & RANK_PROMO;

        // Skip capturing promotions if we are only generating quiet moves.
        // Generates at ALL and CAPTURE
        while (mt != MoveGenType::QUIET && promo_left) {
            const auto index = promo_left.pop();
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_RIGHT, index, PieceType::QUEEN));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_RIGHT, index, PieceType::ROOK));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_RIGHT, index, PieceType::BISHOP));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_RIGHT, index, PieceType::KNIGHT));
        }

        // Skip capturing promotions if we are only generating quiet moves.
        // Generates at ALL and CAPTURE
        while (mt != MoveGenType::QUIET && promo_right) {
            const auto index = promo_right.pop();
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_LEFT, index, PieceType::QUEEN));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_LEFT, index, PieceType::ROOK));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_LEFT, index, PieceType::BISHOP));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN_LEFT, index, PieceType::KNIGHT));
        }

        // Skip quiet promotions if we are only generating captures.
        // Generates at ALL and QUIET
        while (mt != MoveGenType::CAPTURE && promo_push) {
            const auto index = promo_push.pop();
            moves.add(Move::make<Move::PROMOTION>(index + DOWN, index, PieceType::QUEEN));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN, index, PieceType::ROOK));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN, index, PieceType::BISHOP));
            moves.add(Move::make<Move::PROMOTION>(index + DOWN, index, PieceType::KNIGHT));
        }
    }

    single_push &= ~RANK_PROMO;
    l_pawns &= ~RANK_PROMO;
    r_pawns &= ~RANK_PROMO;

    while (mt != MoveGenType::QUIET && l_pawns) {
        const auto index = l_pawns.pop();
        moves.add(Move::make<Move::NORMAL>(index + DOWN_RIGHT, index));
    }

    while (mt != MoveGenType::QUIET && r_pawns) {
        const auto index = r_pawns.pop();
        moves.add(Move::make<Move::NORMAL>(index + DOWN_LEFT, index));
    }

    while (mt != MoveGenType::CAPTURE && single_push) {
        const auto index = single_push.pop();
        moves.add(Move::make<Move::NORMAL>(index + DOWN, index));
    }

    while (mt != MoveGenType::CAPTURE && double_push) {
        const auto index = double_push.pop();
        moves.add(Move::make<Move::NORMAL>(index + DOWN + DOWN, index));
    }

    if constexpr (mt == MoveGenType::QUIET) return;

    const Square ep = board.enpassantSq();

    if (ep != Square::NO_SQ) {
        auto m = generateEPMove(board, checkmask, pin_d, pawns_lr, ep, c);

        for (const auto &move : m) {
            if (move != Move::NO_MOVE) moves.add(move);
        }
    }
}

[[nodiscard]] inline std::array<Move, 2> movegen::generateEPMove(const Board &board, Bitboard checkmask, Bitboard pin_d,
                                                                 Bitboard pawns_lr, Square ep, Color c) {
    assert((ep.rank() == Rank::RANK_3 && board.sideToMove() == Color::BLACK) ||
           (ep.rank() == Rank::RANK_6 && board.sideToMove() == Color::WHITE));

    std::array<Move, 2> moves = {Move::NO_MOVE, Move::NO_MOVE};
    auto i                    = 0;

    const auto DOWN     = make_direction(Direction::SOUTH, c);
    const auto epPawnSq = ep + DOWN;

    /*
     In case the en passant square and the enemy pawn
     that just moved are not on the checkmask
     en passant is not available.
    */
    if ((checkmask & (Bitboard::fromSquare(epPawnSq) | Bitboard::fromSquare(ep))) == Bitboard(0)) return moves;

    const Square kSQ              = board.kingSq(c);
    const Bitboard kingMask       = Bitboard::fromSquare(kSQ) & epPawnSq.rank().bb();
    const Bitboard enemyQueenRook = board.pieces(PieceType::ROOK, ~c) | board.pieces(PieceType::QUEEN, ~c);

    auto epBB = attacks::pawn(~c, ep) & pawns_lr;

    // For one en passant square two pawns could potentially take there.
    while (epBB) {
        const auto from = epBB.pop();
        const auto to   = ep;

        /*
         If the pawn is pinned but the en passant square is not on the
         pin mask then the move is illegal.
        */
        if ((Bitboard::fromSquare(from) & pin_d) && !(pin_d & Bitboard::fromSquare(ep))) continue;

        const auto connectingPawns = Bitboard::fromSquare(epPawnSq) | Bitboard::fromSquare(from);

        /*
         7k/4p3/8/2KP3r/8/8/8/8 b - - 0 1
         If e7e5 there will be a potential ep square for us on e6.
         However, we cannot take en passant because that would put our king
         in check. For this scenario we check if there's an enemy rook/queen
         that would give check if the two pawns were removed.
         If that's the case then the move is illegal and we can break immediately.
        */
        const auto isPossiblePin = kingMask && enemyQueenRook;

        if (isPossiblePin && (attacks::rook(kSQ, board.occ() & ~connectingPawns) & enemyQueenRook) != Bitboard(0))
            break;

        moves[i++] = Move::make<Move::ENPASSANT>(from, to);
    }

    return moves;
}

[[nodiscard]] inline Bitboard movegen::generateKnightMoves(Square sq) { return attacks::knight(sq); }

[[nodiscard]] inline Bitboard movegen::generateBishopMoves(Square sq, Bitboard pin_d, Bitboard occ_all) {
    // The Bishop is pinned diagonally thus can only move diagonally.
    if (pin_d & Bitboard::fromSquare(sq)) return attacks::bishop(sq, occ_all) & pin_d;
    return attacks::bishop(sq, occ_all);
}

[[nodiscard]] inline Bitboard movegen::generateRookMoves(Square sq, Bitboard pin_hv, Bitboard occ_all) {
    // The Rook is pinned horizontally thus can only move horizontally.
    if (pin_hv & Bitboard::fromSquare(sq)) return attacks::rook(sq, occ_all) & pin_hv;
    return attacks::rook(sq, occ_all);
}

[[nodiscard]] inline Bitboard movegen::generateQueenMoves(Square sq, Bitboard pin_d, Bitboard pin_hv,
                                                          Bitboard occ_all) {
    Bitboard moves = 0ULL;

    if (pin_d & Bitboard::fromSquare(sq))
        moves |= attacks::bishop(sq, occ_all) & pin_d;
    else if (pin_hv & Bitboard::fromSquare(sq))
        moves |= attacks::rook(sq, occ_all) & pin_hv;
    else {
        moves |= attacks::rook(sq, occ_all);
        moves |= attacks::bishop(sq, occ_all);
    }

    return moves;
}

[[nodiscard]] inline Bitboard movegen::generateKingMoves(Square sq, Bitboard seen, Bitboard movable_square) {
    return attacks::king(sq) & movable_square & ~seen;
}

template <Color::underlying c, movegen::MoveGenType mt>
[[nodiscard]] inline Bitboard movegen::generateCastleMoves(const Board &board, Square sq, Bitboard seen,
                                                           Bitboard pin_hv) {
    if constexpr (mt == MoveGenType::CAPTURE) return 0ull;
    if (!Square::back_rank(sq, c) || !board.castlingRights().has(c)) return 0ull;

    const auto rights = board.castlingRights();

    Bitboard moves = 0ull;

    for (const auto side : {Board::CastlingRights::Side::KING_SIDE, Board::CastlingRights::Side::QUEEN_SIDE}) {
        if (!rights.has(c, side)) continue;

        const auto end_king_sq = Square::castling_king_square(side == Board::CastlingRights::Side::KING_SIDE, c);
        const auto end_rook_sq = Square::castling_rook_square(side == Board::CastlingRights::Side::KING_SIDE, c);

        const auto from_rook_sq = Square(rights.getRookFile(c, side), sq.rank());

        const Bitboard not_occ_path       = SQUARES_BETWEEN_BB[sq.index()][from_rook_sq.index()];
        const Bitboard not_attacked_path  = SQUARES_BETWEEN_BB[sq.index()][end_king_sq.index()];
        const Bitboard empty_not_attacked = ~seen & ~(board.occ() & Bitboard(~Bitboard::fromSquare(from_rook_sq)));
        const Bitboard withoutRook        = board.occ() & Bitboard(~Bitboard::fromSquare(from_rook_sq));
        const Bitboard withoutKing        = board.occ() & Bitboard(~Bitboard::fromSquare(sq));

        if ((not_attacked_path & empty_not_attacked) == not_attacked_path &&
            ((not_occ_path & ~board.occ()) == not_occ_path) &&
            !(Bitboard::fromSquare(from_rook_sq) & pin_hv.getBits() & sq.rank().bb()) &&
            !(Bitboard::fromSquare(end_rook_sq) & (withoutRook & withoutKing).getBits()) &&
            !(Bitboard::fromSquare(end_king_sq) &
              (seen | (withoutRook & Bitboard(~Bitboard::fromSquare(sq)))).getBits())) {
            moves |= Bitboard::fromSquare(from_rook_sq);
        }
    }

    return moves;
}

template <typename T>
inline void movegen::whileBitboardAdd(Movelist &movelist, Bitboard mask, T func) {
    while (mask) {
        const Square from = mask.pop();
        auto moves        = func(from);
        while (moves) {
            const Square to = moves.pop();
            movelist.add(Move::make<Move::NORMAL>(from, to));
        }
    }
}

template <Color::underlying c, movegen::MoveGenType mt>
inline void movegen::legalmoves(Movelist &movelist, const Board &board, int pieces) {
    /*
     The size of the movelist might not
     be 0! This is done on purpose since it enables
     you to append new move types to any movelist.
    */
    auto king_sq = board.kingSq(c);

    Bitboard occ_us  = board.us(c);
    Bitboard occ_opp = board.us(~c);
    Bitboard occ_all = occ_us | occ_opp;

    Bitboard opp_empty = ~occ_us;

    const auto [checkmask, checks] = checkMask<c>(board, king_sq);
    const auto pin_hv              = pinMaskRooks<c>(board, king_sq, occ_opp, occ_us);
    const auto pin_d               = pinMaskBishops<c>(board, king_sq, occ_opp, occ_us);

    assert(checks <= 2);

    // Moves have to be on the checkmask
    Bitboard movable_square;

    // Slider, Knights and King moves can only go to enemy or empty squares.
    if (mt == MoveGenType::ALL)
        movable_square = opp_empty;
    else if (mt == MoveGenType::CAPTURE)
        movable_square = occ_opp;
    else  // QUIET moves
        movable_square = ~occ_all;

    if (pieces & PieceGenType::KING) {
        Bitboard seen = seenSquares<~c>(board, opp_empty);

        whileBitboardAdd(movelist, Bitboard::fromSquare(king_sq),
                         [&](Square sq) { return generateKingMoves(sq, seen, movable_square); });

        if (checks == 0) {
            Bitboard moves_bb = generateCastleMoves<c, mt>(board, king_sq, seen, pin_hv);

            while (moves_bb) {
                Square to = moves_bb.pop();
                movelist.add(Move::make<Move::CASTLING>(king_sq, to));
            }
        }
    }

    movable_square &= checkmask;

    // Early return for double check as described earlier
    if (checks == 2) return;

    // Add the moves to the movelist.
    if (pieces & PieceGenType::PAWN) {
        generatePawnMoves<c, mt>(board, movelist, pin_d, pin_hv, checkmask, occ_opp);
    }

    if (pieces & PieceGenType::KNIGHT) {
        // Prune knights that are pinned since these cannot move.
        Bitboard knights_mask = board.pieces(PieceType::KNIGHT, c) & ~(pin_d | pin_hv);

        whileBitboardAdd(movelist, knights_mask, [&](Square sq) { return generateKnightMoves(sq) & movable_square; });
    }

    if (pieces & PieceGenType::BISHOP) {
        // Prune horizontally pinned bishops
        Bitboard bishops_mask = board.pieces(PieceType::BISHOP, c) & ~pin_hv;

        whileBitboardAdd(movelist, bishops_mask,
                         [&](Square sq) { return generateBishopMoves(sq, pin_d, occ_all) & movable_square; });
    }

    if (pieces & PieceGenType::ROOK) {
        //  Prune diagonally pinned rooks
        Bitboard rooks_mask = board.pieces(PieceType::ROOK, c) & ~pin_d;

        whileBitboardAdd(movelist, rooks_mask,
                         [&](Square sq) { return generateRookMoves(sq, pin_hv, occ_all) & movable_square; });
    }

    if (pieces & PieceGenType::QUEEN) {
        // Prune double pinned queens
        Bitboard queens_mask = board.pieces(PieceType::QUEEN, c) & ~(pin_d & pin_hv);

        whileBitboardAdd(movelist, queens_mask,
                         [&](Square sq) { return generateQueenMoves(sq, pin_d, pin_hv, occ_all) & movable_square; });
    }
}

template <movegen::MoveGenType mt>
inline void movegen::legalmoves(Movelist &movelist, const Board &board, int pieces) {
    movelist.clear();

    if (board.sideToMove() == Color::WHITE)
        legalmoves<Color::WHITE, mt>(movelist, board, pieces);
    else
        legalmoves<Color::BLACK, mt>(movelist, board, pieces);
}

template <Color::underlying c>
inline bool movegen::isEpSquareValid(const Board &board, Square ep) {
    const auto stm = board.sideToMove();

    Bitboard occ_us  = board.us(stm);
    Bitboard occ_opp = board.us(~stm);
    auto king_sq     = board.kingSq(stm);

    const auto [checkmask, checks] = movegen::checkMask<c>(board, king_sq);
    const auto pin_hv              = movegen::pinMaskRooks<c>(board, king_sq, occ_opp, occ_us);
    const auto pin_d               = movegen::pinMaskBishops<c>(board, king_sq, occ_opp, occ_us);

    const auto pawns    = board.pieces(PieceType::PAWN, stm);
    const auto pawns_lr = pawns & ~pin_hv;
    const auto m        = movegen::generateEPMove(board, checkmask, pin_d, pawns_lr, ep, stm);
    bool found          = false;

    for (const auto &move : m) {
        if (move != Move::NO_MOVE) {
            found = true;
            break;
        }
    }

    return found;
}

inline const std::array<std::array<Bitboard, 64>, 64> movegen::SQUARES_BETWEEN_BB = [] {
    attacks::initAttacks();
    return movegen::init_squares_between();
}();

}  // namespace chess

#include <istream>

namespace chess::pgn {

namespace detail {

/**
 * @brief Private class
 */
class StringBuffer {
   public:
    bool empty() const noexcept { return index_ == 0; }

    void clear() noexcept { index_ = 0; }

    std::string_view get() const noexcept { return std::string_view(buffer_.data(), index_); }

    bool add(char c) {
        if (index_ >= N) {
            return false;
        }

        buffer_[index_] = c;

        ++index_;

        return true;
    }

   private:
    // PGN String Tokens are limited to 255 characters
    static constexpr int N = 255;

    std::array<char, N> buffer_ = {};

    std::size_t index_ = 0;
};

/**
 * @brief Private class
 * @tparam BUFFER_SIZE
 */
template <std::size_t BUFFER_SIZE>
class StreamBuffer {
   private:
    static constexpr std::size_t N = BUFFER_SIZE;
    using BufferType               = std::array<char, N * N>;

   public:
    StreamBuffer(std::istream &stream) : stream_(stream) {}

    // Get the current character, skip carriage returns
    std::optional<char> some() {
        while (true) {
            if (buffer_index_ < bytes_read_) {
                const auto c = buffer_[buffer_index_];

                if (c == '\r') {
                    ++buffer_index_;
                    continue;
                }

                return c;
            }

            if (!fill()) {
                return std::nullopt;
            }
        }
    }

    // Assume that the current character is already the opening_delim
    bool skipUntil(char open_delim, char close_delim) {
        int stack = 0;

        while (true) {
            const auto ret = some();
            advance();

            if (!ret.has_value()) {
                return false;
            }

            if (*ret == open_delim) {
                ++stack;
            } else if (*ret == close_delim) {
                if (stack == 0) {
                    // Mismatched closing delimiter
                    return false;
                } else {
                    --stack;
                    if (stack == 0) {
                        // Matching closing delimiter found
                        return true;
                    }
                }
            }
        }

        // If we reach this point, there are unmatched opening delimiters
        return false;
    }

    bool fill() {
        buffer_index_ = 0;

        stream_.read(buffer_.data(), N * N);
        bytes_read_ = stream_.gcount();

        return bytes_read_ > 0;
    }

    void advance() {
        if (buffer_index_ >= bytes_read_) {
            fill();
        }

        ++buffer_index_;
    }

    char peek() {
        if (buffer_index_ + 1 >= bytes_read_) {
            return stream_.peek();
        }

        return buffer_[buffer_index_ + 1];
    }

    std::optional<char> current() {
        if (buffer_index_ >= bytes_read_) {
            return fill() ? std::optional<char>(buffer_[buffer_index_]) : std::nullopt;
        }

        return buffer_[buffer_index_];
    }

   private:
    std::istream &stream_;
    BufferType buffer_;
    std::streamsize bytes_read_   = 0;
    std::streamsize buffer_index_ = 0;
};

}  // namespace detail

/**
 * @brief Visitor interface for parsing PGN files
 */
class Visitor {
   public:
    virtual ~Visitor() {};

    /**
     * @brief When true, the current PGN will be skipped and only
     * endPgn will be called, this will also reset the skip flag to false.
     * Has to be called after startPgn.
     * @param skip
     */
    void skipPgn(bool skip) { skip_ = skip; }
    bool skip() { return skip_; }

    /**
     * @brief Called when a new PGN starts
     */
    virtual void startPgn() = 0;

    /**
     * @brief Called for each header
     * @param key
     * @param value
     */
    virtual void header(std::string_view key, std::string_view value) = 0;

    /**
     * @brief Called before the first move of a game
     */
    virtual void startMoves() = 0;

    /**
     * @brief Called for each move of a game
     * @param move
     * @param comment
     */
    virtual void move(std::string_view move, std::string_view comment) = 0;

    /**
     * @brief Called when a game ends
     */
    virtual void endPgn() = 0;

   private:
    bool skip_ = false;
};

class StreamParserError {
   public:
    enum Code {
        None,
        ExceededMaxStringLength,
        InvalidHeaderMissingClosingBracket,
        InvalidHeaderMissingClosingQuote,
        NotEnoughData
    };

    StreamParserError() : code_(None) {}

    StreamParserError(Code code) : code_(code) {}

    Code code() const { return code_; }

    bool hasError() const { return code_ != None; }

    std::string message() const {
        switch (code_) {
            case None:
                return "No error";
            case InvalidHeaderMissingClosingBracket:
                return "Invalid header: missing closing bracket";
            case InvalidHeaderMissingClosingQuote:
                return "Invalid header: missing closing quote";
            case NotEnoughData:
                return "Not enough data";
            default:
                assert(false);
                return "Unknown error";
        }
    }

    bool operator==(Code code) const { return code_ == code; }
    bool operator!=(Code code) const { return code_ != code; }
    bool operator==(const StreamParserError &other) const { return code_ == other.code_; }
    bool operator!=(const StreamParserError &other) const { return code_ != other.code_; }

    operator bool() const { return code_ != None; }

   private:
    Code code_;
};

template <std::size_t BUFFER_SIZE =
#if defined(__APPLE__) || defined(__MACH__)
              256
#elif defined(__unix__) || defined(__unix) || defined(unix)
              1024
#else
              256
#endif
          >
class StreamParser {
   public:
    StreamParser(std::istream &stream) : stream_buffer(stream) {}

    StreamParserError readGames(Visitor &vis) {
        visitor = &vis;

        if (!stream_buffer.fill()) {
            return StreamParserError::NotEnoughData;
        }

        while (auto c = stream_buffer.some()) {
            if (in_header) {
                visitor->skipPgn(false);

                if (*c == '[') {
                    visitor->startPgn();
                    pgn_end = false;

                    processHeader();

                    if (error != StreamParserError::None) {
                        return error;
                    }
                }

            } else if (in_body) {
                processBody();

                if (error != StreamParserError::None) {
                    return error;
                }
            }

            if (!dont_advance_after_body) stream_buffer.advance();
            dont_advance_after_body = false;
        }

        if (!pgn_end) {
            onEnd();
        }

        return error;
    }

   private:
    void reset_trackers() {
        header.first.clear();
        header.second.clear();

        move.clear();
        comment.clear();

        in_header = true;
        in_body   = false;
    }

    void callVisitorMoveFunction() {
        if (!move.empty()) {
            if (!visitor->skip()) visitor->move(move.get(), comment);

            move.clear();
            comment.clear();
        }
    }

    void processHeader() {
        bool backslash = false;

        while (auto c = stream_buffer.some()) {
            switch (*c) {
                // tag start
                case '[':
                    stream_buffer.advance();

                    while (auto k = stream_buffer.some()) {
                        if (is_space(*k)) {
                            break;
                        } else {
                            if (!header.first.add(*k)) {
                                error = StreamParserError::ExceededMaxStringLength;
                                return;
                            }

                            stream_buffer.advance();
                        }
                    }

                    stream_buffer.advance();
                    break;
                case '"':
                    stream_buffer.advance();

                    while (auto k = stream_buffer.some()) {
                        if (*k == '\\') {
                            backslash = true;
                            // don't add backslash to header, is this really correct?
                            stream_buffer.advance();
                        } else if (*k == '"' && !backslash) {
                            stream_buffer.advance();

                            // we should be now at ]
                            if (stream_buffer.current().value_or('\0') != ']') {
                                error = StreamParserError::InvalidHeaderMissingClosingBracket;
                                return;
                            }

                            stream_buffer.advance();

                            break;
                        } else if (*k == '\n') {
                            // we missed the closing quote and read until the newline character
                            // this is an invalid pgn, let's throw an error
                            error = StreamParserError::InvalidHeaderMissingClosingQuote;
                            return;
                        } else {
                            backslash = false;

                            if (!header.second.add(*k)) {
                                error = StreamParserError::ExceededMaxStringLength;
                                return;
                            }

                            stream_buffer.advance();
                        }
                    }

                    // manually skip carriage return, otherwise we would be in the body
                    // ideally we should completely skip all carriage returns and newlines to avoid this
                    if (stream_buffer.current() == '\r') {
                        stream_buffer.advance();
                    }

                    if (!visitor->skip()) visitor->header(header.first.get(), header.second.get());

                    header.first.clear();
                    header.second.clear();

                    stream_buffer.advance();
                    break;
                case '\n':
                    in_header = false;
                    in_body   = true;

                    if (!visitor->skip()) visitor->startMoves();

                    return;
                default:
                    // this should normally not happen
                    // lets just go into the body, will this always be save?
                    in_header = false;
                    in_body   = true;

                    if (!visitor->skip()) visitor->startMoves();

                    return;
            }
        }
    }

    void processBody() {
        auto is_termination_symbol = false;
        auto has_comment           = false;

    start:
        /*
        Skip first move number or game termination
        Also skip - * / to fix games
        which directly start with a game termination
        this https://github.com/Disservin/chess-library/issues/68
        */

        while (auto c = stream_buffer.some()) {
            if (*c == ' ' || is_digit(*c)) {
                stream_buffer.advance();
            } else if (*c == '-' || *c == '*' || c == '/') {
                is_termination_symbol = true;
                stream_buffer.advance();
            } else if (*c == '{') {
                has_comment = true;

                // reading comment
                stream_buffer.advance();

                while (auto k = stream_buffer.some()) {
                    stream_buffer.advance();

                    if (*k == '}') {
                        break;
                    }

                    comment += *k;
                }

                // the game has no moves, but a comment followed by a game termination
                if (!visitor->skip()) {
                    visitor->move("", comment);

                    comment.clear();
                }
            } else {
                break;
            }
        }

        // we need to reparse the termination symbol
        if (has_comment && !is_termination_symbol) {
            goto start;
        }

        // game had no moves, so we can skip it and call endPgn
        if (is_termination_symbol) {
            onEnd();
            return;
        }

        while (auto c = stream_buffer.some()) {
            if (is_space(*c)) {
                stream_buffer.advance();
                continue;
            }

            break;
        }

        while (auto cd = stream_buffer.some()) {
            // Pgn are build up in the following way.
            // {move_number} {move} {comment} {move} {comment} {move_number} ...
            // So we need to skip the move_number then start reading the move, then save the comment
            // then read the second move in the group. After that a move_number will follow again.

            // [ is unexpected here, it probably is a new pgn and the current one is finished
            if (*cd == '[') {
                onEnd();
                dont_advance_after_body = true;
                // break;
                break;
            }

            // skip move number digits
            while (auto c = stream_buffer.some()) {
                if (is_space(*c) || is_digit(*c)) {
                    stream_buffer.advance();
                } else {
                    break;
                }
            }

            // skip dots
            while (auto c = stream_buffer.some()) {
                if (*c == '.') {
                    stream_buffer.advance();
                } else {
                    break;
                }
            }

            // skip spaces
            while (auto c = stream_buffer.some()) {
                if (is_space(*c)) {
                    stream_buffer.advance();
                } else {
                    break;
                }
            }

            // parse move
            if (parseMove()) {
                break;
            }

            // skip spaces
            while (auto c = stream_buffer.some()) {
                if (is_space(*c)) {
                    stream_buffer.advance();
                } else {
                    break;
                }
            }

            // game termination
            auto curr = stream_buffer.current();

            if (!curr.has_value()) {
                onEnd();
                break;
            }

            // game termination
            if (*curr == '*') {
                onEnd();
                stream_buffer.advance();

                break;
            }

            const auto peek = stream_buffer.peek();

            if (*curr == '1') {
                if (peek == '-') {
                    stream_buffer.advance();
                    stream_buffer.advance();

                    onEnd();
                    break;
                } else if (peek == '/') {
                    for (size_t i = 0; i <= 6; ++i) {
                        stream_buffer.advance();
                    }

                    onEnd();
                    break;
                }
            }

            // might be 0-1 (game termination) or 0-0-0/0-0 (castling)
            if (*curr == '0' && stream_buffer.peek() == '-') {
                stream_buffer.advance();
                stream_buffer.advance();

                const auto c = stream_buffer.current();
                if (!c.has_value()) {
                    onEnd();

                    break;
                }

                // game termination
                if (*c == '1') {
                    onEnd();
                    stream_buffer.advance();

                    break;
                }
                // castling
                else {
                    if (!move.add('0') || !move.add('-')) {
                        error = StreamParserError::ExceededMaxStringLength;
                        return;
                    }

                    if (parseMove()) {
                        stream_buffer.advance();
                        break;
                    }
                }
            }
        }
    }

    bool parseMove() {
        // reading move
        while (auto c = stream_buffer.some()) {
            if (is_space(*c)) {
                break;
            }

            if (!move.add(*c)) {
                error = StreamParserError::ExceededMaxStringLength;
                return true;
            }

            stream_buffer.advance();
        }

        return parseMoveAppendix();
    }

    bool parseMoveAppendix() {
        while (true) {
            auto curr = stream_buffer.current();

            if (!curr.has_value()) {
                onEnd();
                return true;
            }

            switch (*curr) {
                case '{': {
                    // reading comment
                    stream_buffer.advance();

                    while (auto c = stream_buffer.some()) {
                        stream_buffer.advance();

                        if (*c == '}') {
                            break;
                        }

                        comment += *c;
                    }

                    break;
                }
                case '(': {
                    stream_buffer.skipUntil('(', ')');
                    break;
                }
                case '$': {
                    while (auto c = stream_buffer.some()) {
                        if (is_space(*c)) {
                            break;
                        }

                        stream_buffer.advance();
                    }

                    break;
                }
                case ' ': {
                    while (auto c = stream_buffer.some()) {
                        if (!is_space(*c)) {
                            break;
                        }

                        stream_buffer.advance();
                    }

                    break;
                }
                default:
                    callVisitorMoveFunction();
                    return false;
            }
        }
    }

    void onEnd() {
        callVisitorMoveFunction();
        visitor->endPgn();
        visitor->skipPgn(false);

        reset_trackers();

        pgn_end = true;
    }

    bool is_space(const char c) noexcept {
        switch (c) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                return true;
            default:
                return false;
        }
    }

    bool is_digit(const char c) noexcept {
        switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return true;
            default:
                return false;
        }
    }

    detail::StreamBuffer<BUFFER_SIZE> stream_buffer;

    Visitor *visitor = nullptr;

    // one time allocations
    std::pair<detail::StringBuffer, detail::StringBuffer> header = {detail::StringBuffer{}, detail::StringBuffer{}};

    detail::StringBuffer move = {};
    std::string comment       = {};

    // State

    StreamParserError error = StreamParserError::None;

    bool in_header = true;
    bool in_body   = false;

    bool pgn_end = true;

    bool dont_advance_after_body = false;
};
}  // namespace chess::pgn

#include <sstream>


namespace chess {
class uci {
   public:
    /**
     * @brief Converts an internal move to a UCI string
     * @param move
     * @param chess960
     * @return
     */
    [[nodiscard]] static std::string moveToUci(const Move &move, bool chess960 = false) noexcept(false) {
        // Get the from and to squares
        Square from_sq = move.from();
        Square to_sq   = move.to();

        // If the move is not a chess960 castling move and is a king moving more than one square,
        // update the to square to be the correct square for a regular castling move
        if (!chess960 && move.typeOf() == Move::CASTLING) {
            to_sq = Square(to_sq > from_sq ? File::FILE_G : File::FILE_C, from_sq.rank());
        }

        std::stringstream ss;

        // Add the from and to squares to the string stream
        ss << from_sq;
        ss << to_sq;

        // If the move is a promotion, add the promoted piece to the string stream
        if (move.typeOf() == Move::PROMOTION) {
            ss << static_cast<std::string>(move.promotionType());
        }

        return ss.str();
    }

    /**
     * @brief Converts a UCI string to an internal move.
     * @param board
     * @param uci
     * @return
     */
    [[nodiscard]] static Move uciToMove(const Board &board, const std::string &uci) noexcept(false) {
        if (uci.length() < 4) {
            return Move::NO_MOVE;
        }

        Square source = Square(uci.substr(0, 2));
        Square target = Square(uci.substr(2, 2));

        if (!source.is_valid() || !target.is_valid()) {
            return Move::NO_MOVE;
        }

        auto pt = board.at(source).type();

        // castling in chess960
        if (board.chess960() && pt == PieceType::KING && board.at(target).type() == PieceType::ROOK &&
            board.at(target).color() == board.sideToMove()) {
            return Move::make<Move::CASTLING>(source, target);
        }

        // convert to king captures rook
        // in chess960 the move should be sent as king captures rook already!
        if (!board.chess960() && pt == PieceType::KING && Square::distance(target, source) == 2) {
            target = Square(target > source ? File::FILE_H : File::FILE_A, source.rank());
            return Move::make<Move::CASTLING>(source, target);
        }

        // en passant
        if (pt == PieceType::PAWN && target == board.enpassantSq()) {
            return Move::make<Move::ENPASSANT>(source, target);
        }

        // promotion
        if (pt == PieceType::PAWN && uci.length() == 5 && Square::back_rank(target, ~board.sideToMove())) {
            auto promotion = PieceType(uci.substr(4, 1));

            if (promotion == PieceType::NONE || promotion == PieceType::KING || promotion == PieceType::PAWN) {
                return Move::NO_MOVE;
            }

            return Move::make<Move::PROMOTION>(source, target, PieceType(uci.substr(4, 1)));
        }

        switch (uci.length()) {
            case 4:
                return Move::make<Move::NORMAL>(source, target);
            default:
                return Move::NO_MOVE;
        }
    }

    /**
     * @brief Converts a move to a SAN string
     * @param board
     * @param move
     * @return
     */
    [[nodiscard]] static std::string moveToSan(const Board &board, const Move &move) noexcept(false) {
        std::string san;
        moveToRep<false>(board, move, san);
        return san;
    }

    /**
     * @brief Converts a move to a LAN string
     * @param board
     * @param move
     * @return
     */
    [[nodiscard]] static std::string moveToLan(const Board &board, const Move &move) noexcept(false) {
        std::string lan;
        moveToRep<true>(board, move, lan);
        return lan;
    }

    class SanParseError : public std::exception {
       public:
        explicit SanParseError(const char *message) : msg_(message) {}

        explicit SanParseError(const std::string &message) : msg_(message) {}

        virtual ~SanParseError() noexcept {}

        virtual const char *what() const noexcept { return msg_.c_str(); }

       protected:
        std::string msg_;
    };

    class AmbiguousMoveError : public std::exception {
       public:
        explicit AmbiguousMoveError(const char *message) : msg_(message) {}

        explicit AmbiguousMoveError(const std::string &message) : msg_(message) {}

        virtual ~AmbiguousMoveError() noexcept {}

        virtual const char *what() const noexcept { return msg_.c_str(); }

       protected:
        std::string msg_;
    };

    /**
     * @brief Parse a san string and return the move.
     * This function will throw a SanParseError if the san string is invalid.
     * @param board
     * @param san
     * @return
     */
    [[nodiscard]] static Move parseSan(const Board &board, std::string_view san) noexcept(false) {
        Movelist moves;

        return parseSan(board, san, moves);
    }

    /**
     * @brief Parse a san string and return the move.
     * This function will throw a SanParseError if the san string is invalid.
     * @param board
     * @param san
     * @param moves
     * @return
     */
    [[nodiscard]] static Move parseSan(const Board &board, std::string_view san, Movelist &moves) noexcept(false) {
        if (san.empty()) {
            return Move::NO_MOVE;
        }

        static constexpr auto pt_to_pgt = [](PieceType pt) { return 1 << (pt); };
        const SanMoveInformation info   = parseSanInfo(san);

        if (info.capture) {
            movegen::legalmoves<movegen::MoveGenType::CAPTURE>(moves, board, pt_to_pgt(info.piece));
        } else {
            movegen::legalmoves<movegen::MoveGenType::QUIET>(moves, board, pt_to_pgt(info.piece));
        }

        if (info.castling_short || info.castling_long) {
            for (const auto &move : moves) {
                if (move.typeOf() == Move::CASTLING) {
                    if ((info.castling_short && move.to() > move.from()) ||
                        (info.castling_long && move.to() < move.from())) {
                        return move;
                    }
                }
            }

#ifndef CHESS_NO_EXCEPTIONS
            throw SanParseError("Failed to parse san. At step 2: " + std::string(san) + " " + board.getFen());
#endif
        }

        Move matchingMove = Move::NO_MOVE;
        bool foundMatch   = false;

        for (const auto &move : moves) {
            // Skip all moves that are not to the correct square
            // or are castling moves
            if (move.to() != info.to || move.typeOf() == Move::CASTLING) {
                continue;
            }

            // Handle promotion moves
            if (info.promotion != PieceType::NONE) {
                if (move.typeOf() != Move::PROMOTION || info.promotion != move.promotionType() ||
                    move.from().file() != info.from_file) {
                    continue;
                }
            }
            // Handle en passant moves
            else if (move.typeOf() == Move::ENPASSANT) {
                if (move.from().file() != info.from_file) {
                    continue;
                }
            }
            // Handle moves with specific from square
            else if (info.from != Square::NO_SQ) {
                if (move.from() != info.from) {
                    continue;
                }
            }
            // Handle moves with partial from information (rank or file)
            else if (info.from_rank != Rank::NO_RANK || info.from_file != File::NO_FILE) {
                if ((info.from_file != File::NO_FILE && move.from().file() != info.from_file) ||
                    (info.from_rank != Rank::NO_RANK && move.from().rank() != info.from_rank)) {
                    continue;
                }
            }

            // If we get here, the move matches our criteria
            if (foundMatch) {
#ifndef CHESS_NO_EXCEPTIONS
                throw AmbiguousMoveError("Ambiguous san: " + std::string(san) + " in " + board.getFen());
#endif
            }

            matchingMove = move;
            foundMatch   = true;
        }

        if (!foundMatch) {
#ifndef CHESS_NO_EXCEPTIONS
            throw SanParseError("Failed to parse san. At step 3: " + std::string(san) + " " + board.getFen());
#endif
        }

        return matchingMove;
    }

    /**
     * @brief Check if a string is a valid UCI move. Must also have the correct length.
     * @param move
     * @return
     */
    static bool isUciMove(const std::string &move) noexcept {
        bool is_uci = false;

        static constexpr auto is_digit     = [](char c) { return c >= '1' && c <= '8'; };
        static constexpr auto is_file      = [](char c) { return c >= 'a' && c <= 'h'; };
        static constexpr auto is_promotion = [](char c) { return c == 'n' || c == 'b' || c == 'r' || c == 'q'; };

        // assert that the move is in uci format, [abcdefgh][1-8][abcdefgh][1-8][nbrq]
        if (move.size() >= 4) {
            is_uci = is_file(move[0]) && is_digit(move[1]) && is_file(move[2]) && is_digit(move[3]);
        }

        if (move.size() == 5) {
            is_uci = is_uci && is_promotion(move[4]);
        }

        if (move.size() > 5) {
            return false;
        }

        return is_uci;
    }

   private:
    struct SanMoveInformation {
        File from_file = File::NO_FILE;
        Rank from_rank = Rank::NO_RANK;

        PieceType promotion = PieceType::NONE;

        Square from = Square::NO_SQ;
        // a valid move always has a to square
        Square to = Square::NO_SQ;

        // a valid move always has a piece
        PieceType piece = PieceType::NONE;

        bool castling_short = false;
        bool castling_long  = false;

        bool capture = false;
    };

    [[nodiscard]] static SanMoveInformation parseSanInfo(std::string_view san) noexcept(false) {
#ifndef CHESS_NO_EXCEPTIONS
        if (san.length() < 2) {
            throw SanParseError("Failed to parse san. At step 0: " + std::string(san));
        }
#endif
        constexpr auto parse_castle = [](std::string_view &san, SanMoveInformation &info, char castling_char) {
            info.piece = PieceType::KING;

            san.remove_prefix(3);

            info.castling_short = san.length() == 0 || (san.length() >= 1 && san[0] != '-');
            info.castling_long  = san.length() >= 2 && san[0] == '-' && san[1] == castling_char;

            assert((info.castling_short && !info.castling_long) || (!info.castling_short && info.castling_long) ||
                   (!info.castling_short && !info.castling_long));
        };

        static constexpr auto isRank = [](char c) { return c >= '1' && c <= '8'; };
        static constexpr auto isFile = [](char c) { return c >= 'a' && c <= 'h'; };
        static constexpr auto sw     = [](const char &c) { return std::string_view(&c, 1); };

        SanMoveInformation info;

        // set to 1 to skip piece type offset
        std::size_t index = 1;

        if (san[0] == 'O' || san[0] == '0') {
            parse_castle(san, info, san[0]);
            return info;
        } else if (isFile(san[0])) {
            index--;
            info.piece = PieceType::PAWN;
        } else {
            info.piece = PieceType(san);
        }

        File file_to = File::NO_FILE;
        Rank rank_to = Rank::NO_RANK;

        // check if san starts with a file, if so it will be start file
        if (index < san.size() && isFile(san[index])) {
            info.from_file = File(sw(san[index]));
            index++;
        }

        // check if san starts with a rank, if so it will be start rank
        if (index < san.size() && isRank(san[index])) {
            info.from_rank = Rank(sw(san[index]));
            index++;
        }

        // skip capture sign
        if (index < san.size() && san[index] == 'x') {
            info.capture = true;
            index++;
        }

        // to file
        if (index < san.size() && isFile(san[index])) {
            file_to = File(sw(san[index]));
            index++;
        }

        // to rank
        if (index < san.size() && isRank(san[index])) {
            rank_to = Rank(sw(san[index]));
            index++;
        }

        // promotion
        if (index < san.size() && san[index] == '=') {
            index++;
            info.promotion = PieceType(sw(san[index]));

#ifndef CHESS_NO_EXCEPTIONS
            if (info.promotion == PieceType::KING || info.promotion == PieceType::PAWN ||
                info.promotion == PieceType::NONE)
                throw SanParseError("Failed to parse promotion, during san conversion." + std::string(san));
#endif

            index++;
        }

        // for simple moves like Nf3, e4, etc. all the information is contained
        // in the from file and rank. Thus we need to move it to the to file and rank.
        if (file_to == File::NO_FILE && rank_to == Rank::NO_RANK) {
            file_to = info.from_file;
            rank_to = info.from_rank;

            info.from_file = File::NO_FILE;
            info.from_rank = Rank::NO_RANK;
        }

        // pawns which are not capturing stay on the same file
        if (info.piece == PieceType::PAWN && info.from_file == File::NO_FILE && !info.capture) {
            info.from_file = file_to;
        }

        info.to = Square(file_to, rank_to);

        if (info.from_file != File::NO_FILE && info.from_rank != Rank::NO_RANK) {
            info.from = Square(info.from_file, info.from_rank);
        }

        return info;
    }

    template <bool LAN = false>
    static void moveToRep(Board board, const Move &move, std::string &str) {
        if (handleCastling(move, str)) {
            board.makeMove(move);
            if (board.inCheck()) appendCheckSymbol(board, str);
            return;
        }

        const PieceType pt   = board.at(move.from()).type();
        const bool isCapture = board.at(move.to()) != Piece::NONE || move.typeOf() == Move::ENPASSANT;

        assert(pt != PieceType::NONE);

        if (pt != PieceType::PAWN) {
            appendPieceSymbol(pt, str);
        }

        if constexpr (LAN) {
            appendSquare(move.from(), str);
        } else {
            if (pt == PieceType::PAWN) {
                str += isCapture ? static_cast<std::string>(move.from().file()) : "";
            } else {
                resolveAmbiguity(board, move, pt, str);
            }
        }

        if (isCapture) {
            str += 'x';
        }

        appendSquare(move.to(), str);

        if (move.typeOf() == Move::PROMOTION) appendPromotion(move, str);

        board.makeMove(move);

        if (board.inCheck()) appendCheckSymbol(board, str);
    }

    static bool handleCastling(const Move &move, std::string &str) {
        if (move.typeOf() != Move::CASTLING) return false;

        str = (move.to().file() > move.from().file()) ? "O-O" : "O-O-O";
        return true;
    }

    static void appendPieceSymbol(PieceType pieceType, std::string &str) {
        str += std::toupper(static_cast<std::string>(pieceType)[0]);
    }

    static void appendSquare(Square square, std::string &str) {
        str += static_cast<std::string>(square.file());
        str += static_cast<std::string>(square.rank());
    }

    static void appendPromotion(const Move &move, std::string &str) {
        str += '=';
        str += std::toupper(static_cast<std::string>(move.promotionType())[0]);
    }

    static void appendCheckSymbol(Board &board, std::string &str) {
        const auto gameState = board.isGameOver().second;
        str += (gameState == GameResult::LOSE) ? '#' : '+';
    }

    static void resolveAmbiguity(const Board &board, const Move &move, PieceType pieceType, std::string &str) {
        Movelist moves;
        movegen::legalmoves(moves, board, 1 << pieceType);

        bool needFile         = false;
        bool needRank         = false;
        bool hasAmbiguousMove = false;

        for (const auto &m : moves) {
            if (m != move && m.to() == move.to()) {
                hasAmbiguousMove = true;

                /*
                First, if the moving pieces can be distinguished by their originating files, the originating
                file letter of the moving piece is inserted immediately after the moving piece letter.

                Second (when the first step fails), if the moving pieces can be distinguished by their
                originating ranks, the originating rank digit of the moving piece is inserted immediately after
                the moving piece letter.

                Third (when both the first and the second steps fail), the two character square coordinate of
                the originating square of the moving piece is inserted immediately after the moving piece
                letter.
                */

                if (isIdentifiableByType(moves, move, move.from().file())) {
                    needFile = true;
                    break;
                }

                if (isIdentifiableByType(moves, move, move.from().rank())) {
                    needRank = true;
                    break;
                }
            }
        }

        if (needFile) str += static_cast<std::string>(move.from().file());
        if (needRank) str += static_cast<std::string>(move.from().rank());

        // we weren't able to disambiguate the move by either file or rank, so we need to use both
        if (hasAmbiguousMove && !needFile && !needRank) {
            appendSquare(move.from(), str);
        }
    }

    template <typename CoordinateType>
    static bool isIdentifiableByType(const Movelist &moves, const Move move, CoordinateType type) {
        static_assert(std::is_same_v<CoordinateType, File> || std::is_same_v<CoordinateType, Rank>,
                      "CoordinateType must be either File or Rank");

        for (const auto &m : moves) {
            if (m == move || m.to() != move.to()) {
                continue;
            }

            // file
            if constexpr (std::is_same_v<CoordinateType, File>) {
                if (type == m.from().file()) return false;
            }
            // rank
            else {
                if (type == m.from().rank()) return false;
            }
        }

        return true;
    }
};
}  // namespace chess

#endif
