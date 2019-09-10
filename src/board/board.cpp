#include "board.hpp"

/*
   This is the main core of the chess engine - the board
   This board is using a 10x12 layout (see
    ) White pieces start at
   index 0 (top)
 */

void parse_fen(string, Board &);

Board::Board() { parse_fen(starting_fen, *this); }

Board::Board(string fen) : Board() { parse_fen(fen, *this); }

Board::Board(const Board &other) {
    // Copy board state
    ep_square = other.get_ep_square();
    turn = other.get_turn();
    castling = other.get_castling_rights();
    to_move = other.get_to_move();
    // Copy board and piece count arrays
    std::copy(std::begin(other.board), std::end(other.board),
              std::begin(board));
    std::copy(std::begin(other.piece_count_list),
              std::end(other.piece_count_list), std::begin(piece_count_list));
}

int Board::get_ep_square() const { return ep_square; }

unsigned int Board::get_castling_rights() const { return castling; }

Color Board::get_to_move() const { return to_move; }

int Board::get_turn() const { return turn; }

void Board::set_turn(int _turn) { turn = _turn; }

void Board::set_to_move(Color _to_move) { to_move = _to_move; }

void Board::set_ep_square(int _ep_square) { ep_square = _ep_square; }

void Board::set_castling_rights(int _castling) { castling = _castling; }

void Board::set_board(Piece pieces[64]) {
    for (int i = 0; i < 64; i++) {
        board[i] = pieces[i];
    }
}

bool Board::make_move(Move &move) {
    // Makes the given move on the board, update piece count for
    // captures/promotions Returns true if the move is legal and applied, else
    // false

    // TODO: Check if the move is king or rook. If it is, deny castling rights
    Piece moved = board[move.from_square()];
    board[move.from_square()] = Empty;
    board[move.to_square()] = moved;
    if(moved == wKing){
        if(move.from_square() == E1 && move.to_square() == G1){
            // Move rook from H1 to F1
            board[H1] = Empty;
            board[F1] = wRook;
        }
        if(move.from_square() == E1 && move.to_square() == C1){
            // Move white rook from A1 to D1
            board[A1] = Empty;
            board[D1] = wRook;
        }
    }
    if(moved == bKing){
        if(move.from_square() == E8 && move.to_square() == G8){
            // Move rook from H8 to F8
            board[H8] = Empty;
            board[F8] = bRook;
        }
        if(move.from_square() == E8 && move.to_square() == C8){
            // Move white rook from A8 to D8
            board[A8] = Empty;
            board[D8] = bRook;
        }
    }

    if(moved == wKing){
        // Remove all white castling rights
        unsetCastlingRights(wCastleQueen);
        unsetCastlingRights(wCastleKing);
    }
    if(moved == bKing){
        unsetCastlingRights(bCastleQueen);
        unsetCastlingRights(bCastleKing);
    }
    if(move.from_square() == A1 && moved == wRook){
        // Even though this will be true for all times we move a rook from
        // A1, it is true the first time it happens, and that is what matters
        unsetCastlingRights(wCastleQueen);
    }
    if(move.from_square() == H1 && moved == wRook){
        unsetCastlingRights(wCastleKing);
    }
    if(move.from_square() == A8 && moved == bRook){
        // Even though this will be true for all times we move a rook from
        // A1, it is true the first time it happens, and that is what matters
        unsetCastlingRights(bCastleQueen);
    }
    if(move.from_square() == H8 && moved == bRook){
        unsetCastlingRights(bCastleKing);
    }

    if (is_illegal_state()) {
        // Reverse the move
        board[move.from_square()] = moved;
        board[move.to_square()] = Empty;
        return false;
    }
    to_move = to_move ^ 1;
    update_piece_count_list(move);
    return true;
}

void Board::unsetCastlingRights(CastlePermissions permission){
    // Castling permissions are controlled by 1 bit each, in total 4 bits.
    // Therefore, remove all
    castling &= (~permission & 0xF);
}

void Board::update_piece_count_list(Move &move) {
    // Since a move can be both a capture and a promotion, we need to check for
    // both
    // TODO: Implement this.
}

void Board::set_position(string fen) { parse_fen(fen, *this); }

bool Board::is_illegal_state() {
    /*  Returns true if the board is in an illegal state
        This is in order to make move generation easier, since we are
        not checking whether or not a move is illegal, only if it
        generates an illegal board state after being applied
    */
    // Check if the king of the opposite side is in check
    // std::cout << "info Checking if color " << to_move << " has king in check"
    // << std::endl;
    return in_check(to_move);
}

