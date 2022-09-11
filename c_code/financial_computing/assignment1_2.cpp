#include<bits/stdc++.h>
using namespace std;
int main(){
    cout<<"Array Size?";
    int n;cin>>n;
    for(int s=0;s<(1<<n);s++){
        cout<<"{ ";
        for(int i=0;i<n;i++)
            if(s&(1<<i))
                cout << i+1 << " ";
        cout <<"}"<< endl;      
    }
    system("pause");
    return 0;
}