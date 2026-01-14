#include<bits/stdc++.h>

using namespace std;

signed main(){
    int n,m;
    cin>>n>>m;

    vector<int> vis(n+1,0);
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        vis[x]=1;
    }

    cout<<n-m<<endl;
    for(int i=1;i<=n;i++) if(!vis[i]) cout<<i<<' ';cout<<endl;

    return 0;
}