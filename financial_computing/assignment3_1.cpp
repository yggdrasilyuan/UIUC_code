#include <iostream>
#include "assignment3_1.h"
using namespace std;

int main (int argc, char * argv[]) 
{
	Sudoku x;

	x.read_puzzle(argc, argv);
	

	x.print_puzzle();
	cout<<endl<<endl;
	x.init_check_diagonals();
	// cout<<"->"<<endl;
	x.init_check_min();
	// cout<<"-->"<<endl;
	x.Solve(0,0);
	// cout<<"total count="<<x.count<<endl;
	
	// x.print_puzzle();

	system("pause");
    return 0;
}