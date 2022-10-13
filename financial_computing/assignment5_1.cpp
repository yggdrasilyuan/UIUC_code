#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;
#define FLAG -1
// Private
int no_of_couples;
vector <vector <int> > Preference_of_men;
vector <vector <int> > Preference_of_women;
vector <int> match_for_men;
vector <int> match_for_women;

   int anybody_free(vector <bool> my_array)
    {  
        int n=my_array.size();
        for(int i=0;i<n;i++){
            if(my_array[i]==true)
                return i;
        }
        return -1;
        // fill the necessary code for this function
    }
    
    // private member function: if index1 is ranked higher than index2
    // in a preference array called "my_array" it returns "true"; otherwise
    // it returns "false"
    bool rank_check (vector <int> my_array, int index1, int index2)
    {
        // fill the necessary code for this function
        my_array
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        vector <vector <bool> > has_this_man_proposed_to_this_woman;
        
        int man_index, perferLady;
        int man_start_index=0;
        
        // initializing everything
        for (int i= 0; i < no_of_couples; i++)
        {
            is_man_free[i]=true;
            is_woman_free[i]=true;
            // do the necessary initialization here
        }
        
        // Gale-Shapley Algorithm
        while ( (man_index = anybody_free(is_man_free)) >= 0)
        {
            // fill the necessary code here
            perferLady=Preference_of_men[man_index][man_start_index];//选择在自己名单上排在首位的女人
            if(is_woman_free[perferLady]==true)//如果该女子没有对象则接受表白
            {
                match_for_men[man_index]=perferLady;
                match_for_women[perferLady]=man_index;
            }else
            {
                
            }
           
        }
    }
// private member function: reads data
void read_data(int argc, const char * argv[])
{
    ifstream input_file("Input1");
    
    if (input_file.is_open())
    {
        input_file >> no_of_couples;
        for (int i = 0; i < no_of_couples; i++)
        {
            Preference_of_men.push_back(vector<int>(no_of_couples));
            for (int j = 0; j < no_of_couples; j++)
            {
                input_file >> Preference_of_men[i][j];
            }
        }
        for (int i = 0; i < no_of_couples; i++)
        {
            Preference_of_women.push_back(vector<int>(no_of_couples));
            for (int j = 0; j < no_of_couples; j++)
            {
                input_file >> Preference_of_women[i][j];
            }
        }
        match_for_men = vector<int>(no_of_couples, -1);
        match_for_women = vector<int>(no_of_couples, -1);
    }
    
}

// private member function: print solution
void print_soln()
{
    // write the appropriate code here
}


void solve_it(int argc, const char * argv[])
{
    read_data(argc, argv);
    
    Gale_Shapley();
    
    print_soln();
}

int main(int argc, const char * argv[])
{
    solve_it(argc, argv);
}


