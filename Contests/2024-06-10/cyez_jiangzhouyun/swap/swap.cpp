#include<bits/stdc++.h>

using namespace std;

const int N=3e2+5;
const int inf=1e9+5;

int a[N],f[N][N][N],g[N][N][N];

int main(){
    int T;
    cin>>T;
    while(T--){
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                for(int k=0;k<=n;k++) f[i][j][k]=g[i][j][k]=-inf;
            }
        }
        f[1][1][1]=a[1];
        f[1][2][0]=a[2];
        for(int i=1;i<=n;i++) g[1][i][1]=a[1];
        for(int i=2;i<=n;i++) g[1][i][0]=a[2];
        for(int i=2;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int k=0;k<=n;k++){
                    if(f[i-1][j][k]>-inf) f[i][j][k]=f[i-1][j][k]+a[j];
                    else f[i][j][k]=-inf;
                    if(j>=i){
                        if(k-1+j-i>=0&&k-1+j-i<=n&&g[i-1][j-1][k-1+j-i]>-inf){
                            f[i][j][k]=max(f[i][j][k],g[i-1][j-1][k-1+j-i]+a[j]);
                        }
                    }
                    g[i][j][k]=max(g[i][j-1][k],f[i][j][k]);
                }
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n;j++) ans=max(ans,f[n][i][j]);
        }
        cout<<ans<<endl;
    }
    return 0;
}