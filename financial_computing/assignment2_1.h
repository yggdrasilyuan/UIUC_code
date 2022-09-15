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
	bool is_this_position_safe(vector<vector<char>> &chess_board, int x, int y)//x=row y=column
	{
		// write the appropriate code on your own that returns
		// "true" if the (row,col) position is safe.  If it is 
		// unsafe (i.e. some other queen can threaten this position)
		// return "false"'
        for(int j=0;j<=y;j++){
            for(int i=0;i<chess_board[0].size();i++){
                if(chess_board[i][j]=='Q'&&(i==x||abs(x-i)==abs(y-j))){
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
		chess_board = new vector<vector<char>>(n,vector<char>(n,'-'));
        
		// write the appropriate code that uses the pointer-to-pointer 
		// method to initialize the (n x n) chessboard.  Once initialized,
		// put zeros in all entries.  Later on, if you placed a queen in
		// the (i,j)-th position, then chessboard[i][j] will be 1.  
	}
	
	// private member function: prints the board position
	void print_board(vector<vector<char> > &chess_board,int col,int n)
	{
		// write the appropriate code here to print out the solved 
		// board as shown in the assignment description
		
		//每列都摆满皇后时，则产生了一种解法
        if(col==n){
            // res.add(chsToList(chs));
			
			for(int i=0;i<n;i++){
				cout<<"   ";
				for(int j=0;j<n;j++){
					
					cout<<chess_board[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;cout<<endl;
            return;
        }
        //一列一列地摆放，在确定一列中的那个皇后应该摆在哪一列时，需要当前列是否合法。
        //如果合法，则将皇后放置在当前位置，并进行递归，回溯。
        for(int row=0;row<chess_board[0].size();row++){
            if(is_this_position_safe(chess_board,row,col)){
                chess_board[row][col]='Q';
                //递归
                print_board(chess_board,col+1,n);
                //回溯
                chess_board[row][col]='-';
            }
        }

	}

	
	// private member function: recursive backtracking
	// bool solve(int col)
	// {
	// 	// implement the recursive backtracking procedure described in 
	// 	// pseudocode format in figure 1 of the description of the first
	// 	// programming assignment
		
	// }
	
public:
	// Solves the n-Queens problem by (recursive) backtracking
    int chess_size;

	void nQueens(int n)
	{
		initialize(n);
		// chess_size
		if (n>3){
			cout << size << "-Queens Problem Solution" << endl;
			for(int flag=0; flag<n;flag++){
			cout<<"-----";
			}
			cout<<endl;
			print_board(*chess_board,0,n);
			for(int flag=0; flag<n;flag++){
			cout<<"-----";
			}
			cout<<endl;
		}else 
			cout << "There is no solution to the " << n << "-Queens Problem" << endl;
	}
};
#endif