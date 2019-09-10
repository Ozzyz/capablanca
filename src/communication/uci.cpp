#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "hashing/board_hash.hpp"
#include "fen.hpp"
#include "../utils/utils.hpp"
using std::cout;
using std::endl;

Move search_moves(Board &board, std::map<std::uint64_t, int> &board_hashes,
                  Zobrist &hasher);

void make_uci_move(Move &move) {
    // Sends the given move to the uci receiver
    cout << "bestmove " << move.uci() << endl;
}

void parse_move(const string& move_string, Board &board) {
    cout << "info parsing move string " << move_string << endl;
    Move move = Move(move_string);
    cout << "info created move " << move.toString() << endl;
    board.make_move(move);
}

void parse_uci_position(const string& line, Board &board) {
    // The UCI command position is on the form
    // position [fen]
    // position startposition
    // and both can optionally end with a set of moves, for example e2e3 f7f5
    // b7b8q (Promote to queen on the b8 square)
    // TODO: Implement move info

    int end_pos = line.find("moves");
    if (line.find("startposition")) {
        board.set_position(starting_fen);
    } else {
        board.set_position(line.substr(9, end_pos));
    }
    // If we have moves, apply each move
    if (end_pos != string::npos) {
        string substring = line.substr(end_pos + 6, line.length());
        cout << "info substring " << substring << endl;
        std::istringstream iss(substring);

        string s;
        // Each move is separated by a space
        while (getline(iss, s, ' ')) {
            cout << "info parsing move " << s
                 << "Lenght of move: " << s.length() << endl;
            parse_move(s, board);
        }
    }
}

void parse_uci_go(const string& line, Board &board,
                  std::map<uint64_t, int> board_hashes, Zobrist hasher) {
    // Example format: go wtime 289536 btime 300000 winc 0 binc 0
    // Find all moves
    vector<Move> moves = generate_all_moves(board);
    cout << "info choosing best move out of " << moves.size()
         << "available moves" << endl;
    // Make move (for now, just select the first)
    // TODO: Replace this with call to move search
    cout << "info Considering " << moves.size() << " moves" << endl;
    for (auto &move : moves) {
        cout << "\t " << move.toAlgebraic() << endl;
    }
    Move chosen_move = search_moves(board, board_hashes, hasher);
    // Move chosen_move = moves[0];
    // Make the move on the board
    board.make_move(chosen_move);
    print_board(board.board);
    // Return move to UCI engine
    make_uci_move(chosen_move);
}

void uci_loop(Board &board) {
    // Initialize hash helpers
    // TODO: Move this?
    std::map<uint64_t, int> board_hashes;
    Zobrist hasher = Zobrist();

    cout << "info entering uci parse loop!" << endl;
    string line;
    // Parse input from GUI
    while (true) {
        std::getline(std::cin, line);
        if (line.compare(0, 3, "uci") == 0) {
            // Send ready signal and info to the UCI-GUI
            cout << "id name Sisyphus" << endl;
            cout << "id author Ozzyz" << endl;
            cout << "uciok" << endl;
        }
        if (line.compare(0, 7, "isready") == 0) {
            cout << "readyok" << endl;
        }
        if (line.compare(0, 8, "position") == 0) {
            parse_uci_position(line, board);
        }
        if (line.compare(0, 2, "go") == 0) {
            parse_uci_go(line, board, board_hashes, hasher);
        }
        if (line.compare(0, 5, "quit") == 0) {
            break;
        }
    }
}