Piece piece[64] = {};

// Initial piece placement
Piece init_piece[64] = {
    wRook, wKnight, wBishop, wKing, wQueen, wBishop, wKnight, wRook,
    wPawn, wPawn,   wPawn,   wPawn, wPawn,  wPawn,   wPawn,   wPawn,
    Empty, Empty,   Empty,   Empty, Empty,  Empty,   Empty,   Empty,
    Empty, Empty,   Empty,   Empty, Empty,  Empty,   Empty,   Empty,
    Empty, Empty,   Empty,   Empty, Empty,  Empty,   Empty,   Empty,
    Empty, Empty,   Empty,   Empty, Empty,  Empty,   Empty,   Empty,
    bPawn, bPawn,   bPawn,   bPawn, bPawn,  bPawn,   bPawn,   bPawn,
    bRook, bKnight, bBishop, bKing, bQueen, bBishop, bKnight, bRook,
};

/* clang-format off */
int mailbox_board[120] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, -1,
    -1, 8, 9, 10, 11, 12, 13, 14, 15, -1,
    -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
    -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
    -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
    -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
    -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
    -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
// Mapping of real squares to indexes of 10x12 board
int board_map[64] = {
    21, 22, 23, 24, 25, 26, 27, 28,
    31, 32, 33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48,
    51, 52, 53, 54, 55, 56, 57, 58,
    61, 62, 63, 64, 65, 66, 67, 68,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88,
    91, 92, 93, 94, 95, 96, 97, 98};

/* clang-format on */

bool slide[6] = {false, false, true, true, true, false};
/* number of knight or ray directions the piece can move
   0 is pawn, 1 knight, 2 bishop ...*/
int num_directions[6] = {0, 8, 4, 4, 8, 8};

/* The distance to every square the piece can reach. This is specified relative
   to the full board (120)*/
int offset[6][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {-21, -19, -12, -8, 8, 12, 19, 21}, /* KNIGHT */
    {-11, -9, 9, 11, 0, 0, 0, 0},       /* BISHOP */
    {-10, -1, 1, 10, 0, 0, 0, 0},       /* ROOK */
    {-11, -10, -9, -1, 1, 9, 10, 11},   /* QUEEN */
    {-11, -10, -9, -1, 1, 9, 10, 11}    /* KING */
};

bool in_check(Color color) {
    // Returns true if the king of given color is in check

    Piece king = color == White ? wKing : bKing;
    for (int square = 0; square < 64; square++) {
        if (piece[square] == king) {
            bool attacked_king = is_attacked(square, color ^ 1);

            if (attacked_king) {
                // std::cout << "info King " << king << " is attacked by color "
                // << (color ^ 1) << " on square " << square << std::endl;
            } else {
                // std::cout << "info King " << king << " is not attacked by
                // color " << (color ^1) << "on square " << square << std::endl;
            }
            return attacked_king;
        }
    }
    return false;
}

bool is_attacked(int square, Color atk_color) {
    // Returns true if the square is attacked by pieces with the given color
    int mod = atk_color == Black ? -1 : 1;
    for (int i = 0; i < 64; i++) {
        if (is_color(piece[i], atk_color)) {
            Piece pc = piece[i];
            if (PAWN(pc)) {
                // Reverse attacking direction if black
                if (COL(i) != 7 && (i + 7 * mod) == square) {
                    return true;
                }
                if (COL(i) != 0 && (i + 9 * mod) == square) {
                    return true;
                }
            } else {
                // Look at available moves for each piece. Check if it is within
                // bounds
                int piece_type = pc >> 1;
                for (int j = 0; j < num_directions[piece_type];
                     ++j) {             /* for all knight or ray directions */
                    for (int n = i;;) { /* starting with from square */
                        n = mailbox_board[board_map[n] +
                                          offset[piece_type][j]]; /* next square
                                                                     along the
                                                                     ray j */
                        if (n == square) {
                            return true;
                        }
                        if (n == -1) break; /* outside board */
                        if (piece[n] != Empty) {
                            break;
                        }  // Piece is blocking path
                        if (!slide[piece_type]) {
                            break;
                        }
                    }
                }
            }
        }
    }
    return false;
}

