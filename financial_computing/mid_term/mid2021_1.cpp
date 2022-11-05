#include<iostream>
using namespace std;

void f(string my,int index,string current_string)
{
    long n=my.length();
    if(index==n){
        cout<<"{"<<current_string<<"}"<<endl;
        return;
    }
    f(my,index+1,current_string+my[index]);
    f(my,index+1,current_string);
//理解有没有看懂第一次作业
}

int main(){
    string str="xyz";
    f(str,0,"");
    system("pause");
    return 0;
}