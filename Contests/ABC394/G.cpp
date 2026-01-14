#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=5e2+9;
const int M=1e6+9;
const int lgM=2e1;

int a[N][N],n,m,q;
vector<pii> pos[M];
#define Id(i,j) (((i)-1)*m+(j))

const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
int fa[M],siz[M],t[M];
inline int Find(int x){
    if(fa[x]==x) return x;
    else return Find(fa[x]);
}
inline void Merge(int x,int y,int z){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    siz[x]+=siz[y];
    fa[y]=x,t[y]=z;
}

vector<int> e[M];
int f[M][lgM],mn[M][lgM],dep[M],root;
inline void DFS(int x){for(int y:e[x]) dep[y]=dep[x]+1,DFS(y);}
inline void Init(){
    root=Find(1);
    for(int i=1;i<=n*m;i++) if(fa[i]!=i) e[fa[i]].push_back(i);
    dep[root]=1,DFS(root);
    memset(mn,0x3f,sizeof mn);
    for(int i=1;i<=n*m;i++) f[i][0]=fa[i],mn[i][0]=t[i];
    for(int k=1;k<lgM;k++){
        for(int i=1;i<=n*m;i++){
            f[i][k]=f[f[i][k-1]][k-1];
            mn[i][k]=min(mn[i][k-1],mn[f[i][k-1]][k-1]);
            // cout<<mn[i][k]<<' ';
        }
        // cout<<endl;
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=lgM-1;~k;k--) if(dep[f[x][k]]>=dep[y]) x=f[x][k];
    if(x==y) return x;
    for(int k=lgM-1;~k;k--) if(f[x][k]!=f[y][k]) x=f[x][k],y=f[y][k];
    return fa[x];
}
inline int Min(int x,int y){
    int res=1e6+1;
    for(int k=lgM-1;~k;k--) if(dep[f[y][k]]>=dep[x]) res=min(res,mn[y][k]),y=f[y][k];
    return res;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) pos[a[i][j]].push_back({i,j});
    }

    for(int i=1;i<=n*m;i++) fa[i]=i,siz[i]=1,t[i]=1e6+1;
    for(int i=1e6;i>=0;i--){
        for(pii p:pos[i]){
            int x=fir(p),y=sec(p);
            for(int k=0;k<4;k++){
                int xx=x+dx[k],yy=y+dy[k];
                if(xx<1||yy<1||xx>n||yy>m) continue ;
                if(a[xx][yy]<i) continue ;
                Merge(Id(x,y),Id(xx,yy),i);
                // cout<<x<<' '<<y<<" : "<<xx<<' '<<yy<<" : "<<i<<endl;
            }
        }
    }
    // for(int i=1;i<=n*m;i++) cout<<fa[i]<<'/'<<t[i]<<endl;
    // for(int i=1;i<=n*m;i++) cout<<fa[i]<<' '<<i<<endl;
    Init();

    cin>>q;
    while(q--){
        int si,sj,sf,ti,tj,tf;
        cin>>si>>sj>>sf>>ti>>tj>>tf;

        int x=Id(si,sj),y=Id(ti,tj),lca=LCA(x,y);
        int f=min(Min(lca,x),Min(lca,y));
        f=min(f,min(sf,tf));
        // cout<<x<<" : "<<y<<" : "<<lca<<' '<<f<<endl;

        cout<<sf-f+tf-f<<endl;
    }

    return 0;
}