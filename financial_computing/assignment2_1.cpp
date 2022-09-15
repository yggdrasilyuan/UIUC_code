#include <iostream>
#include "assignment2_1.h"
#include<bits/stdc++.h>
#include<String>
using namespace std;



int main (int argc, char * const argv[]) 
{
    Board x;
    
    int board_size;
    cout<<"board size: ";
    cin>>board_size;
    // sscanf (argv[1], "%d", &board_size);// 传参

	x.nQueens(board_size);
	system("pause");
    return 0;
}