//
//  main.cpp
//  hw3
//
//  Created by Shuxiang Lei on 2022/9/19.
//



#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include"Header.h"
using namespace std;

int main (int argc, char * const argv[])
{
    Sudoku x;
    x.read_puzzle(argc, argv);
    x.print_puzzle();
    x.Solve(0,0);
    x.print_puzzle();
    
    return 0;
}
