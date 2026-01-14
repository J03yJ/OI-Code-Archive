#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m,cnt=0,r=0;
    cin>>n>>m;
    string s;
    cin>>s;
    for(auto c:s){
        if(c=='X') r=0;
        else r++;
        if(r==m) cnt++,r=0;
    }
    cout<<cnt<<endl;
}