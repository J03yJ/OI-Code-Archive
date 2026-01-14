#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=3e2+9;
const int Q=2e5+9;
const int inf=1e18;

int a[N][N],n,m,q;
int op[Q],qx[Q],qy[Q],ans[Q],blk[N];
int u[Q],v[Q],w[Q];

signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i];
    for(int i=1;i<=q;i++){
        cin>>op[i];
        if(op[i]==1) cin>>qx[i],blk[qx[i]]=1;
        else cin>>qx[i]>>qy[i];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue ;
            a[i][j]=inf;
        }
    }
    for(int i=1;i<=m;i++){
        if(blk[i]) continue ;
        a[u[i]][v[i]]=a[v[i]][u[i]]=min(a[v[i]][u[i]],w[i]);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
            }
        }
    }
    for(int i=q;i>=1;i--){
        if(op[i]==2){
            if(a[qx[i]][qy[i]]==inf) ans[i]=-1;
            else ans[i]=a[qx[i]][qy[i]];
        }else{
            int x=u[qx[i]],y=v[qx[i]],val=w[qx[i]];
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    a[j][k]=min(a[j][k],a[j][x]+a[y][k]+val);
                    a[j][k]=min(a[j][k],a[j][y]+a[x][k]+val);
                }
            }
        }
    }
    for(int i=1;i<=q;i++) if(op[i]==2) cout<<ans[i]<<endl;

    return 0;
}