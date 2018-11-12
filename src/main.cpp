#include "board.hpp"
#include "utils.hpp"
#include "uci.hpp"


int main(){
    Board board = Board();
    uci_loop(board);
    return 0;
}
