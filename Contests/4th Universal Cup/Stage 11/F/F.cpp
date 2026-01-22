#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int L=1e9;
const int N=2e5+9;
const int lgN=2e1;
const ll inf=1e18;

vector<int> e[N];
int l[N],r[N],n;

int fa[N],dep[N],elr[N<<1],pos[N],ecnt;
inline void GetElr(int x){
    elr[++ecnt]=x;
    pos[x]=ecnt;
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        GetElr(y);
		elr[++ecnt]=x;
    }
}
int mn[lgN][N<<1];
inline void InitLCA(){
    for(int i=1;i<=ecnt;i++) mn[0][i]=pos[elr[i]];
    for(int k=1;k<=__lg(ecnt);k++){
        for(int i=1;i+(1<<k)-1<=ecnt;i++){
            mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
        }
    }
}
inline int LCA(int x,int y){
    x=pos[x],y=pos[y];
    if(x>y) swap(x,y);
    int k=__lg(y-x+1);
    return elr[min(mn[k][x],mn[k][y-(1<<k)+1])];
}
inline int Dist(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}

int vis[N],siz[N];
inline void GetGrv(int x,int fa,int tot,int &grv){
    bool flag=1;
    siz[x]=1;
    for(int y:e[x]){
        if(y==fa) continue ;
        if(vis[y]) continue ;
        GetGrv(y,x,tot,grv);
        siz[x]+=siz[y];
        flag&=(siz[y]<=tot/2);
    }
    flag&=(tot-siz[x]<=tot/2);
    if(flag) grv=x;
}
int up[N],lim[N];
vector<int> node[N],val[N];
inline void GetNode(int x,int fa,vector<int> &v){
    v.push_back(x);
    for(int y:e[x]){
        if(y==fa) continue ;
        if(vis[y]) continue ;
        GetNode(y,x,v);
    }
}
vector<array<int,2>> g[N*80]; 
int lc[N*80],rc[N*80],ox[N*80],ix[N*80],tot,pc;
inline int Build(int l,int r){
    int x=++pc;
    ox[x]=++tot;
    ix[x]=++tot;
    g[ox[x]].push_back({ix[x],0});
    if(l==r) return x;
    int mid=l+r>>1;
    lc[x]=Build(l,mid);
    rc[x]=Build(mid+1,r);
    g[ox[x]].push_back({ox[lc[x]],0});
    g[ox[x]].push_back({ox[rc[x]],0});
    g[ix[lc[x]]].push_back({ix[x],0});
    g[ix[rc[x]]].push_back({ix[x],0});
    return x;
}
inline void Link(int x,int L,int R,int l,int r,int u,int k){
    if(l<=L&&R<=r){
        g[u].push_back({ox[x],k});
        g[ix[x]].push_back({u,k});
        return ;
    }
    int mid=L+R>>1;
    if(l<=mid) Link(lc[x],L,mid,l,r,u,k);
    if(r>mid) Link(rc[x],mid+1,R,l,r,u,k);
}
inline void Conquer(int x,int tot,int t){
    GetGrv(x,-1,tot,x);
    GetGrv(x,-1,tot,x);
    vis[x]=1,up[x]=t;

    GetNode(x,-1,node[x]);
    for(int y:node[x]) val[x].push_back(l[y]);
    for(int y:node[x]) val[x].push_back(r[y]);
    val[x].push_back(-1);
    sort(val[x].begin(),val[x].end());
    val[x].erase(unique(val[x].begin(),val[x].end()),val[x].end());
    lim[x]=val[x].size()-1;
    int root=Build(1,lim[x]);
    for(int u:node[x]){
        int lp=lower_bound(val[x].begin(),val[x].end(),l[u])-val[x].begin();
        int rp=lower_bound(val[x].begin(),val[x].end(),r[u])-val[x].begin();
        Link(root,1,lim[x],lp,rp,u,Dist(u,x));
    }

    for(int y:e[x]){
        if(vis[y]) continue ;
        Conquer(y,siz[y],x);
    }
}

ll dis[N*80];
inline void Dij(int s){
    vector<int> vis(tot+1,0);
    for(int i=1;i<=tot;i++) dis[i]=inf;
    dis[s]=0;
    priority_queue<pair<ll,int>> q;
    q.push({0,s});
    while(q.size()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(auto p:g[x]){
            ll tmp=dis[x]+p[1];
            if(p[0]<=n) tmp++;
            if(tmp<dis[p[0]]){
                dis[p[0]]=tmp;
                q.push({-dis[p[0]],p[0]});
            }
        }
    }
}

signed main(){
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);

    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i];

    GetElr(1),InitLCA();

    if(r[1]>=l[n]&&r[n]>=l[1]){
        cout<<Dist(1,n)<<endl;
        return 0;
    }

    tot=n;
    Conquer(1,n,0);
    Dij(1);

    cout<<dis[n]-1<<endl;

    return 0;
}