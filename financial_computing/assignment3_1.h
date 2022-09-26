#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include<iostream>
#include <tuple>

using std::vector;
using namespace std;
class Sudoku 
{ 
	// Private
	int puzzle[9][9];
	
    bool Check(int n, int key)//judge row/col/3*3
    {
        for (int i = 0; i < 9; i++)//judge row
        {
            int j = n / 9;//j=row
            if (puzzle[j][i] == key) return false;
        }
    
        for (int i = 0; i < 9; i++)//judge col
        {
            int j = n % 9;//j==col
            if (puzzle[i][j] == key) return false;
        }
        /* x为n所在的小九宫格左顶点竖坐标 */
        int x = (n / 9) / 3 * 3;
        /* y为n所在的小九宫格左顶点横坐标 */
        int y = (n % 9) / 3 * 3;
        /* 判断n所在的小九宫格是否合法 */
        for (int i = x; i < x + 3; i++)
        {
            for (int j = y; j < y + 3; j++)
            {
                if (puzzle[i][j] == key) return false;
            }
        }
        return true;
    }

    bool check_diagonals_valid(){
        int count1=0;
        int count2=0;
        for(int i=0;i<9;i++)
        {
            count1=count1+puzzle[i][i];
            count2=count2+puzzle[i][8-i];
        }
        if(count1==45&&count2==45)
            return true;
        else
            return false;
    }
    
    
    // Private member function that checks if the positive-diagonal
    // (SW to NE diagonals) have no repeated digits. If the initial
    // partially-filled puzzle does not meet this requirement, I need
    // to flag this (see write-up). I am using tuples for this. This
    // way I can show which value is repeated along the diagonal multiple times
    // I took this from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
    
    std::tuple<bool, int> positive_diagonals_valid()
    {
        // write code that checks if there are any repeated
        // digits along the 15-many positive diagonals
        // If the intial puzzle does not meet this requirement,
        // I want to let the user know that digit X has appeared
        // multiple times along some positive diagonal (in the
        // partially-filled input puzzle). This way the user can
        // see the reason why there can be no solution to the
        // Dutch Miracle Sudoku puzzle instance.
        //
        // In my implementation, if the returned bool variable is false,
        // then the second-tuple is the X that was repeated along
        // some positive diagonal (see description of assignment
        // for a sample output).
    }
    
    // Private member funtion that checks if adjacent cells
    // (along the positive diagonal) touching at a corner
    // have a difference of atleast 4
    std::tuple<bool, int, int> adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4()
    {
        // write code that checks if all non-zero entries in the
        // puzzle (filled so far) have met the "minimum-difference
        // of 4" rule.
        //
        // In my implementation, if the returned bool variable is false,
        // then the two ints (i and j, say) identify puzzle[i][j] and
        // puzzle[i-1][j+1] that do not meet the "minimum-difference
        // of 4" (see program assignment description for a sample output)
    }
    
	
public:
	// Public member function that reads the incomplete puzzle
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid

    bool flag=false;
    int count=0;
    void read_puzzle(int argc, char * const argv[])
    {   
        int data;
        int flag=0;
        ifstream input_file(argv[1]);
        if(input_file.is_open()){
            while(input_file>>data){
                puzzle[flag/9][flag%9]=data;
                flag++;
            }
        }
        
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
    }
	
	// Public member function that prints the puzzle when called
	void print_puzzle()
	{
		//cout << number_of_calls << endl;
		cout << endl << "Board Position" << endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					cout << "0 ";
				}
			}
			cout << endl;
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
        int n= 9*row+col;
  
        int nextrow=(n+1)/9; int nextcol=(n+1)%9;
        if(n>80){
            flag=true;
            count++;
            // print_puzzle();
            return true;
        }
        if(puzzle[n/9][n%9]!=0){
            Solve(nextrow,nextcol);
        }
        else{
            for(int k=1; k<=9; k++){
                if(Check(n,k)==true)
                {
                    puzzle[n/9][n%9]=k;
                    Solve(nextrow,nextcol);
                    if(flag==true){
                        print_puzzle();
                        count++;
                        cout<<"number:"<<count<<endl;
                        return true;
                    }else
                    puzzle[n/9][n%9]=0;
                }
            }
        }

        // use the pseudo code of figure 3 of the description
    }
};

#endif
