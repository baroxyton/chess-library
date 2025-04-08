#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>

#include "include/chess.hpp"

using chess::Board;
using chess::Move;
using chess::Movelist;

using chess::movegen;
using chess::uci;

using U128 = __uint128_t;

// Custom hash function for std::unordered_map with std::string keys
using FenToHashMap = std::unordered_map<std::string, U128>;

std::string u128ToHex(U128 val) {
    std::ostringstream oss;
    oss << "0x" << std::hex;
    oss << static_cast<uint64_t>(val >> 64);
    oss << std::setw(16) << std::setfill('0') << static_cast<uint64_t>(val);
    return oss.str();
}

Move getRandomMove(const Movelist& moves, std::mt19937& rng) {
    std::uniform_int_distribution<size_t> dist(0, moves.size() - 1);
    return moves[dist(rng)];
}

int main() {
    constexpr int GAMES     = 1000;
    constexpr int MAX_PLIES = 200;

    std::mt19937 rng(1337);  // Seeded RNG for determinism
    FenToHashMap fenToHash;

    int collisions = 0;

    for (int g = 0; g < GAMES; ++g) {
        Board board;

        for (int ply = 0; ply < MAX_PLIES; ++ply) {
            Movelist moves;
            movegen::legalmoves(moves, board);

            if (moves.empty()) break;

            Move move = getRandomMove(moves, rng);
            board.makeMove(move);

            std::string fen = board.getFen(false);
            U128 hash       = board.hash();

            auto it = fenToHash.find(fen);
            if (it != fenToHash.end()) {
                if (it->second != hash) {
                    std::cerr << "[ERROR] Hash mismatch for same FEN!\n";
                    std::cerr << "FEN: " << fen << "\n";
                    std::cerr << "Expected: " << u128ToHex(it->second) << "\n";
                    std::cerr << "Found:    " << u128ToHex(hash) << "\n";
                    std::exit(1);
                }
            } else {
                fenToHash[fen] = hash;
            }
        }
    }

    std::cout << "✔ FEN → Zobrist test passed with " << fenToHash.size() << " unique positions.\n";
    struct U128Hash {
        size_t operator()(const U128& x) const { return static_cast<size_t>(x ^ (x >> 64)); }
    };

    // Check for hash collisions on different FENs
    std::unordered_map<U128, std::string, U128Hash> hashToFen;
    for (const auto& [fen, hash] : fenToHash) {
        auto it = hashToFen.find(hash);
        if (it != hashToFen.end() && it->second != fen) {
            std::cerr << "[COLLISION] Hash collision between:\n";
            std::cerr << "  FEN1: " << it->second << "\n";
            std::cerr << "  FEN2: " << fen << "\n";
            ++collisions;
        } else {
            hashToFen[hash] = fen;
        }
    }

    std::cout << "→ Collisions found: " << collisions << "\n";

    // Print a few dozen zobrist hashes
    std::cout << "\n=== Sample Zobrist hashes ===\n";
    int printed = 0;
    for (const auto& [fen, hash] : fenToHash) {
        std::cout << u128ToHex(hash) << "\n";
        if (++printed >= 30) break;
    }

    return 0;
}
