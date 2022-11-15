#include<bits/stdc++.h>
using namespace std;

int main(){
    string credit_card;
    cout << "enter the identification number" << endl;
    cin >> credit_card;
    int digits;
    digits=credit_card.size();
    int Acc_num[digits];
    int shuma = 0;
    

    // store the digits
    for (int i = 0 ; i < digits ; i ++ ) {
        Acc_num[digits-1-i] = credit_card[i]-48;//change string to number
    }

    // Double every other
    for (int i = 1 ; i <=digits ; i ++) {
        if (i % 2 == 0) {
            Acc_num[i-1] =  2 * Acc_num[i-1];
        } else {
            Acc_num[i-1] = Acc_num [i-1];
        }
    }

    //Sum digits
    for (int i = 1 ; i <= digits ; i ++ ) {
        if (Acc_num[i-1] > 9 && i % 2 == 0) {
            int mod = Acc_num[i-1] % 10 ;
            Acc_num[i-1]  =  1 + mod ;
        } else {
        Acc_num[i-1] = Acc_num[i-1];
        }
    }

    // the sum
    for (int i = 0 ; i <= (digits - 1) ; i ++ ) {
        shuma += Acc_num[i];
    }
    cout<<endl<<shuma<<endl;
    // if (shuma % 10 == 0) {
    //     cout << "\nthis number is valid" << endl;
    // } else {
    //     cout << "\nthis number is invalid" << endl;
    // }
    system("pause");
    return 0;
}