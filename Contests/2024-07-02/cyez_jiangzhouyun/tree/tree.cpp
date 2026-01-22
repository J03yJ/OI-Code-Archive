#include<bits/stdc++.h>

using namespace std;

const int N=2e1;

int a[N+9][N+9],fa[N+9],blk[(1<<N)+9],dp[(1<<N)+9][N+9],pcnt[(1<<N)+9];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    fa[find(y)]=find(x);
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++) cin>>u>>v,a[u][v]=a[v][u]=1;
    for(int sta=1;sta<(1<<n);sta++){
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((sta>>i-1&1)&&(sta>>j-1&1)&&a[i][j]) merge(j,i);
            }
        }
        int root=0;
        for(int i=1;i<=n;i++){
            if(!(sta>>i-1&1)) continue ;
            pcnt[sta]++;
            if(!root) root=i;
            if(find(root)==find(i)) blk[sta]|=1<<i-1;
        }
    }
    for(int sta=1;sta<(1<<n);sta++){
        for(int i=1;i<=n;i++){
            if(sta>>i-1&1){
                int tta=blk[sta^(1<<i-1)];
                if(!tta) dp[sta][i]=1;
                // cout<<pcnt[tta]<<endl;
                for(int j=1;j<=n;j++){
                    if(a[i][j]&&(blk[sta^(1<<i-1)]>>j-1&1)){
                        dp[sta][i]=max(dp[sta][i],dp[sta^tta][i]+dp[tta][j]+pcnt[tta]);
                    }
                }
            }
            // cout<<dp[sta][i]<<' ';
        }
        // cout<<endl;
    }
    cout<<dp[(1<<n)-1][1]<<endl;
    return 0;
}