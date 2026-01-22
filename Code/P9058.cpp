#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int Q=1e6+9;
const int lgN=2e1;
const int NlgN=2e6+9;
const ll inf=1e18+7;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int fa[N],elr[N<<1],pos[N],ecnt;
ll dep[N];
inline void DFS(int x){
    elr[++ecnt]=x;
    pos[x]=ecnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        dep[y]=dep[x]+w[i];
        fa[y]=x;
        DFS(y);
        elr[++ecnt]=x;
    }
}
int mn[N<<1][lgN],lg[N<<1];
inline void Init(){
    for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
    for(int k=1;k<=lg[ecnt];k++){
        for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
    }
}
inline int LCA(int u,int v){
    u=pos[u],v=pos[v];
    if(u>v) swap(u,v);
    int k=lg[v-u+1];
    return elr[min(mn[u][k],mn[v-(1<<k)+1][k])];
}
inline ll Dist(int u,int v){return dep[u]+dep[v]-2*dep[LCA(u,v)];}

int vis[N],siz[N];
inline void GetGrv(int x,int f,int tot,int &grv){
    bool flag=1;
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==f) continue ;
        GetGrv(y,x,tot,grv);
        siz[x]+=siz[y];
        if(siz[y]>tot/2) flag=0;
    }
    if(tot-siz[x]>tot/2) flag=0;
    if(flag) grv=x;
}
inline void GetMem(int x,int f,vector<int> &v){
    siz[x]=1;
    v.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==f) continue ;
        GetMem(y,x,v);
        siz[x]+=siz[y];
    }
}
int pl[NlgN<<1],pr[NlgN<<1],po[NlgN<<1],pcnt;
inline void Divide(int x,int tot){
    GetGrv(x,0,tot,x);
    vis[x]=1;

    vector<int> v,l(tot,0),r(tot,0);
    vector<ll> d(tot);
    GetMem(x,0,v);
    sort(v.begin(),v.end());
    for(int i=0;i<tot;i++) d[i]=Dist(x,v[i]);
    vector<int> stk;
    for(int i=0;i<tot;i++){
        while(stk.size()&&d[i]<d[stk.back()]) stk.pop_back();
        if(stk.size()) l[i]=v[stk.back()];
        stk.push_back(i);
    }
    stk.clear();
    for(int i=tot-1;~i;i--){
        while(stk.size()&&d[i]<d[stk.back()]) stk.pop_back();
        if(stk.size()) r[i]=v[stk.back()];
        stk.push_back(i);
    }
    for(int i=0;i<tot;i++){
        if(l[i]) pcnt++,pl[pcnt]=l[i],pr[pcnt]=v[i];
        if(r[i]) pcnt++,pl[pcnt]=v[i],pr[pcnt]=r[i];
    }

    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        Divide(y,siz[y]);
    }
}

int n;
ll tr[N];
inline void Modify(int x,ll k){
    while(x<=n){
        tr[x]=min(tr[x],k);
        x+=x&-x;
    }
}
inline ll Query(int x){
    ll res=inf;
    while(x){
        res=min(res,tr[x]);
        x&=x-1;
    }
    return res;
}

int ql[Q],qr[Q],qo[Q],q;
ll ans[Q];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1,u,v,w;i<n;i++) cin>>u>>v>>w,AddEdge(u,v,w),AddEdge(v,u,w);
    cin>>q;
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];
    
    DFS(1),Init();
    Divide(1,n);
    for(int i=1;i<=pcnt;i++) po[i]=i;
    sort(po+1,po+pcnt+1,[](int i,int j){return pr[i]<pr[j];});
    for(int i=1;i<=q;i++) qo[i]=i;
    sort(qo+1,qo+q+1,[](int i,int j){return qr[i]<qr[j];});

    for(int i=1;i<=n;i++) tr[i]=inf;
    for(int i=1,j=1,k=1;i<=n;i++){
        while(j<=pcnt&&pr[po[j]]<=i) Modify(n-pl[po[j]]+1,Dist(pl[po[j]],pr[po[j]])),j++;
        while(k<=q&&qr[qo[k]]<=i) ans[qo[k]]=Query(n-ql[qo[k]]+1),k++;
    }

    for(int i=1;i<=q;i++) cout<<(ans[i]!=inf?ans[i]:-1)<<endl;

    return 0;
}