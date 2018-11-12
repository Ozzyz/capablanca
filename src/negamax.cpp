#include "negamax.hpp"

using namespace std;
int MAX_DEPTH = 4;
int evaluate(Board &board);
vector<Move> generate_all_moves(Color current_side, Board &board);

int negamax(Board &board, int alpha, int beta, int depth){
    /*  Takes as input a board and searches the game tree for the optimal move.
        Arguments:
            board - reference to the current board state
            depth - the current searched depth
            is_max - Whether or not the current player is the one trying to maximize score
    */
    int max = -999999;
    int score = 0; 
    if(depth == MAX_DEPTH){
        return evaluate(board);
    }
    // Iterate through all candidate moves
    // TODO: Change generate_all_moves to only take in board
    vector<Move> available_moves = generate_all_moves(board.get_to_move(), board);
    for(auto &move: available_moves) { 
        // Apply move to board
        Board board_copy = Board(board);
        // Skip move if it is not valid
        if(!board_copy.make_move(move)){
            cout << "Undid move - illegal " << move.toAlgebraic() << endl;
            continue;
        } 
        score = -negamax(board_copy, alpha, beta, depth+1);
        if(score > max){
            max = score;
        }
        if(alpha >= beta){
            break;
        }
    }
    return max;
}

Move search_moves(Board &board){
    /*  This is the main method for doing negamax with alpha-beta pruning. 
    */
    cout << "info entering search_moves (negamax) with alpha beta pruning. Max depth " << MAX_DEPTH << endl;
    // Iterate through all candidate moves
    vector<Move> available_moves = generate_all_moves(board.get_to_move(), board);
    cout << "info found " << available_moves.size() << " available moves." << endl;
    int max = -999999;
    int score = 0;
    int alpha = -999999;
    int beta = 999999;
    Move best_move;
    for(auto &move: available_moves) {
        cout << "info Applying move " << move.toAlgebraic() << endl;
        // Apply move to board
        Board board_copy = Board(board);
        if(!board_copy.make_move(move)){
            cout << "Undid move - illegal " << move.toAlgebraic() << endl;
            continue;
        } 
        score = -negamax(board_copy, alpha, beta, 0);
        if(score > max){
            cout << "info considering move " << move.toAlgebraic() << ", score: " << score << endl;
            best_move = move;
            max = score;
        }
    }
    cout << "info found best move to be " << best_move.toAlgebraic() << " with score " << score <<  endl;
    return best_move;
}
