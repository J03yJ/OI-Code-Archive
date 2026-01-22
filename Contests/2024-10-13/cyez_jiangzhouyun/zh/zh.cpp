#include<bits/stdc++.h>

using namespace std;

ifstream fin("zh.in");
ofstream fout("zh.out");
#define cin fin
#define cout fout

#define int long long
const int N=3e3+9;
const int mod=1211221111;

int f[N][N],g[N][N],C[N][N],n,m;

signed main(){
    cin>>n>>m;
    if(m>n) swap(n,m);
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }

    g[m][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=m;k++) f[j][k]=g[j][k],g[j][k]=0;
        }
        for(int j=0;j<=m;j++){
            for(int k=0;k<=m;k++){
                if(k>=1) g[j][k-1]=(g[j][k-1]+f[j][k]*C[k][1]%mod)%mod;
                if(k>=2) g[j][k-2]=(g[j][k-2]+f[j][k]*C[k][2]%mod)%mod;
                if(j>=1) g[j-1][k+1]=(g[j-1][k+1]+f[j][k]*C[j][1]%mod)%mod;
                if(j>=2) g[j-2][k+2]=(g[j-2][k+2]+f[j][k]*C[j][2]%mod)%mod;
                if(j>=1&&k>=1) g[j-1][k]=(g[j-1][k]+f[j][k]*C[j][1]%mod*C[k][1]%mod)%mod;
            }
        }
    }
    
    int ans=0;
    for(int i=0;i<=m;i++) ans=(ans+g[0][i])%mod;
    cout<<ans<<endl;

    return 0;
}