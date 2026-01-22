#include<bits/stdc++.h>

using namespace std;

int main(){
    int cnt=0;
    while(true){
        cnt++;
        cout<<"# "<<cnt<<" : "<<endl;
        system(".\\make.exe");
        system(".\\dfs.exe");
        system(".\\naive.exe");
        if(system("fc dfs.out dfs.ans")) break ;
    }
}