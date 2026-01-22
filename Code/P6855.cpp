#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

long long f[N][N],g[N][N],a[N][N];
long long l[N][N],u[N][N];

int main(){
    ios::sync_with_stdio(0);

    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            g[i][j]=max(g[i+1][j],g[i][j+1])+a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            l[i][j]=max(l[i][j-1],f[i][j-1]+g[i+1][j-1]);
            u[i][j]=max(u[i-1][j],f[i-1][j]+g[i-1][j+1]);
        }
    }

    long long ans=1e18;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans=min(ans,max(f[i][j]+g[i][j]-a[i][j]*2,max(l[i][j],u[i][j])));
        }
    }
    cout<<ans<<endl;

    return 0;
}