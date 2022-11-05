#include "assignment7.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    solution x;
    double outcome[40],theory[40];
    double Alice_Probility, Bob_Probability;
    cin >> Alice_Probility;
    cin >> Bob_Probability;
    
//    for
    cout << "Probability of head up for Alice = " << Alice_Probility << endl;
    cout << "Probability of head up for Bob = " << Bob_Probability << endl;
    
    x.set_probability(Alice_Probility, Bob_Probability);
    
    int result = x.result();
    if (result > 0){
        cout << "The optimal number of coin tosses is " << result << endl;
    }
    
    system("pause");
    return 0;
}
