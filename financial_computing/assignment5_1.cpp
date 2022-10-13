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

class  stable_marriage_instance
{
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
    bool rank_check (int num, int index1, int index2)
    {
        // fill the necessary code for this function
        int before = 0, now = 0;
        for (int i = 0; i < no_of_couples; i++)
        {
            if (Preference_of_women[num][i] == index1)
            {
                before = i;
            }
            if (Preference_of_women[num][i] == index2)
            {
                now = i;
            }
        }
        if (before < now)
            return false;
        else
            return true;
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        
        int man_index;
        // cout<<"<--"<<endl;
        int man_start_index[no_of_couples];
        // cout<<"true"<<endl;
        
        // initializing everything
        is_man_free=vector<bool>(no_of_couples, true);
        is_woman_free=vector<bool>(no_of_couples, true);
        for (int i= 0; i < no_of_couples; i++)
        {
            man_start_index[i]=0;
            // do the necessary initialization here
        }
        // cout<<"here"<<endl;
        // Gale-Shapley Algorithm
        while ( (man_index = anybody_free(is_man_free)) >= 0)
        {
            for (int i = 0; i < no_of_couples; i++)
            {
                if (is_man_free[i] == true)
                {
                    int man_choice = Preference_of_men[i][man_start_index[i]];
                    int man_choice_bf = match_for_women[man_choice];
                    if (man_choice_bf != -1)
                    {
                        if (rank_check(man_choice, man_choice_bf, i))
                        {
                            match_for_men[man_choice_bf] = -1;
                            match_for_men[i] = man_choice;
                            match_for_women[man_choice] = i;
                            is_man_free[i] = false;
                            is_man_free[man_choice_bf] = true;
                        }
                    }
                    else
                    {
                        match_for_men[i] = man_choice;
                        match_for_women[man_choice] = i;
                        is_man_free[i] = false;
                    }
                    man_start_index[i]++;
                }
            }
        }
    }
    // private member function: reads data
    void read_data(int argc, const char * argv[])
    {
        ifstream input_file(argv[1]);
        
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

            cout << "Number of couples = " << no_of_couples << endl;
            cout << "Preferences of Men" << endl << "------------------" << endl;
            for (int i = 0; i < no_of_couples; i++)
            {
                cout << "(" << i << "): ";
                for (int j = 0; j < no_of_couples; j++)
                {
                    cout << Preference_of_men[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cout << "Preferences of Women" << endl << "---------------------" << endl;
            for (int i = 0; i < no_of_couples; i++)
            {
                cout << "(" << i << "): ";
                for (int j = 0; j < no_of_couples; j++)
                {
                    cout << Preference_of_women[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        else{
            cout<<"false"<<endl;
        }
        
    }

    // private member function: print solution
    void print_soln()
    {
        // write the appropriate code here
        cout << "Matching for Men" << endl;
        for (int i = 0; i < no_of_couples; i++)
        {
            cout << "Man: " << i << " -> " << "Woman: " << match_for_men[i] << endl;
        }
        cout << endl;
        cout << "Matching for Women" << endl;
        for (int i = 0; i < no_of_couples; i++)
        {
            cout << "Woman: " << i << " -> " << "Man: " << match_for_women[i] << endl;
        }
        cout << endl;
    }

public:
    void solve_it(int argc, const char * argv[])
    {
        read_data(argc, argv);
        // cout<<"read"<<endl;
        
        Gale_Shapley();
        
        print_soln();
    }
};

int main(int argc, const char * argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
    system("pause");
    return 0;
}