vector<Move> generate_all_moves(Board &board) {
    // Add all possible pseudomoves (include illegal moves, for example that the
    // moves puts the moving color in check)
    // TODO: Castling moves
    // TODO: Dont calculate this each round, maybe use some delta-algorithm?
    Color current_side = board.get_to_move();
    Color opponent_color = current_side ^ 1;

    vector<Move> moves;
    // Reverse attacking direction if black
    int mod = current_side == Black ? -1 : 1;
    int king_square = 0;
    for (int i = 0; i < 64; i++) {
        if (is_color(board.board[i], current_side)) {
            Piece pc = board.board[i];
            if (KING(pc)) {
                king_square = i;
            }
            // Pawn moves
            if (PAWN(pc)) {
                // TODO: Check en passant
                // Regular pawn captures (that may lead to promotion)
                if (COL(i) != 7 &&
                    is_color(board.board[(i + 7 * mod)], opponent_color)) {
                    generate_move(i, i + 7 * mod, Capture, moves);
                }
                if (COL(i) != 0 &&
                    is_color(board.board[(i + 9 * mod)], opponent_color)) {
                    generate_move(i, i + 9 * mod, Capture, moves);
                }

                // One step forward
                if (board.board[i + 8 * mod] == Empty) {
                    // TODO: What should we pass in as flag? May be promotion or normal step
                    generate_move(i, i + 8 * mod, Quiet, moves);
                }
                // Two steps forward
                // Only legal if the two squares in front are not occupied and
                // the pawns are at the starting row
                if (board.board[i + 8 * mod] == Empty &&
                    board.board[i + 2 * 8 * mod] == Empty &&
                    ((i >= 48 && is_color(pc, Black)) ||
                     (i <= 15 && is_color(pc, White)))) {
                    generate_move(i, i + 2 * 8 * mod, DoublePawn, moves);
                }
            }
            // Other moves (knights, bishops, rooks, queen, king)
            else {
                // Look at available moves for each piece. Check if it is within
                // bounds
                int piece_type = pc >> 1;
                for (int j = 0; j < num_directions[piece_type];
                     ++j) {             /* for all knight or ray directions */
                    for (int n = i;;) { /* starting with from square */
                        n = mailbox_board[board_map[n] +
                                          offset[piece_type][j]]; /* next square
                                                                     along the
                                                                     ray j */
                        // If the square is inside our board
                        if (n != -1) {
                            if (board.board[n] == Empty) {
                                generate_move(i, n, Quiet, moves);
                            }
                            // If the square we are attacking has opponents
                            // piece
                            if (is_color(board.board[n], opponent_color)) {
                                generate_move(i, n, Capture, moves);
                            }
                        }
                        if (n == -1) break; /* outside board */
                        if (board.board[n] != Empty) {
                            break;
                        }  // Piece is blocking path
                        if (!slide[piece_type]) {
                            break;
                        }
                    }
                }
            }
        }
    }
    // Add castling moves for the current side
    // Note that we do not check whether or not the king or rook has moved -
    // this is checked in Board::make_move.
    if (current_side == White) {
        bool kingSideEmpty =
            board.board[F1] == Empty && board.board[G1] == Empty;
        bool queenSideEmpty = board.board[B1] == Empty &&
                              board.board[C1] == Empty &&
                              board.board[D1] == Empty;
        if (board.get_castling_rights() & wCastleKing && kingSideEmpty) {
            // In order to castle king side, the squares between the king and
            // rook have to be Empty
            generate_move(WHITE_KING_START, G1, KCastle, moves);
        } else if (board.get_castling_rights() & wCastleQueen &&
                   queenSideEmpty) {
            generate_move(WHITE_KING_START, C1, QCastle, moves);
        }
    }  // Black castling
    else {
        bool kingSideEmpty =
            board.board[F8] == Empty && board.board[G8] == Empty;
        bool queenSideEmpty = board.board[B8] == Empty &&
                              board.board[C8] == Empty &&
                              board.board[D8] == Empty;
        if (board.get_castling_rights() & bCastleKing && kingSideEmpty) {
            // In order to castle king side, the squares between the king and
            // rook have to be Empty
            generate_move(BLACK_KING_START, G8, KCastle, moves);
        } else if (board.get_castling_rights() & bCastleQueen &&
                   queenSideEmpty) {
            generate_move(BLACK_KING_START, C1, QCastle, moves);
        }
    }
    return moves;
}

void generate_move(int from, int to, int flags, vector<Move> &available_moves) {
    available_moves.push_back(Move(from, to, flags));
}

bool is_color(Piece piece, Color color) {
    // Since all white pieces are even numbered, and the color white is 0, the
    // following is correct
    return (piece % 2) == color && piece != Empty;
}

void init_board(Piece pieces[]) {
    for (int i = 0; i < 64; i++) {
        piece[i] = pieces[i];
    }
}

void init_board() {
    for (int i = 0; i < 64; i++) {
        piece[i] = init_piece[i];
    }
}
