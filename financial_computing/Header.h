//
//  Header.h
//  hw3
//
//  Created by Shuxiang Lei on 2022/9/19.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
    // Private
    int puzzle[9][9];
    int count = 0;
    
    bool row_valid(int row, int col)
    {
        for(int i = 0; i < 9; i++)
        {
            if(i != row)
            {
                if(puzzle[row][col]==puzzle[i][col])
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int row, int col)
    {
        for(int i = 0; i < 9; i++)
        {
            if(i != col)
            {
                if(puzzle[row][col] == puzzle[row][i])
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int newrow, int newcol)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (puzzle[row + newrow][col + newcol] == puzzle[newrow][newcol])
                    return true;
            }
        }
        return false;
    }
    
    
    // Private member function that checks if the positive-diagonal
    // (SW to NE diagonals) have no repeated digits. If the initial
    // partially-filled puzzle does not meet this requirement, I need
    // to flag this (see write-up). I am using tuples for this. This
    // way I can show which value is repeated along the diagonal multiple times
    // I took this from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
    
//    std::tuple<bool, int> positive_diagonals_valid()
//    {
//        // write code that checks if there are any repeated
//        // digits along the 15-many positive diagonals
//        // If the intial puzzle does not meet this requirement,
//        // I want to let the user know that digit X has appeared
//        // multiple times along some positive diagonal (in the
//        // partially-filled input puzzle). This way the user can
//        // see the reason why there can be no solution to the
//        // Dutch Miracle Sudoku puzzle instance.
//        //
//        // In my implementation, if the returned bool variable is false,
//        // then the second-tuple is the X that was repeated along
//        // some positive diagonal (see description of assignment
//        // for a sample output).
//
//    }
//
//    // Private member funtion that checks if adjacent cells
//    // (along the positive diagonal) touching at a corner
//    // have a difference of atleast 4
//    std::tuple<bool, int, int> adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4()
//    {
//        // write code that checks if all non-zero entries in the
//        // puzzle (filled so far) have met the "minimum-difference
//        // of 4" rule.
//        //
//        // In my implementation, if the returned bool variable is false,
//        // then the two ints (i and j, say) identify puzzle[i][j] and
//        // puzzle[i-1][j+1] that do not meet the "minimum-difference
//        // of 4" (see program assignment description for a sample output)
//
//    }
    
    
public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
        double value_just_read_from_file;
        vector <double> P;
        ifstream input_file("input1.txt");
        if (input_file.is_open())
        {
            while(input_file >> value_just_read_from_file)
            {
                P.push_back(value_just_read_from_file);
            }
            
        }
        cout <<"Vector P has " <<P.size() << " entries, and they are: " <<endl ;
        for(int i = 0;i < P.size(); i++)
        {
            for(int j = 0;j < P.size(); j++)
            {
                puzzle[i][j]=P[9*i+j];
            }
        }
        
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        //std::cout << number_of_calls << std::endl;
        std::cout << std::endl << "Board Position" << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    bool Solve(int row, int col)
    {
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col- and block-valid...
        // use the pseudo code of figure 3 of the description
        int zero = 0;
        
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(puzzle[i][j] == 0)
                {
                    zero += 1;
                }
            }
        }
        if(zero==0)
        {
            count += 1;
            print_puzzle();
            return true;
        }
        else
        {
            for(int i = 0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    if(puzzle[i][j] == 0)
                    {
                        for(int k = 1; k < 10; k++)
                        {
                            puzzle[i][j] = k;
                            if(row_valid(i,j) && col_valid(i,j) && block_valid(i, j))
                            {
                                if(Solve(i, j) == 0)
                                {
                                    puzzle[i][j]=0;
                                }
                            }
                        }
                        puzzle[i][j] = 0;
                        return false;
                    }
                }
            }
        }
        return false;
    }
};
