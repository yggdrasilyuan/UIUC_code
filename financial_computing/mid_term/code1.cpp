#include<bits/stdc++.h>
using namespace std;
string capitalizeTitle(string title) {
    int n = title.size(), i = 0, j = 0;
    while(i < n && j < n){
        while(j < n && title[j] != ' '){
            j++;
        }
        title[i] = toupper(title[i]);
        // if(j - i < 3){
        //     title[i] = tolower(title[i]); //单词长度为1或2,首字母小写
        // }
        // else{
        //     title[i] = toupper(title[i]); //首字母大写
        // }
        for(int k = i + 1; k < j; k++){
            title[k] = tolower(title[k]);
        }
        j++;
        i = j;
    }
    return title;
}
int main(){
    string temp="ni hao woshi";
    temp=capitalizeTitle(temp);
    cout<<temp;
    system("pause");
    return 0;
}