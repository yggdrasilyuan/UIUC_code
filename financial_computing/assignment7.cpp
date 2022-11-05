#include "assignment7.h"
#include <fstream>
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
    
    ofstream p;
    p.open("output.csv",ios::out|ios::trunc);                //打开文件路径
    p<<"num_game"<<","<<"pratical"<<","<<"theory"<<endl;    //输入内容，注意要用逗号，隔开
    for(int i=0; i<31;i++){
        outcome[i]=x.optimal_number_of_toss(i, 500000);
        cout<<"number of toss "<<i<<" probability:"<<outcome[i]<<endl;
        theory[i]=x.calculate(Alice_Probility,Bob_Probability,i);
        cout<<"----number of toss "<<i<<" probability:"<<theory[i]<<endl;
        p<<i<<","<<outcome[i]<<","<<theory[i]<<endl;
    }
    

    p.close();


    // system("pause");
    return 0;
}
