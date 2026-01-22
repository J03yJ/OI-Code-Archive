#include<bits/stdc++.h>

using namespace std;

ifstream fin("road.in");
ofstream fout("road.out");
#define cin fin
#define cout fout

using ll=long long;

const int N=2e6+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)
int fac[N],ifac[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m>n||m<0) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int f[N],g[N],fa[N],siz[N],n;
inline void DFS(int x){
    siz[x]=1,f[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        siz[x]+=siz[y];
        f[x]=1ll*f[x]*g[y]%mod*ifac[siz[y]]%mod;
    }
    g[x]=f[x]=1ll*f[x]*fac[siz[x]-1]%mod;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        int val=1ll*f[x]*Inv(g[y])%mod*Inv(C(siz[x]-1,siz[y]))%mod;
        AddAs(g[x],1ll*g[y]*val%mod*C(siz[x]-1,siz[x]-siz[y])%mod);
    }
}

signed main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    Init(n);
    DFS(1);
    cout<<f[1]<<endl;

    return 0;
}