#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main(int argc, char* argv[]) {

  char board[9][9];

  cout << "=================== Tester ===================" << "\n\n";

  load_board(argv[1], board);
  if (solve_board(board)) {
    cout << "The board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  cout << "function calls : " << count_global << endl;

}
