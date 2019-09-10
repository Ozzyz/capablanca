//
// Created by asbr on 10.09.2019.
//
#include <board/board.hpp>
#include <gtest/gtest.h>
#include <communication/fen.hpp>

class CastlingMovesTest: public ::testing::Test {
protected:
    void SetUp() override {
        // initialize the starting position to a position where both colors have the possibility to castle to both sides
        board = Board();
        parse_fen("r3k2r/pbppqppp/1pnbpn2/8/3P4/2NBPN2/PPPBQPPP/R3K2R w KQkq - 4 8", board);
    }
    Board board;
};



TEST_F(CastlingMovesTest, CastlingWhiteKingsideMovesPiecesCorrectly){
    // Try to castle kingside, then check that pieces are moved correctly
    Move move = Move("e1g1");
    board.make_move(move);
    EXPECT_EQ(board.board[E1], Empty);
    EXPECT_EQ(board.board[F1], wRook);
    EXPECT_EQ(board.board[G1], wKing);
    EXPECT_EQ(board.board[H1], Empty);
}

TEST_F(CastlingMovesTest, CastlingWhiteQueensideMovesPiecesCorrectly){
    // Try to castle kingside, then check that pieces are moved correctly
    Move move = Move("e1c1");
    board.make_move(move);
    EXPECT_EQ(board.board[E1], Empty);
    EXPECT_EQ(board.board[D1], wRook);
    EXPECT_EQ(board.board[C1], wKing);
    EXPECT_EQ(board.board[A1], Empty);
}

TEST_F(CastlingMovesTest, CastlingBlackKingsideMovesPiecesCorrectly){
    // Try to castle kingside, then check that pieces are moved correctly
    Move move = Move("e8g8");
    board.make_move(move);
    EXPECT_EQ(board.board[E8], Empty);
    EXPECT_EQ(board.board[F8], bRook);
    EXPECT_EQ(board.board[G8], bKing);
    EXPECT_EQ(board.board[H8], Empty);
}

TEST_F(CastlingMovesTest, CastlingBlackQueensideMovesPiecesCorrectly){
    // Try to castle kingside, then check that pieces are moved correctly
    Move move = Move("e8c8");
    board.make_move(move);
    EXPECT_EQ(board.board[E8], Empty);
    EXPECT_EQ(board.board[D8], bRook);
    EXPECT_EQ(board.board[C8], bKing);
    EXPECT_EQ(board.board[A8], Empty);
}