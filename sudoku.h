#include <cstring>

using namespace std;

extern int count_global;
void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(char board[9][9]);
bool make_move(string position, char digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);
bool solve_board(char board[9][9]);
