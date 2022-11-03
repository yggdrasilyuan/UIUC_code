#include<iostream>
using namespace std;
long gcd(long m, long n){
    if(m==n )return n;
    else if(m<n) return gcd(m,n-m);
    else return gcd(m-n,n);
}
int main()
{
    cout<<gcd(7,4)<<endl;
    system("pause");
}