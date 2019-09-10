#include "move.hpp"
#include <exception>

Move::Move() { move = 0; }

Move::Move(unsigned int from, unsigned int to, unsigned int flags) {
    move =
        (from & 0b111111) | ((to & 0b111111) << 6) | ((flags & 0b111111) << 12);
}

Move::Move(string move_string) {
    // Assume every move is on the form e2e4 or g1f3
    if (move_string.length() < 4) {
        std::cout << "info Could not parse move string\n";
    }
    string from_square = move_string.substr(0, 2);
    string to_square = move_string.substr(2, 4);
    int from = square_to_board_index(from_square);
    int to = square_to_board_index(to_square);
    // TODO: Parse promotions
    int flags = 0;
    move =
        (from & 0b111111) | ((to & 0b111111) << 6) | ((flags & 0b111111) << 12);
}

unsigned int Move::from_square() { return move & 0b111111; }

unsigned int Move::to_square() { return (move >> 6) & 0b111111; }

unsigned int Move::get_flags() { return (move >> 12) & 0b111111; }

bool Move::is_capture() { return get_flags() == Capture; }
bool Move::is_promotion() { return get_flags() & 0b1000; }

string Move::uci() {
    // TODO: Include captures/promotions
    return board_index_to_square(from_square()) +
           board_index_to_square(to_square());
}

string Move::toString() {
    return "From: " + std::to_string(from_square()) +
           ", To: " + std::to_string(to_square()) +
           ", Flags: " + std::to_string(get_flags());
}

string board_index_to_square(int index);

char get_promotion_suffix(unsigned int flags){
    if(flags == KnightPromo || flags == KnightPromoCapture){
        return 'N';
    }
    if(flags == QueenPromo || flags == QueenPromoCapture){
        return 'Q';
    }
    if(flags == RookPromo || flags == RookPromoCapture){
        return 'R';
    }
    if(flags == BishopPromo || flags == BishopPromoCapture){
        return 'B';
    }
    return ' ';

}

string Move::toAlgebraic() {
    string modifier = "";

    if (is_capture()) {
        modifier = "x";
    }
    string promotion_suffix = "";
    if(is_promotion()){
        promotion_suffix = get_promotion_suffix(get_flags());
    }
    return board_index_to_square(from_square()) +
           board_index_to_square(to_square()) + promotion_suffix;
}

