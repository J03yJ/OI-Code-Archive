#include<bits/stdc++.h>

using namespace std;

ifstream fin("city.in");
ofstream fout("city.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=3e5+9;

int fa[N],siz[N];
ll tag[N];
inline int Find(int x){return x==fa[x]?x:Find(fa[x]);}
inline void Merge(int x,int y,ll t){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    tag[x]+=siz[y]*t;
    tag[y]+=siz[x]*t;
    tag[y]-=tag[x];
    fa[y]=x;
    siz[x]+=siz[y];
}
inline ll Calc(int x){
    ll sum=0;
    while(x){
        sum+=tag[x];
        if(x==fa[x]) break ;
        x=fa[x];
    }
    return sum;
}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int w[N],p[N],vis[N],n,m;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AddEdge(u,v);
        AddEdge(v,u);
    }
    
    iota(fa+1,fa+n+1,1);
    fill(siz+1,siz+n+1,1);
    iota(p+1,p+n+1,1);
    sort(p+1,p+n+1,[](int i,int j){return w[i]<w[j];});
    for(int i=1;i<=n;i++){
        int x=p[i];
        vis[x]=1;
        for(int j=fi[x];j;j=ne[j]){
            int y=to[j];
            if(!vis[y]) continue ;
            Merge(x,y,w[x]);
        }
    }

    for(int i=1;i<=n;i++) cout<<Calc(i)+w[i]<<' ';cout<<endl;

    return 0;
}