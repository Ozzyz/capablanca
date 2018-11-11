#include "utils.hpp"

void print_piece(Piece piece);
using namespace std;


void print_board(Piece board[64]) {
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0) {

            cout << '\n'<< string(40, '_') << '\n';
        }
        Piece pc = (Piece)board[i];
        if (pc == Empty) {
            cout << "  ";
        }else{
            print_piece(pc);
        }
        cout << "|  ";
    }
    cout << endl;
}
const wchar_t* unicode_pieces[12] = { L"\u265F" ,L"\u2659" ,
    L"\u265E" ,L"\u2658" , L"\u265D" ,L"\u2657" ,L"\u265C" , L"\u2656" ,
    L"\u265B" ,L"\u2655" , L"\u265A" ,L"\u2654" };

const wchar_t* char_pieces[13] = { L"wP", L"bP",
    L"wKn", L"bKn",
    L"wB", L"bB",
    L"wR", L"bR",
    L"wQ", L"bQ",
    L"wK", L"bK",L"  "};

void print_piece(Piece pc) {
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //SetConsoleOutputCP(65001);
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //DWORD written = 0;
    // explicitly call the wide version (which always accepts UTF-16)
    std::wcout << char_pieces[pc];
}

int square_to_board_index(string square) {
    if (square.length() != 2) {
        throw std::invalid_argument("Cant convert - Illegal square!");
    }
    string files = "hgfedcba";
    string ranks = "12345678";
    char file = square[0];
    char rank = square[1];
    return (int)files.find_first_of(file) + ranks.find_first_of(rank) * 8;
}

string board_index_to_square(int index) {
    string files = "hgfedcba";
    string ranks = "12345678";
    char file = files.at(COL(index));
    char rank = ranks.at(ROW(index));
    return std::string{ file,rank };
}


