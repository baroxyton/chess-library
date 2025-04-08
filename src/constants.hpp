#pragma once

#include "bitboard.hpp"

#ifndef CHESS_SAFE_ASSERT
#    define CHESS_SAFE_ASSERT(x) \
        if (!(x)) throw std::runtime_error("assert failed: " #x)
#endif

namespace chess::constants {

constexpr Bitboard DEFAULT_CHECKMASK = Bitboard(0xFFFFFFFFFFFFFFFFull);
constexpr auto STARTPOS              = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
constexpr auto MAX_MOVES             = 256;
}  // namespace chess::constants
