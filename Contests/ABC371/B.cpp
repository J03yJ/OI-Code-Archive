#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    map<int,int> mp;
    while(m--){
        int x;char c;
        cin>>x>>c;
        if(!mp[x]&&c=='M') mp[x]=1,cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}