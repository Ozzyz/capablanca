
/*
   This file is responsible for parsing FEN-strings to boards.
   This will be our sole way of initializing given board states (at least for now)
 */
#include "fen.h"
using std::cout;
using std::endl;
using std::string;

int get_castle_permissions(string);

void fill_empty(Piece board[64]) {
    for (int i = 0; i < 64; i++)
    {
        board[i] = Empty;
    }
}

void parse_fen(string fen,Board &boardclass) {
    cout << "info trying to parse fen " + fen << endl;
    int castling = 0;
    Color next_move;
    int ep_square;
    // Used to keep track over when we are done parsing piece-part of fen
    int count = 0;
    int file = 7;
    int rank = 7;
    Piece pieces[64];
    fill_empty(pieces);

    int fen_pos = 0;
    for (int i = 0; i < fen.length(); i++)
    {
        fen_pos++;
        /*if (file == 0) {
          rank -= 1;
          }*/
        char cur = fen[i];
        Piece pc = Empty;
        if (isdigit(cur)) {
            // Using the fact that the difference in the chars is the difference of the value they represent
            int num_empties = cur - '0';
            file -= num_empties;
            count += num_empties;
        }
        // Encountered new row
        else if(cur == '/'){
            // Reset file counter
            file = 7;
            rank--;
        }

        else if (count >= 64){
            // Finished parsing pieces
            boardclass.set_board(pieces);
            break;
        }
        else {
            switch (cur) {
                case 'p':
                    pc = bPawn;
                    break;
                case 'P':
                    pc = wPawn;
                    break;
                case 'b':
                    pc = bBishop;
                    break;
                case 'B':
                    pc = wBishop;
                    break;
                case 'n':
                    pc = bKnight;
                    break;
                case 'N':
                    pc = wKnight;
                    break;
                case 'r':
                    pc = bRook;
                    break;
                case 'R':
                    pc = wRook;
                    break;
                case 'q':
                    pc = bQueen;
                    break;
                case 'Q':
                    pc = wQueen;
                    break;
                case 'k':
                    pc = bKing;
                    break;
                case 'K':
                    pc = wKing;
                    break;
                    // Whitespace or garbage, discard
                default:
                    pc = Empty;
                    break;
            }
            int index = 8 * rank + file;
            if (index < 0 && index < 64) {
                continue;
            }
            pieces[index] = pc;
            count++;
            file--;
        }
    }
    // Parse extra info (castling rights, en-passant square, turn to move)
    string delimiter = " ";
    fen = fen.substr(fen_pos, fen.length());
    int pos = 0;
    string token;
    std::vector<string> args;
    while ((pos = fen.find(delimiter)) != std::string::npos) {
        token = fen.substr(0, pos);
        std::cout << "info " <<pos << "Token " << token << std::endl;
        args.push_back(token);
        fen.erase(0, pos + delimiter.length());
    }
    try {
        next_move = args[0].compare("w") == 0 ? White : Black;
        //Castling
        castling = get_castle_permissions(args[1]);
        // En passant
        ep_square = args[2].compare("-") ? square_to_board_index(args[2]) : -99;
        // TODO: Turns ++

        boardclass.set_castling_rights(castling);
        boardclass.set_to_move(next_move);
        boardclass.set_ep_square(ep_square);
    }
    catch(int e){
        std::cout << "info: Could not parse fen! ";
        return;
    }
}

int get_castle_permissions(string castle_descriptor) {
    int castling = 0;
    for (int i = 0; i < castle_descriptor.length(); i++)
    {
        char cur = castle_descriptor[i];
        switch (cur) {
            case 'k':
                castling |= bCastleKing;
                break;
            case 'K':
                castling |= wCastleKing;
                break;
            case 'Q':
                castling |= wCastleQueen;
                break;
            case 'q':
                castling |= bCastleQueen;
                break;
            default:
                break;
        }
    }
    return castling;
}

