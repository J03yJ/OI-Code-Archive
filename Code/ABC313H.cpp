#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e3+9;
const int mod=998244353;

int f[N][N],a[N],b[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n+1;i++) cin>>b[i];

    sort(a+1,a+n+1,greater<int>());
    sort(b+1,b+n+2,greater<int>());

    f[0][2]=1;
    for(int i=0;i<n;i++){
        for(int j=2;j<=i+2;j++){
            f[i+1][j+1]=(f[i+1][j+1]+1ll*(j-1)*f[i][j])%mod;
            if(a[i+1]<b[i-j+3]) f[i+1][j]=(f[i+1][j]+2ll*(j-1)*f[i][j])%mod;
            if(a[i+1]<b[i-j+4]) f[i+1][j-1]=(f[i+1][j-1]+1ll*(j-1)*f[i][j])%mod;
        }
    }
    cout<<f[n][1]<<endl;

    return 0;
}