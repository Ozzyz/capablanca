#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "move.hpp"
#include "utils.hpp"

using std::string;
using std::vector;

// Handy square definitions
static const int A1 = 7;
static const int A8 = 63;
static const int B8 = 62;
static const int C8 = 61;
static const int D8 = 60;
static const int E8 = 59;
static const int F8 = 58;
static const int G8 = 57;
static const int H8 = 56;
static const int B1 = 6;
static const int C1 = 5;
static const int D1 = 4;
static const int H1 = 0;
static const int G1 = 1;
static const int F1 = 2;

static const int WHITE_KING_START = 3;
static const int BLACK_KING_START = E8;

typedef enum {
    wCastleKing = 8,
    wCastleQueen = 4,
    bCastleKing = 2,
    bCastleQueen = 1
} CastlePermissions;

class Board {
   private:
    static const int NUM_BOARD_SQUARES = 10 * 12;
    static const int BOARD_SIZE = 64;
    // Square that can be attacked en passant, if viable, else 99
    int ep_square;
    int turn;
    /* Used to keep track over castling rights
             The two leftmost bits is whether white can castle
             First is Queenside, then Kingside
             The same for black (two rightmost bits)
           */
    int castling;
    // Which side to move next
    Color to_move;

   public:
    Board();
    Board(string fen);
    Board(const Board &board);
    Piece board[BOARD_SIZE];
    // Each piece number corresponds to the index.
    // The 13th space is to count number of empty squares (useful for evaluating
    // open/closed positions)
    int piece_count_list[13] = {0};
    int get_ep_square() const;
    int get_castling_rights() const;
    Color get_to_move() const;
    int get_turn() const;
    void set_turn(int turn);
    void set_to_move(Color to_move);
    void set_ep_square(int ep_square);
    void set_castling_rights(int castling);
    void set_board(Piece pieces[64]);
    bool make_move(Move &move);
    void update_piece_count_list(Move &move);
    void set_position(string fen);
    bool is_illegal_state();
};

static const string starting_fen =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

extern Piece piece[64];
extern Piece init_piece[64];
extern int mailbox_board[120];
extern int board_map[64];
bool in_check(Color color);
void init_board(Piece piece[]);
void init_board();
bool is_attacked(int square, Color color);
bool is_color(Piece piece, Color color);

vector<Move> generate_all_moves(Color, Board &);
void generate_move(int from, int to, int flags, vector<Move> &);
