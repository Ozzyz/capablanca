#include "evaluation.hpp"
#include "../board/board.hpp"
/*
This file evaluates the current chess position by using
piece-square tables and material count.
In order to save arrays, a mirror array is used to index the piece tables for
black All 'points' are measured in centipawns.
*/

using namespace std;
// Knights are better in the center, and especially offensive center squares

/* clang-format off */
int knightSquareEval[64] = {
	 0, -10,    0,  0,  0,  0, -10,  0,
	 0,   0,    0,  0,  0,  0,   0,  0,
	10,   0,   20,  0,  0, 20,   0, 10,
	0,    0,   20, 20, 20, 20,   0,  0,
	0,    0,   20, 20, 20, 20,   0,  0,
	0,    0,   30, 30, 30, 30,  30,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
};

// Reward center pawns and pawns near promotion
// We dont have to account for promoted pawns, since that will be reflected in our
// material evaluation
int pawnSquareEval[64]{
	 0,    0,     0,  0,  0,  0,   0,  0,
	10,   10,    10,  0,  0, 10,  10, 10,
	10,    5,    10,  5,  5,  5,   5, 10,
	 0,    0,    20, 20, 20, 20,   0,  0,
	 0,    0,    20, 20, 20, 20,   0,  0,
	10,   10,    15, 15, 15, 15,  10, 10,
	20,   20,    25, 25, 25, 25,  20, 20,
	 0,    0,    0,  0,  0,   0,   0,  0,
};

int bishopSquareEval[64]{
	0,     0,     0,   0,   0,   0,    0,  0,
	0,    15,    10,  10,  10,  10,   15,  0,
	0,    10,    20,  20,  20,  20,   10,  0,
	0,     0,    15,  15,  15,  15,    0,  0,
	0,     0,     0,  10,  10,   0,    0,  0,
	0,     0,     0,   0,   0,   0,    0,  0,
	0,     0,     0,   0,   0,   0,    0,  0,
	0,     0,     0,   0,   0,   0,    0,  0,
};


// TODO: Add evaluation for rooks on open files
int rookSquareEval[64]{
	0,     0,     0,  10,  10,   5,    0,   0,
	0,     0,     0,   5,   5,   0,    0,   0,
	0,     0,     0,   0,   0,   0,    0,   0,
	0,     0,     0,   0,   0,   0,    0,   0,
	0,     0,     0,   0,   0,   0,    0,   0,
	0,     0,     0,   0,   0,   0,    0,   0,
	20,    20,    20,  20,  20,  20,   20,  20,
	0,     0,     0,   0,   0,   0,   0,    0,
};

int queenSquareEval[64]{
   -5,   -5,    -5,   0,   0,   0,   0, -5,
	0,    0,     0,  10,  10,  10,   0,  0,
	0,    0,    15,  15,  15,  15,   0,  0,
	5,    0,    20,  20,  20,  20,   0,  5,
	5,    0,    20,  20,  20,  20,   0,  5,
	0,    0,    15,  15,  15,  15,   0,  0,
	0,    0,     0,   0,   0,   0,   0,  0,
	0,    0,     0,   0,   0,   0,   0,  0,
};


// TODO: Fill this in
int kingSquareEval[64]{
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
	0,    0,    0,  0,  0,  0,   0,  0,
};

int blackSquareMirror[64]{
	56, 57, 58, 59, 60, 61, 62, 63,
	48, 49, 50, 51, 52, 53, 54, 55,
	40, 41, 42, 43, 44, 45, 46, 47,
	32, 33, 34, 35, 36, 37, 38, 39,
	24, 25, 26, 27, 28, 29, 30, 31,
	16, 17, 18, 19, 20, 21, 22, 23,
	8,   9, 10, 11, 12, 13, 14, 15,
	0,   1,  2,  3,  4,  5,  6,  7,
};

/* clang-format on */
int calc_centipawns(int board_idx, Piece cur_piece, Color current_side) {
    // Calculates the centipawn score for the given piece
    // The score is subtracted if the piece is not of the current side.
    int centipawns = 0;
    int modifier = -1;  // Whether or not to count the position of the piece as
                        // positive or negative
    if (cur_piece % 2 == 0 && current_side == White ||
        cur_piece % 2 != 0 && current_side == Black) {
        modifier = 1;
    }
    if (PAWN(cur_piece)) {
        return modifier * pawnSquareEval[board_idx];
    }
    if (KNIGHT(cur_piece)) {
        return modifier * knightSquareEval[board_idx];
    }
    if (BISHOP(cur_piece)) {
        return modifier * bishopSquareEval[board_idx];
    }
    if (ROOK(cur_piece)) {
        return modifier * rookSquareEval[board_idx];
    }
    if (QUEEN(cur_piece)) {
        return modifier * queenSquareEval[board_idx];
    }
    if (KING(cur_piece)) {
        return modifier * kingSquareEval[board_idx];
    }
    return 0;
}

int evaluate(Board &board) {
    // Iterate through each piece for the side, summing up centipawns for each
    // positioned piece.
    // Each piece is also summed up to get values for both sides
    int positional_score = 0;
    int board_idx = 0;
    int who2move = 1;
    int black_piece_values = 0;
    int white_piece_values = 0;
    // Piece values irrespective of color (pawn, knight, bishop, rook, queen,
    // king)
    int piece_values[6] = {1, 3, 3, 5, 9, 100};
    Color current_side = board.get_to_move();
    if (current_side == Black) {
        who2move = -1;
    }
    for (int i = 0; i < 64; i++) {
        Piece cur_piece = board.board[i];
        if (cur_piece == Empty) {
            continue;
        }
        if (cur_piece % 2 == 0) {  // curent piece is white
            // cout << "Value of cur piece " << cur_piece << ": " <<
            // piece_values[cur_piece / 2] << endl;
            white_piece_values += piece_values[cur_piece / 2];
        } else {
            // cout << "Value of cur piece " << cur_piece << ". " <<
            // piece_values[(cur_piece-1)/2] << endl;
            black_piece_values += piece_values[(cur_piece - 1) / 2];
        }

        if (current_side == Black) {
            board_idx = blackSquareMirror[i];
        } else {
            board_idx = i;
        }
        positional_score += calc_centipawns(board_idx, cur_piece, current_side);
    }
    // cout << "info White piece values: " << white_piece_values << endl;
    // cout << "info Black piece values: " << black_piece_values << endl;
    // cout << "info Centipawns(positional score): " << positional_score << ",
    // current side: " << current_side << endl;
    return 100 * (white_piece_values - black_piece_values) * who2move +
           positional_score;
}
