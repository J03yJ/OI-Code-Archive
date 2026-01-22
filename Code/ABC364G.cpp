#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pli=pair<ll,int>;

const int N=4e3+9;
const int M=8e3+9;
const int K=1e1+9;
const int T=(1<<10)+9;
const ll inf=0x3f3f3f3f3f3f3f3f;

int fi[N],ne[M<<1],to[M<<1],w[M<<1],adj;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int vis[N],n,m,k;
ll f[T][N];
inline void Dijkstra(int sta){
    priority_queue<pli> q;
    for(int i=1;i<=n;i++) if(f[sta][i]!=inf) q.push({-f[sta][i],i});
    for(int i=1;i<=n;i++) vis[i]=0;
    while(q.size()){
        int x=sec(q.top());
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(f[sta][x]+w[i]<f[sta][y]){
                f[sta][y]=f[sta][x]+w[i];
                q.push({-f[sta][y],y});
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>k,k--;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }

    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++) f[0][i]=0;
    for(int i=1;i<=k;i++) f[1<<i-1][i]=0;
    for(int sta=1;sta<(1<<k);sta++){
        for(int tta=sta-1;tta;tta=sta&(tta-1)){
            for(int i=1;i<=n;i++) f[sta][i]=min(f[sta][i],f[tta][i]+f[sta^tta][i]);
        }
        Dijkstra(sta);
    }

    for(int i=k+1;i<=n;i++) cout<<f[(1<<k)-1][i]<<endl;

    return 0;
}