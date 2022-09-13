#include <iostream>
#include <bits/stdc++.h>
#include "assignment2_1.h"
using namespace std;
int main (int argc, char * const argv[]) 
{
    cout<<"boardsize: ";

    Board x;
    
    int board_size;
    cin>>board_size;
    sscanf (argv[1], "%d", &board_size);
	
	x.nQueens(board_size);
	system("pause");
    return 0;
}