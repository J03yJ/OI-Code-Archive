#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e6+9;

int f[N][2],a[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    f[0][1]=-1e18;
    for(int i=1;i<=n;i++){
        f[i][0]=max(f[i-1][0],f[i-1][1]+a[i]*2);
        f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]);
    }
    cout<<max(f[n][0],f[n][1])<<endl;

    return 0;
}