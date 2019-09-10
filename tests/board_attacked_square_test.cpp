
#include "../src/board/board.hpp"
#include "gtest/gtest.h"

class BoardAttackedSquaresTest: public ::testing::Test {
protected:
    void SetUp() override {
        // Testboard: https://lichess.org/editor/r1bqkb1r/ppp1pppp/2n3P1/Q5Rn/8/B6p/PPPPPPPP/RN2KBN1_w_KQkq_-
        Piece testboard[64] = {
                Empty, wKnight, wBishop, wKing, Empty, Empty, wKnight, wRook,
                wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn,
                bPawn, Empty, Empty, Empty, Empty, Empty, Empty, wBishop,
                Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
                bKnight, wRook, Empty, Empty, Empty, Empty, Empty, wQueen,
                Empty, wPawn, Empty, Empty, Empty, bKnight, Empty, Empty,
                bPawn, bPawn, bPawn, bPawn, Empty, bPawn, bPawn, bPawn,
                bRook, bKnight, bBishop, bKing, bQueen, bBishop, Empty, bRook,
        };

        init_board(testboard);
        boardc.set_board(testboard);
        // Set up board with default fen
    }
    Board boardc = Board();
};

    TEST_F(BoardAttackedSquaresTest, Verify_G6_Pawn_Attacks_Two_Squares)
    {
        EXPECT_EQ(true, is_attacked(48, White));
        EXPECT_EQ(true, is_attacked(50, White));

    }

    TEST_F(BoardAttackedSquaresTest, Verify_Unattacked_Squares) {
        // Squares that should not be attacked
    EXPECT_EQ(false, is_attacked(0, Black));
    EXPECT_EQ(false, is_attacked(1, Black));
    EXPECT_EQ(false, is_attacked(5, Black));
    }

    TEST_F(BoardAttackedSquaresTest, Verify_H3_Pawn_Attacks_One_Square)
    {
        EXPECT_EQ(true, is_attacked(9, Black));
        EXPECT_EQ(false, is_attacked(11, Black));
    }

    TEST_F(BoardAttackedSquaresTest, Verify_A3_Bishop_Attacks_One_Square_On_Diagonal)
    {
        EXPECT_EQ(true, is_attacked(51, White));
        EXPECT_EQ(false, is_attacked(58, White));

    }
    TEST_F(BoardAttackedSquaresTest, Verify_C6_Knight_Attacks_Multiple_Squares)
    {
        EXPECT_EQ(true, is_attacked(62, Black));
        EXPECT_EQ(true, is_attacked(55, Black));
        EXPECT_EQ(true, is_attacked(60, Black));
        EXPECT_EQ(true, is_attacked(51, Black));
        EXPECT_EQ(true, is_attacked(39, Black));
        EXPECT_EQ(true, is_attacked(35, Black));
        EXPECT_EQ(true, is_attacked(28, Black));
    }
    TEST_F(BoardAttackedSquaresTest, Verify_D8_Queen_Attacks_White_D2_Pawn)
    {
        EXPECT_EQ(true, is_attacked(12, Black));
    }

    TEST_F(BoardAttackedSquaresTest, Verify_A5_Queen_Attacks_Multiple_Pawns_And_Not_H5_Knight)
    {
        EXPECT_EQ(true, is_attacked(55, White));
        EXPECT_EQ(true, is_attacked(53, White));
    }

    TEST_F(BoardAttackedSquaresTest, MakeMove_G2ToG3_Returns_CorrectModifiedBoard) {
        int from_square = square_to_board_index("g2");
        int to_square = square_to_board_index("g3");
        Move move = Move(from_square, to_square, Quiet);

        // Assert that the square is occupied by a pawn from the start
        EXPECT_EQ(wPawn, boardc.board[from_square]);
        boardc.make_move(move);
        EXPECT_EQ(Empty, boardc.board[from_square]);
        EXPECT_EQ(wPawn, boardc.board[to_square]);
    }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}