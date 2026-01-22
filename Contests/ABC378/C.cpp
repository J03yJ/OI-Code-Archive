#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n,0);
    for(int &x:a) cin>>x;
    vector<int> b(n,0);
    map<int,int> mp;
    for(int i=0;i<n;i++){
        if(!mp[a[i]]) b[i]=-1;
        else b[i]=mp[a[i]];
        mp[a[i]]=i+1;
    }
    for(int x:b) cout<<x<<' ';cout<<endl;
}