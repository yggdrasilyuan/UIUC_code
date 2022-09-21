#include <iostream>
#include "assignment3_1.h"

int main (int argc, char * const argv[]) 
{
	Sudoku x;
	x.read_puzzle(argc, argv);

	x.print_puzzle();
	x.Solve(0,0);
	x.print_puzzle();

	system("pause");
    return 0;
}