#pragma once
#include <string>
using std::string;
#include "utils.hpp"
/*
   The move is represented by a 16-bit field
   From lowest to highest:
   6 bit - From square
   6 bit - To square
   4 bit - Special moves (pawn promotion, where each bit is promote to {Knight, Bishop, Rook, Queen}
   Table for the last 4 bits:

0000 : quiet moves (No captures or promotions)
0001 : double pawn push (Move two squares from initial pawn position)
0010 : King castle
0011 : Queen castle
0100 : Captures
0101 : En-passant capture
0110 : Unused
0111 : Unused
1000 : Knight promotion
1001 : Bishop promotion
1010 : Rook promotion
1011 : Queen promotion
1100 :Knight promotion capture
1101 : Bishop promotion capture
1110 :  Rook promotion capture
1111 : Queen promotion capture
 */



typedef enum {
    Quiet = 0,
    DoublePawn = 1,
    KCastle = 2,
    QCastle = 3,
    Capture = 4,
    EnPassant = 5,
    KnightPromo = 8,
    BishopPromo = 9,
    RookPromo = 10,
    QueenPromo = 11,
    KnightPromoCapture = 12,
    BishopPromoCapture = 13,
    RookPromoCapture = 14,
    QueenPromoCapture = 15
}MoveType;

class Move {
    protected:
        unsigned short move;
    public:

        bool operator==(Move a) const { return (move & 0xffff) == (a.move & 0xffff); }
        bool operator!=(Move a) const { return (move & 0xffff) != (a.move & 0xffff); }

        string uci();

        bool is_promotion();
        Move();
        Move(unsigned int from, unsigned int to, unsigned int flags);

        explicit Move(string move_string);

        unsigned int from_square();

        unsigned int to_square();

        unsigned int get_flags();

        bool is_capture();

        string toString();
        string toAlgebraic();
};


