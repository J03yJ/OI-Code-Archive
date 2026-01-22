#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;
const int V=1e3;
const int mod=1e9+7;

int a[N],rf[N][N],rg[N],n;
int *f[N],*g;

int main(){
    g=rg+V;
    for(int i=0;i<N;i++) f[i]=rf[i]+V;
    
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    f[0][0]=1;
    int l=0,r=0;
    for(int i=1;i<=n;i++){
        for(int j=l;j<=r;j++){
            f[i][j]=(f[i][j]+f[i-1][j])%mod;
            if(j) f[i][j+a[i]]=(f[i][j+a[i]]+(f[i-1][j]+g[j])%mod)%mod;
        }
        g[a[i]]=f[i-1][0];
        l=min(l,l+a[i]);
        r=max(r,r+a[i]);
    }

    int ans=0;
    for(int i=l;i<=r;i++) ans=(ans+f[n][i])%mod;
    cout<<ans<<endl;

    return 0;
}