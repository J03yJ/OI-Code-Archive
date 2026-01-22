#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin>>s;
    map<char,int> mp;
    for(auto c:s) mp[c]++;
    if(mp['1']==1&&mp['2']==2&&mp['3']==3) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}