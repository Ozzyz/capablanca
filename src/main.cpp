#include "board/board.hpp"
#include "communication/uci.hpp"

int main() {
    Board board = Board();
    uci_loop(board);
    return 0;
}
