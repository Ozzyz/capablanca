#include "board.h"
/*
This file evaluates the current chess position by using
piece-square tables and material count.
In order to save arrays, a mirror array is used to index the piece tables for black
All 'points' are measured in centipawns.
*/


// Knights are better in the center, and especially offensive center squares
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
	10,    5,   -10,  5,  5,  5,   5, 10,
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
	56,57,58,59,60,61,62,63,
	48,49,50,51,52,53,54,55,
	40,41,42,43,44,45,46,47,
	32,33,34,35,36,37,38,39,
	24,25,26,27,28,29,30,31,
	16,17,18,19,20,21,22,23,
	8,9,10,11,12,13,14,15,
	0,1,2,3,4,5,6,7,
};


int eval_board_pos(Piece board[64], int pieceCount[13], Color current_side) {
	// Iterate through each piece for the side, summing up centipawns for each positioned
	// piece
	//TODO: Implement this
	return 0;
}
