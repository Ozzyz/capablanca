//
// Created by asbr on 09.09.2019.
//

#include <communication/fen.hpp>
#include "../src/board/board.hpp"
#include "gtest/gtest.h"

/*
 * starting fen is parsed correctly
 * castling rights are preserved
 * moves such as promotions are kept
 * en-passant is kept
 */

class FenParingTest: public ::testing::Test {
protected:
    void SetUp() override {
        // initialize the starting position
        board = Board();
    }
    Board board;
};


TEST_F(FenParingTest, StartingFenIsParsedCorrectly){
    parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board);
    // Castling is represented as 4 bits where two leftmost are white king and queenside, and other are black king and queenside.
    EXPECT_EQ(board.get_castling_rights(), wCastleKing | wCastleQueen| bCastleKing | bCastleQueen);
    EXPECT_EQ(board.get_ep_square(), -99);
    // White pieces
    EXPECT_EQ(board.board[A1], wRook);
    EXPECT_EQ(board.board[B1], wKnight);
    EXPECT_EQ(board.board[C1], wBishop);
    EXPECT_EQ(board.board[D1], wQueen);
    EXPECT_EQ(board.board[E1], wKing);
    EXPECT_EQ(board.board[F1], wBishop);
    EXPECT_EQ(board.board[G1], wKnight);
    EXPECT_EQ(board.board[H1], wRook);
    // Black pieces
    EXPECT_EQ(board.board[A8], bRook);
    EXPECT_EQ(board.board[B8], bKnight);
    EXPECT_EQ(board.board[C8], bBishop);
    EXPECT_EQ(board.board[D8], bQueen);
    EXPECT_EQ(board.board[E8], bKing);
    EXPECT_EQ(board.board[F8], bBishop);
    EXPECT_EQ(board.board[G8], bKnight);
    EXPECT_EQ(board.board[H8], bRook);
    // Turns
    EXPECT_EQ(board.get_to_move(), White);
}

TEST_F(FenParingTest, EnPassantFenIsParsedCorrectly){
    // In this fen, en passant is available at the f6 square.
    // White has castled kingside and black has moved their queenside rook. Thus, the only available castle is black kingside
    // It is whites turn to move
    parse_fen("1r1qkbnr/p1pnp1p1/Bpb4p/3pPp2/3P4/P1P2N2/1P3PPP/RNBQ1RK1 w k f6 0 9", board);
    // Castling is represented as 4 bits - see CastlePermissions enum
    EXPECT_EQ(board.get_castling_rights(), bCastleKing);
    int f6_index = 42;
    EXPECT_EQ(board.get_ep_square(), f6_index);
    // White pieces
    EXPECT_EQ(board.board[A1], wRook);
    EXPECT_EQ(board.board[B1], wKnight);
    EXPECT_EQ(board.board[C1], wBishop);
    EXPECT_EQ(board.board[D1], wQueen);
    EXPECT_EQ(board.board[E1], Empty);
    EXPECT_EQ(board.board[F1], wRook);
    EXPECT_EQ(board.board[G1], wKing);
    EXPECT_EQ(board.board[H1], Empty);
    // Black pieces
    EXPECT_EQ(board.board[A8], Empty);
    EXPECT_EQ(board.board[B8], bRook);
    EXPECT_EQ(board.board[C8], Empty);
    EXPECT_EQ(board.board[D8], bQueen);
    EXPECT_EQ(board.board[E8], bKing);
    EXPECT_EQ(board.board[F8], bBishop);
    EXPECT_EQ(board.board[G8], bKnight);
    EXPECT_EQ(board.board[H8], bRook);
    // Turns
    EXPECT_EQ(board.get_to_move(), White);
}
