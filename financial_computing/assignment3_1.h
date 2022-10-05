#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include<iostream>
#include <tuple>
#include <cstring>

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
        int x = (n / 9) / 3 * 3;//This is the start row number of 3*3 puzzle
        int y = (n % 9) / 3 * 3;//this is the col number
        for (int i = x; i < x + 3; i++)//check 3*3 puzzle
        {
            for (int j = y; j < y + 3; j++)
            {
                if (puzzle[i][j] == key) return false;
            }
        }
        return true;
    }

    bool check_diagonals_valid(int row,int col){
        static bool vis[16];
        int diaID = row + col;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<9;i++){
            int x = i,y = diaID-i;
            if(y < 0 || y >= 9)continue;
            int c = puzzle[x][y];
            if(c == 0)continue;
            // cout << x << " " << y << ": " << c << endl;
            if(vis[c])return false;
            vis[c] = 1;
        }
        return true;
    }
    
    
    // Private member function that checks if the positive-diagonal
    // (SW to NE diagonals) have no repeated digits. If the initial
    // partially-filled puzzle does not meet this requirement, I need
    // to flag this (see write-up). I am using tuples for this. This
    // way I can show which value is repeated along the diagonal multiple times
    // I took this from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
    
    std::tuple<bool, int> positive_diagonals_valid()
    {
        static bool vis[16];
        for(int dia=0;dia<=16;dia++){
            memset(vis,0,sizeof(vis));
            for(int i=0;i<9;i++){
                int x = i,y = dia-i;
                if(y < 0 || y >= 9)continue;
                int c = puzzle[x][y];
                if(c == 0)continue;
                if(vis[c])return make_tuple(false,c);
                vis[c] = 1;
            }
        }

        return make_tuple(true, -1);
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
    std::tuple<bool, int, int> adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4(int i,int j)
    {
        // if(cddCheck()){
        //     cout << "!! adjacent_cells" << endl;
        //     cout << i << " " << j <<": " << puzzle[i][j]<< endl;
        //     cout << i-1 << " " << j+1 <<": " << puzzle[i-1][j+1]<< endl;
        //     cout << "res: " << abs(puzzle[i-1][j+1]-puzzle[i][j]) << endl;
        // }
        // return make_tuple(true,-1,-1);
        if(i-1 < 0 || j+1 >= 9)
            return make_tuple(true,-1,-1);
        // cout << puzzle[i-1][j+1] << " " << puzzle[i][j] << endl;
        if(abs(puzzle[i-1][j+1]-puzzle[i][j])<=3){
            // if(cddCheck())cout << "*" << puzzle[i-1][j+1] << " " << puzzle[i][j] << " " << abs(puzzle[i-1][j+1]-puzzle[i][j]) << endl;
            return make_tuple(false,i,j);
        }
        else return make_tuple(true,-1,-1);
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
					cout << "x ";
				}
			}
			cout << endl;
		}
	}
    // bool cddCheck(){
    //     if(puzzle[0][0] != 5)return 0;
    //     if(puzzle[0][1] != 6)return 0;
    //     if(puzzle[0][2] != 3)return 0;
    //     if(puzzle[0][3] != 9)return 0;
    //     if(puzzle[0][4] != 1)return 0;
    //     if(puzzle[0][5] != 4)return 0;
    //     if(puzzle[0][6] != 7)return 0;
    //     if(puzzle[0][7] != 8)return 0;
    //     if(puzzle[0][8] != 2)return 0;
    //     if(puzzle[1][0] != 1)return 0;
    //     // cout << "->" << puzzle[1][0] << endl;
    //     // if(puzzle[1][0] != 3)return 0;
    //     // if(puzzle[1][1] != 9)return 0;
    //     return 1;
    // }
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    void init_check_diagonals(){
        if(!get<0>(positive_diagonals_valid())){
            cout<<"Partially-Filled Sudoku Puzzle does not meet Dutch Miracle requirements...Quiting!"<<endl;
            cout<<"The number "<<get<1>(positive_diagonals_valid())<<" appears multiple times along the positive diagonals."<<endl;
        }
        
    }
    void init_check_min(){
        for(int i=0;i<81;i++){
            if(!get<0>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4(i/9,i%9))&&puzzle[i/9][i%9]!=0&&puzzle[i/9-1][i%9+1]!=0){
                cout<<"puzzle["<<i/9<<"]["<<i%9<<"]= "<<puzzle[i/9][i%9]<<" ,puzzle["
                <<i/9-1<<"]["<<i%9+1<<"]= "<<puzzle[i/9-1][i%9+1]<<" , and they do not meet the minimum-difference of 4"<<endl;
                break;
            }
        }
    }

    bool Solve(int row, int col)
    {

        // if(cddCheck())print_puzzle();
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col- and block-valid...
        int n= 9*row+col;
  
        int nextrow=(n+1)/9; int nextcol=(n+1)%9;
        if(n>80){
            count++;
            // cout<<"Solution #"<<count;
            if(count==1){
                print_puzzle();
                cout<<endl;
            }
            return true;
        }
        if(puzzle[n/9][n%9]!=0){
            Solve(nextrow,nextcol);

            // if(get<0>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4(row,col)) && check_diagonals_valid(row,col)){
                
            //     int tmp = puzzle[row][col];
            //     puzzle[row][col] = 0;
            //     if(Check(n,tmp) == true){
            //         cout << row << " " << col << " check ok" << endl;
            //         puzzle[row][col] = tmp;
            //         Solve(nextrow,nextcol);
            //     }
            //     else{
            //         cout << row << " " << col << " check bad" << endl;
            //     }
            // }
            // else{
            //     cout << row << " " << col << " bad" << endl;
            //     print_puzzle();
            // } 
        }
        else{
            // cout << "!!!" << row << " " << col << endl;
            for(int k=1; k<=9; k++){
                if(Check(n,k)==true){
                    // if(cddCheck())cout << "->" << k << endl;
                    puzzle[n/9][n%9]=k;
                    if(check_diagonals_valid(row,col) && 
                        get<0>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4(row,col)))
                        {   
                            // if(cddCheck())cout << "-->" << k << endl;
                            Solve(nextrow,nextcol);
                        }
                    puzzle[n/9][n%9]=0;
                }
            }
                
        }

        // use the pseudo code of figure 3 of the description
    }
};

#endif
