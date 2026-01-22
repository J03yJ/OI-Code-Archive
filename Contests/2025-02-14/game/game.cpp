#include<bits/stdc++.h>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],d[N],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    d[x]++;
}
int fa[N],f[N],a[N],n,m;
inline void DFS(int x){
    f[x]=0;
    vector<int> v;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        v.push_back(f[y]);
    }
    sort(v.begin(),v.end());
    for(int k:v){
        if(k==f[x]) f[x]++;
        else if(k>f[x]) break ;
    }
}
int dep[N];
inline void GetDepth(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x,dep[y]=dep[x]+1;
        GetDepth(y);
    }
}

namespace Brute{
    inline void Solve(){
        int root=1;
        fa[root]=0,DFS(root);
        while(m--){
            int op;
            cin>>op;
            if(op==1){
                cin>>root;
                fa[root]=0,DFS(root);
            }else if(op==2){
                int x,tmp;
                cin>>x>>tmp;
                a[x]^=tmp&1;
            }else if(op==3){
                int u,k;
                cin>>u>>k;
                fa[u]=dep[u]=0,GetDepth(u);
                int ans=0;
                for(int i=1;i<=n;i++) if(dep[i]<=k&&a[i]) ans^=f[i];
                cout<<ans<<endl;
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    for(int i=1;i<=n;i++) cin>>a[i],a[i]&=1;

    Brute::Solve();
    
    return 0;
}