all:
	g++ -g -Wall main.cpp sudoku.cpp -o sudoku
	g++ -g -Wall tester.cpp sudoku.cpp -o tester
