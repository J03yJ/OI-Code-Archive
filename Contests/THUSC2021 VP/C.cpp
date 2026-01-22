#include<bits/stdc++.h>

using namespace std;

const int M=2e6+9;
const int N=21;
using lint=long long;

int a[N][M],n,m;
lint f[M],g[M][N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }

    for(int i=1;i<=m;i++){
        lint sta=0,sum=0;
        for(int j=1;j<=n;j++){
            if(a[j][i]==-1) sta|=1<<j-1;
            else sum+=a[j][i];
        }
        f[sta]+=sum;
        for(int j=1;j<=n;j++) if(a[j][i]!=-1) g[sta][j-1]+=a[j][i];
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<(1<<n);i++){
            if(i>>k&1) continue ;
            f[i|(1<<k)]+=f[i];
            for(int j=0;j<n;j++) g[i|(1<<k)][j]+=g[i][j];
            f[i|(1<<k)]-=g[i][k];
            g[i|(1<<k)][k]=0;
        }
    }
    lint ans=0;
    for(int i=0;i<(1<<n);i++) ans=max(ans,f[i]);

    cout<<ans<<endl;

    return 0;
}