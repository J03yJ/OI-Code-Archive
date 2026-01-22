#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e2+9;
const int inf=1e18;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int a[N],imp[N],n,m,p;
void Clear(){
    for(int i=1;i<=n*2;i++) fi[i]=0;
}

int fa[N],w[N];
array<int,3> e[N];
int Find(int x){
    if(fa[x]==x) return fa[x];
    else return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){
    fa[Find(y)]=Find(x);
}

int siz[N],f[N][N],g[N][N];
void DFS(int x){
    for(int i=0;i<=n;i++) f[x][i]=g[x][i]=0;
    siz[x]=imp[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        DFS(y);
        siz[x]+=siz[y];
    }
    if(!fi[x]&&imp[x]){
        f[x][0]=inf;
        return ;
    }
    if(!siz[x]) return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        for(int j=0;j<=siz[x];j++) g[x][j]=f[x][j];
        for(int j=0;j<=siz[x];j++){
            f[x][j]=inf;
            for(int k=0;k<=min(siz[y],j);k++){
                f[x][j]=min(f[x][j],g[x][j-k]+min(f[y][k],w[x]*siz[y]));
            }
        }
        // cout<<x<<" : ";
    // for(int i=0;i<=siz[x];i++) cout<<f[x][i]<<' ';cout<<endl;
    }
    f[x][0]=inf;
    // cout<<x<<" : ";
    // for(int i=0;i<=siz[x];i++) cout<<f[x][i]<<' ';cout<<endl;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>p;
        for(int i=1;i<=p;i++) cin>>a[i],imp[a[i]]=1;
        for(int i=1;i<=m;i++) cin>>e[i][1]>>e[i][2]>>e[i][0];
        sort(e+1,e+m+1);
        iota(fa+1,fa+n+n,1);

        int tot=n;
        for(int i=1;i<=m;i++){
            int u=e[i][1],v=e[i][2];
            if(Find(u)==Find(v)) continue ;
            w[++tot]=e[i][0];
            AdEg(tot,Find(u));
            AdEg(tot,Find(v));
            // cout<<u<<' '<<v<<" : "<<endl;
            // cout<<tot<<' '<<Find(u)<<endl;
            // cout<<tot<<' '<<Find(v)<<endl;
            Merge(tot,Find(u));
            Merge(tot,Find(v));
        }

        DFS(tot);
        for(int i=1;i<=n;i++) cout<<f[tot][i]<<' ';cout<<endl;

        for(int i=1;i<=tot;i++) imp[i]=0;
        Clear();
    }
    return 0;
}