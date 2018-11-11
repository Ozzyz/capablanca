#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include "move.h"

using std::string;
using std::vector;

// Handy square definitions
static const int A1 = 7;
static const int H8 = 56;
static const int A8 = 0;
static const int H1 = 63;

typedef enum
{
    wCastleKing = 8,
    wCastleQueen = 4,
    bCastleKing = 2,
    bCastleQueen = 1
} CastlePermissions;

class Board
{
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
        Piece board[BOARD_SIZE];
        // Each piece number corresponds to the index.
        //The 13th space is to count number of empty squares (useful for evaluating open/closed positions)
        int piece_count_list[13] = {0};
        int get_ep_square();
        int get_castling_rights();
        Color get_to_move();
        int get_turn();
        void set_turn(int turn);
        void set_to_move(Color to_move);
        void set_ep_square(int ep_square);
        void set_castling_rights(int castling);
        void set_board(Piece pieces[64]);
        void make_move(Move &move);
        void update_piece_count_list(Move &move);
        void set_position(string fen);
};

static const string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

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

