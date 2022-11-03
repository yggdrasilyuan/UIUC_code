
#ifndef Header_h
#define Header_h


#endif /* Header_h */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <random>
#include <cmath>

using namespace std;

class solution
{
    double Alice_Probility, Bob_Probability;
    
    double get_uniform()
    {
        return (((float)rand()) / (pow(2.0, 31.0) - 1));
    }
    
    int take(int n, int k)
    {
        if (k == 0)
            return 1;
        else if (k == 1)
            return n;
        else
            return take(n, k - 1)*(n - k + 1) / k;
    }
    
    
public:
    double calculate(double q, double p, int n)
        {
            double aliceprob = 0;
            for (int r = 0; r < n; r++)
            {
                for (int b = r + 1; b <= n; b++)
                {
                    aliceprob = aliceprob + take(n, r)*pow(p, r)*pow(1 - p, n - r)*take(n, b)*pow(q, b)*pow(1 - q, n - b);
                }
            }
            return aliceprob;
        }
    void set_probability(double alice_probility, double bob_probility)
    {
        Alice_Probility = alice_probility;
        Bob_Probability = bob_probility;
    }
    
    double optimal_number_of_toss(int number_of_tosses, int number_of_game)
    {
        binomial_distribution<int> dist1(number_of_tosses, Alice_Probility);
        binomial_distribution<int> dist2(number_of_tosses, Bob_Probability);
        default_random_engine generator1(19260817);
        default_random_engine generator2(7);
        
        int Win_For_Alice = 0;
        for(int i = 0; i < number_of_game; i++)
        {
            if (dist1(generator1) > dist2(generator2)) Win_For_Alice++;
        }
        return (((double)Win_For_Alice) / ((double)number_of_game));

    }
    
    int result()
    {
        int n = 1;
        double a1 = calculate(Alice_Probility, Bob_Probability, n);
        double a2 = calculate(Alice_Probility, Bob_Probability, n + 1);
        while (a2 > a1)
        {
            n++;
            a1 = calculate(Alice_Probility, Bob_Probability, n);
            a2 = calculate(Alice_Probility, Bob_Probability, n + 1);
        }
        return n;
    }
    
};
