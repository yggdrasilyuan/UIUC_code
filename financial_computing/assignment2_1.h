#ifndef N_queens
#define N_queens
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Board
{
	
	// private data member: size of the board
	int size;
    
    // pointer-to-pointer initialization of the board
	vector<vector<char> >* chess_board;

	// private member function:  returns 'false' if
	// the (row, col) position is not safe.
	bool is_this_position_safe(vector<vector<char>> chess_boadrd, int x, int y)//x=row y=column
	{
		// write the appropriate code on your own that returns
		// "true" if the (row,col) position is safe.  If it is 
		// unsafe (i.e. some other queen can threaten this position)
		// return "false"'
        for(int i=0;i<=x;i++){
            for(int j=0;j<chess_boadrd[0].size();j++){
                if(chess_boadrd[i][j]=='Q'&&(j==y||abs(x-i)==abs(y-j))){
                    return false;
                }
            }
        }
        return true;
		
	}
	
	// private member function: initializes the (n x n) chessboard 
	void initialize(int n)
	{
		size = n; 
		chess_board = new vector<vector<char>>(n,vector<char>(n,0));
        
		// write the appropriate code that uses the pointer-to-pointer 
		// method to initialize the (n x n) chessboard.  Once initialized,
		// put zeros in all entries.  Later on, if you placed a queen in
		// the (i,j)-th position, then chessboard[i][j] will be 1.  
	}
	
	// private member function: prints the board position
	void print_board()
	{
        cout << size << "-Queens Problem Solution" << endl;
		// write the appropriate code here to print out the solved 
		// board as shown in the assignment description

	}
	
	// private member function: recursive backtracking
	bool solve(int col)
	{
		// implement the recursive backtracking procedure described in 
		// pseudocode format in figure 1 of the description of the first
		// programming assignment
	}
	
public:
	// Solves the n-Queens problem by (recursive) backtracking
    int chess_size;
	void nQueens(int n)
	{
		initialize(n);
		// chess_size
		if (solve(0))
			print_board();
		else 
			cout << "There is no solution to the " << n << "-Queens Problem" << endl;
	}
};
#endif