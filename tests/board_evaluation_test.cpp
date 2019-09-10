//
// Created by asbr on 10.09.2019.
//
#include <gtest/gtest.h>
#include <communication/fen.hpp>
#include <evaluation/evaluation.hpp>
/* Evaluate some positions that are obviously better for one side */

TEST(BoardEvaluation, StartPositionWhiteHasRookOddsIsBadForWhite){
    Board board = Board();
    parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w Kkq - 0 1", board);
    int score = evaluate(board);
    EXPECT_LE(0, score);
}


TEST(BoardEvaluation, StartPositionWhiteHasRookOddsIsGoodForBlack){
    Board board = Board();
    parse_fen("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/1NBQKBNR b Kkq - 0 1", board);
    int score = evaluate(board);
    EXPECT_LE(0, score);
}

TEST(BoardEvaluation, PositionWhereBlackIsUnderdevelopedIsBadForBlack){
    Board board = Board();
    parse_fen("r1bq1b1r/pp1ppk2/n1p2ppn/7p/2PP1B2/2NBPN1P/PP3PP1/R2QK2R b K - 0 1", board);
    int score = evaluate(board);
    EXPECT_LE(0, score);
}


