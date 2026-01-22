#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using pli=pair<ll,int>;
const int N=2e5+9;
const ll inf=1e18;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj,n,m;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

ll dis[N],sid[N],k,l;
int vis[N],s,t;
inline void Dij(int s,ll *dis){
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    dis[s]=0;
    priority_queue<pli> q;
    q.push({0,s});
    while(q.size()){
        int x=sec(q.top());
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(dis[x]+w[i]<dis[y]){
                dis[y]=dis[x]+w[i];
                q.push({-dis[y],y});
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    cin>>s>>t>>l>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }

    Dij(s,dis),Dij(t,sid);
    if(dis[t]<=k){
        cout<<1ll*n*(n-1)/2<<endl;
        return 0;
    }

    vector<ll> v;
    ll ans=0;
    for(int i=1;i<=n;i++) v.push_back(sid[i]+l);
    sort(v.begin(),v.end());
    for(int i=1;i<=n;i++){
        ans+=upper_bound(v.begin(),v.end(),k-dis[i])-v.begin();
    }
    cout<<ans<<endl;

    return 0;
}