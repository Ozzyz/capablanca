//
// Created by asbr on 09.09.2019.
//

#include "gtest/gtest.h"
#include "../src/board/board.hpp"
#include <algorithm>
#include <communication/fen.hpp>
#include <vector>
class GeneratedMovesTest: public ::testing::Test {
protected:
    Board board = Board();
};


TEST_F(GeneratedMovesTest, VerifyAllGeneratedWhiteMovesInPosition){
    parse_fen("rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4", board);
    std::vector<string> white_moves = {
            // pawn moves
            "a2a3", "a2a4", "b2b3", "b2b4", "c2c3", "d2d3", "d2d4", "g2g3", "g2g4", "h2h3", "h2h4",
            // knight moves
            "b1c3", "b1a3", "f3d4", "f3g5", "f3g1", "f3e5", "f3h4",
            // bishop moves
            "c4b3", "c4d5", "c4e6", "c4f7", "c4b5", "c4a6","c4d3", "c4e2", "c4f1",
            //queen moves
            "d1e2",
            //rook moves
            "h1g1", "h1f1",
            // king moves
            "e1e2", "e1f1", "e1g1"
            };
    vector<Move> moves = generate_all_moves(White, board);
    ASSERT_EQ(white_moves.size(), moves.size()) << "Number of generated moves not equal";
    for(auto move: moves){
        string uci_move = move.uci();
        EXPECT_NE(std::find(white_moves.begin(), white_moves.end(), uci_move), white_moves.end()) << "Could not find move " + uci_move + " in white moves";
    }
}

TEST_F(GeneratedMovesTest, VerifyAllGeneratedBlackMovesInPosition){
    parse_fen("rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R b KQkq - 5 4", board);
    std::vector<string> black_moves = {
            // pawn moves
            "a7a6", "a7a5", "b7b6", "b7b5", "c7c6", "d7d6", "d7d5", "g7g6", "g7g5", "h7h6", "h7h5",
            // knight moves
            "b8c6", "b8a6", "f6d5", "f6g4", "f6g8", "f6e4", "f6h5",
            // bishop moves
            "c5b6", "c5d4", "c5e3", "c5f2", "c5b4", "c5a3","c5d6", "c5e7", "c5f8",
            //queen moves
            "d8e7",
            //rook moves
            "h8g8", "h8f8",
            // king moves
            "e8e7", "e8f8", "e8g8"
    };
    vector<Move> moves = generate_all_moves(Black, board);
    ASSERT_EQ(black_moves.size(), moves.size()) << "Number of generated moves not equal";
    for(auto move: moves){
        string uci_move = move.uci();
        EXPECT_NE(std::find(black_moves.begin(), black_moves.end(), uci_move), black_moves.end()) << "Could not find move " + uci_move + " in black moves";
    }
}