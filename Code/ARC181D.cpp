#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],q[N],n,m;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++) cin>>q[i];

    int res=0;
    for(int i=1;i<=n;i++) res+=abs(i-a[i]),cout<<i-a[i]<<endl;

    cout<<res<<endl;

    return 0;
}