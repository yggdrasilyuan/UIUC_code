// #include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;
int s;
void print(vector<int> &box){
    cout<<"{ ";
    for(int i=0; i<box.size(); i++)
        cout<<box[i]<<" ";
    cout<<"}"<<endl;
}
void dfs(int a[],int n, int i, vector<int> &box){
    if(i>=n){
        if(box.size()==s){
            print(box);
        }     
        // print(box);
    }
    else{
        box.push_back(a[i]);
        dfs(a, n, i+1, box); //a[i] pick
        box.pop_back();
        dfs(a, n, i+1, box); //a[i] not pick
    }
}

int main(){
    int size_of_array, number_of_objects_to_be_picked;
	int *array; vector<int> box;
	
	cout << "Array Size? ";
	cin >> size_of_array;
	cout << "#Objects to be picked from array? ";
	cin >> number_of_objects_to_be_picked;
    s=number_of_objects_to_be_picked;
	
	// I am just filling the array with integers... it could be a list of
	// other objects, for example.
	array = new int[size_of_array];
	for (int i = 0; i < size_of_array; i++)
		array[i] = i+1;
    dfs(array,size_of_array,0,box);
    system("pause");
    return 0;
}