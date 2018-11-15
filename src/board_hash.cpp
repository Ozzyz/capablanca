
/*  This is the class that performs board hashing.
    It uses Zobrist hashing, which basically consists of the following steps:
        1) Generate a 8x8x12 array that is initialized with a 64-bit randomly
   generated bitstring for each entry 2) Generate a hash of the 8x8 board by
   looping over the entire board, then XORing each entry with the table[i][j]
   where i is the current square and j the picece occupying that square.

*/

#include "board_hash.hpp"
#include <chrono>
#include <cmath>
#include <random>

std::uint64_t Zobrist::random_bitstring() {
    std::mt19937_64 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    return rng();
}

Zobrist::Zobrist() {
    // Initialize the hash board
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 12; j++) {
            hash_board[i][j] = random_bitstring();
        }
    }
}

std::uint64_t Zobrist::hash(Board &board) {
    std::uint64_t hash = 0;
    for (int i = 0; i < 64; i++) {
        Piece piece = board.board[i];
        if (piece != Empty) {
            hash = hash ^ hash_board[i][piece];
        }
    }
    return hash;
}
