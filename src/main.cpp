#include "board.hpp"
#include "uci.hpp"
#include "utils.hpp"

int main() {
    Board board = Board();
    uci_loop(board);
    return 0;
}
