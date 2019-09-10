#include "negamax.hpp"
#include "hashing/board_hash.hpp"

using namespace std;
int MAX_DEPTH = 6;
int evaluate(Board &board);

vector<Move> generate_all_moves(Board &board);

int negamax(Board &board, int alpha, int beta, int depth,
            map<uint64_t, int> &board_hashes, Zobrist &hasher) {
    /*  Takes as input a board and searches the game tree for the optimal move.
        Arguments:
            board - reference to the current board state
            depth - the current searched depth
            is_max - Whether or not the current player is the one trying to
       maximize score
    */
    int max = -999999;
    int score = 0;
    // If the board value has been calculated already, return the previous
    // calculated score
    uint64_t board_hash = hasher.hash(board);
    auto it = board_hashes.find(board_hash);
    if (it != board_hashes.end()) {
        score = board_hashes.at(board_hash);
        cout << "info Found hash for board " << board_hash << " " << score <<
        endl;
        return score;
    }
    if (depth == MAX_DEPTH) {
        cout << "info Reached maxdepth -- evaluating boardstate";
        return evaluate(board);
    }
    // Iterate through all candidate moves
    vector<Move> available_moves =
        generate_all_moves(board);
    for (auto &move : available_moves) {
        // Apply move to board
        Board board_copy = Board(board);
        // Skip move if it is not valid (for instance not moving king in check, or castling through check)
        if (!board_copy.make_move(move)) {
            cout << "info Undid move - illegal " << move.toAlgebraic() << endl;
            continue;
        }
        score =
            -negamax(board_copy, alpha, beta, depth + 1, board_hashes, hasher);
        if (score > max) {
            board_hashes.insert(pair<uint64_t, int>(board_hash, score));
            max = score;
        }
        if (score >= alpha) {
            alpha = score;
        }
        if (alpha >= beta) {
            break;
        }
    }
    return max;
}

Move search_moves(Board &board, map<std::uint64_t, int> &board_hashes,
                  Zobrist &hasher) {
    /*  This is the main method for doing negamax with alpha-beta pruning.
        In:
            board - The current board state
            board_scores - A map over previous explored board states where k is
       the hash of the board defined by board_hash and the value is the score in
       centipawns.
    */
    cout << "info entering search_moves (negamax) with alpha beta pruning. Max "
            "depth "
         << MAX_DEPTH << endl;

    // Iterate through all candidate moves
    vector<Move> available_moves =
        generate_all_moves(board);
    cout << "info found " << available_moves.size() << " available moves."
         << endl;
    int max = -999999;
    int score = 0;
    int alpha = -999999;
    int beta = 999999;
    Move best_move;

    for (auto &move : available_moves) {
        cout << "info Applying move " << move.toAlgebraic() << endl;
        // Apply move to board
        Board board_copy = Board(board);
        if (!board_copy.make_move(move)) {
            cout << "info Undid move - illegal " << move.toAlgebraic() << endl;
            continue;
        }

        uint64_t board_hash = hasher.hash(board);
        auto it = board_hashes.find(board_hash);
        score = -negamax(board_copy, alpha, beta, 0, board_hashes, hasher);
        // If the board is not hashed already
        if (it == board_hashes.end()) {
            cout << "info board state not hashed already - hashing..." << endl;
            // Save score of hash for later
            board_hashes.insert(pair<uint64_t, int>(board_hash, score));
        }
        if (score > max) {
            cout << "info considering move " << move.toAlgebraic()
                 << ", score: " << score << endl;
            best_move = move;
            max = score;
        }
    }
    cout << "info found best move to be " << best_move.toAlgebraic()
         << " with score " << score << endl;
    return best_move;
}
