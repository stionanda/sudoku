#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

int count_global=0;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */
bool is_complete(char board[9][9]) {
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (board[i][j] == '.') return false;
    }
  }
  return true;
}

bool make_move(string position, char digit, char board[9][9]) {
  int r = position[0] - 'A', c = position[1] - '1';
  if (r < 0 || r >= 9 || c < 0 || c >=9) return false;
  
  if (board[r][c] == digit) return true;

  for (int i=0; i<9; i++) {
    if (board[r][i] == digit || board[i][c] == digit) return false;
  }

  int nr = r / 3 * 3, nc = c / 3 * 3;

  for (int j=nr; j< nr + 3; j++) { 
    for (int k=nc; k< nc + 3; k++) {
      if (board[j][k] == digit) return false;
    }
  }
  
  board[r][c] = digit;
  return true;

}

bool save_board(const char* filename, char board[9][9]) {
  ofstream out(filename);
  if(!out) return false;

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++){
      out << board[i][j];
    }
    out << endl;
  }
  return true;
}

bool solve_board(int r, int c, char board[9][9]) {
  
  count_global++;

  if (r == 9) return true;
  int nr = c == 8 ? r + 1: r;
  int nc = (c+1)%9;

  string s;
  s.push_back(r + 'A');
  s.push_back(c + '1');

  if (board[r][c]!='.') return solve_board(nr,nc,board);
  
  for (int i=1; i<=9; i++) {
    if (make_move(s,i+'0',board) && solve_board(nr,nc,board)) return true;
  }
  board[r][c] = '.';
  return false;
}

bool solve_board(char board[9][9]) {
  return solve_board(0, 0, board);
}

