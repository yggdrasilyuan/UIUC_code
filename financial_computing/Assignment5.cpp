#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class stable_marriage_instance
{

    int no_of_couples = 0;
    int Preference_of_men[10][10];
    int Preference_of_women[10][10];
    int match_for_men[10];
    int match_for_women[10];

    int anybody_free(bool my_array[10])
    {
        for (int i = 0; i < no_of_couples; i++)
        {
            if (my_array[i] == true)
            {
                return i;
            }
        }
        return -1;
    }

    bool rank_check(int num, int index1, int index2)
    {
        int rank_of_current = 0, rank_of_chasing = 0;
        for (int i = 0; i < no_of_couples; i++)
        {
            if (Preference_of_women[num][i] == index1)
            {
                rank_of_current = i;
            }
            if (Preference_of_women[num][i] == index2)
            {
                rank_of_chasing = i;
            }
        }
        if (rank_of_current < rank_of_chasing)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void Gale_Shapley()
    {
        bool is_man_free[10];
        int boy_most_love[10];

        for (int i = 0; i < no_of_couples; i++)
        {
            is_man_free[i] = true;
            match_for_men[i] = -1;
            match_for_women[i] = -1;
            boy_most_love[i] = 0;
        }

        while ((anybody_free(is_man_free)) >= 0)
        {
            for (int i = 0; i < no_of_couples; i++)
            {
                if (is_man_free[i] == true)
                {
                    int boy_chase = Preference_of_men[i][boy_most_love[i]];
                    int boy_chase_bf = match_for_women[boy_chase];
                    if (boy_chase_bf != -1)
                    {
                        if (rank_check(boy_chase, boy_chase_bf, i))
                        {
                            match_for_men[boy_chase_bf] = -1;
                            match_for_men[i] = boy_chase;
                            match_for_women[boy_chase] = i;
                            is_man_free[i] = false;
                            is_man_free[boy_chase_bf] = true;
                        }
                    }
                    else
                    {
                        match_for_men[i] = boy_chase;
                        match_for_women[boy_chase] = i;
                        is_man_free[i] = false;
                    }
                    boy_most_love[i]++;
                }
            }

        }
    }

    void read_data(int argc, const char* argv[])
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                Preference_of_men[i][j] = 0;
                Preference_of_women[i][j] = 0;
            }
        }
        int value_just_read_from_file;
        vector <int> P;
        ifstream input_file("input");
        if (input_file.is_open())
        {
            while (input_file >> value_just_read_from_file)
            {
                P.push_back(value_just_read_from_file);
            }
        }
        no_of_couples = P[0];
        int number = P[0];
        for (int i = 0; i < (number * number); i++)
        {
            Preference_of_men[i / number][i % number] = P[i + 1];
        }
        for (int i = 0; i < (number * number); i++)
        {
            Preference_of_women[i / number][i % number] = P[i + 1 + (number * number)];
        }
        cout << "Number of couples = " << P[0] << endl;
        cout << "Preferences of Men" << endl << "------------------" << endl;
        for (int i = 0; i < P[0]; i++)
        {
            cout << "(" << i << "): ";
            for (int j = 0; j < P[0]; j++)
            {
                cout << Preference_of_men[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Preferences of Women" << endl << "---------------------" << endl;
        for (int i = 0; i < P[0]; i++)
        {
            cout << "(" << i << "): ";
            for (int j = 0; j < P[0]; j++)
            {
                cout << Preference_of_women[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void print_soln()
    {
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
    void solve_it(int argc, const char* argv[])
    {
        read_data(argc, argv);

        Gale_Shapley();

        print_soln();
    }
};

int main(int argc, const char* argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
}
