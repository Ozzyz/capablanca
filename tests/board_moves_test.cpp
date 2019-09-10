//
// Created by asbr on 09.09.2019.
//
#include "../src/board/board.hpp"
#include "gtest/gtest.h"
#include <utils/utils.hpp>
class BoardMovesTest: public ::testing::Test {
protected:
    Board board = Board();
};

TEST_F(BoardMovesTest, MovingKingRookRemovesCastlingRights){
    // Move king knights for both players, then move rooks.
    // Then, check if castling rights are correct for both players
    Move moves[4] = {Move("g1f3"), Move("g8f6"), Move("h1g1"), Move("h8g8")};
    for(auto move: moves){
        // Make move returns success if the move is applied and legal
        bool success = board.make_move(move);
        EXPECT_EQ(true, success);
    }
    // Check that board state matches up with expected moves
    EXPECT_EQ(board.board[F3], wKnight);
    EXPECT_EQ(board.board[F6], bKnight);
    EXPECT_EQ(board.board[G1], wRook);
    EXPECT_EQ(board.board[G8], bRook);
    EXPECT_EQ(board.board[H1], Empty);
    EXPECT_EQ(board.board[H8], Empty);
    // Check that castling is only available for both players on queenside
    EXPECT_EQ(board.get_castling_rights(), bCastleQueen | wCastleQueen);

}

TEST_F(BoardMovesTest, MovingQueenRookRemovesCastlingRights){
    // Move queen rook for both players, check that castling rights are only available kingside
    Move moves[4] = {Move("b1c3"), Move("b8c6"), Move("a1b1"), Move("a8b8")};
    for(auto move: moves){
        // Make move returns success if the move is applied and legal
        bool success = board.make_move(move);
        EXPECT_EQ(true, success);
    }
    // Check that board state matches up with expected moves
    EXPECT_EQ(board.board[C3], wKnight);
    EXPECT_EQ(board.board[C6], bKnight);
    EXPECT_EQ(board.board[B1], wRook);
    EXPECT_EQ(board.board[B8], bRook);
    EXPECT_EQ(board.board[A1], Empty);
    EXPECT_EQ(board.board[A8], Empty);
    // Check that castling is only available for both players on queenside
    EXPECT_EQ(board.get_castling_rights(), bCastleKing | wCastleKing);
}

TEST_F(BoardMovesTest, MovingKingRemovesAllCastlingRights){
    Move moves[4] = {Move("e2e4"), Move("e7e5"), Move("e1e2"), Move("e8e7")};
    for(auto move: moves){
        // Make move returns success if the move is applied and legal
        bool success = board.make_move(move);
        EXPECT_EQ(true, success);
    }
    // Check that board state matches up with expected moves
    EXPECT_EQ(board.board[E4], wPawn);
    EXPECT_EQ(board.board[E5], bPawn);
    EXPECT_EQ(board.board[E2], wKing);
    EXPECT_EQ(board.board[E7], bKing);
    EXPECT_EQ(board.board[E1], Empty);
    EXPECT_EQ(board.board[E8], Empty);
    // Check that castling is not available on any side
    EXPECT_EQ(board.get_castling_rights(), 0);

}
