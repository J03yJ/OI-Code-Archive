#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=4e2+9;
const int M=2e5+9;

int dis[N][N],u[M],v[M],w[M],n,m;
int dp[N][1<<6];
void ChMin(int &x,int y){
    if(y<x) x=y;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j) dis[i][j]=1e18;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
        dis[u[i]][v[i]]=dis[v[i]][u[i]]=min(dis[u[i]][v[i]],w[i]);
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            if(i==k) continue ;
            for(int j=1;j<=n;j++){
                if(i==j) continue ;
                if(j==k) continue ;
                ChMin(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }

    int q;
    cin>>q;
    while(q--){
        int k;
        cin>>k;
        vector<int> b(k);
        for(int i=0;i<k;i++) cin>>b[i];
        
        memset(dp,0x3f,sizeof dp);
        dp[1][0]=0;
        for(int sta=0;sta<(1<<k);sta++){
            for(int i=1;i<=n;i++){
                // cout<<dp[i][sta]<<' ';
                for(int j=0;j<k;j++){
                    if(sta>>j&1) continue ;
                    ChMin(dp[u[b[j]]][sta|(1<<j)],dp[i][sta]+dis[i][v[b[j]]]+w[b[j]]);
                    ChMin(dp[v[b[j]]][sta|(1<<j)],dp[i][sta]+dis[i][u[b[j]]]+w[b[j]]);
                }
            }
            // cout<<endl;
        }
        int ans=1e18;
        for(int i=1;i<=n;i++) ChMin(ans,dp[i][(1<<k)-1]+dis[i][n]);
        cout<<ans<<endl;
    }

    return 0;
}