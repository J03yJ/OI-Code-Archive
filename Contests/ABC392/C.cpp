#include<bits/stdc++.h>

using namespace std;

signed main(){
    int n;
    cin>>n;
    vector<int> p(n+1,0),q(n+1,0);
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>q[i];

    vector<int> ans(n+1,0);
    for(int i=1;i<=n;i++) ans[q[i]]=q[p[i]];

    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}