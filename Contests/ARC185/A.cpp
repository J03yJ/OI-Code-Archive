#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        int x=n*(n+1);
        // cout<<x%m<<endl;
        if(x%m&&x%m<=n) cout<<"Bob"<<endl;
        else cout<<"Alice"<<endl;
    }
}