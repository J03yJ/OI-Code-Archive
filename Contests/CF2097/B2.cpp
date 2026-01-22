#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int long long
const int N=1e3+9;
const int M=1e6+9;
const int mod=1e9+7;

int fi[M],ne[M<<1],to[M<<1],adj;
inline void AddEdge(int x,int y){
    // if(~adj&1) cout<<x<<' '<<y<<endl;
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int px[M],py[M],ban[M],vis[N],fa[M],siz[M][2],f[M][2],n,m,k;
inline void DFS(int x){
    vis[x]=1;
    f[x][0]=1;
    siz[x][0]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        siz[x][1]++;
        if(y==fa[x]) continue ;
        if(vis[y]) continue ;
        fa[y]=x;
        DFS(y);
        siz[x][0]+=siz[y][0];
        siz[x][1]+=siz[y][1];
        // cout<<x<<' '<<y<<" ~ "<<f[x][0]<<' '<<f[x][1]<<' '<<f[y][0]<<' '<<f[y][1]<<endl;
        f[x][1]=(1ll*f[x][1]*f[y][1]%mod+1ll*f[x][0]*f[y][0]%mod)%mod;
        f[x][0]=1ll*f[x][0]*f[y][1]%mod;
    }
    if(!ban[x]) f[x][1]=(f[x][1]+f[x][0])%mod;
    // cout<<x<<' '<<siz[x][0]<<' '<<siz[x][1]<<' '<<f[x][0]<<' '<<f[x][1]<<' '<<ban[x]<<endl;
}
inline int Id(int i,int j){return (i-1)*m+j;}
inline void Clear(){
    for(int i=1;i<=n*m;i++) ban[i]=fa[i]=siz[i][0]=siz[i][1]=f[i][0]=f[i][1]=vis[i]=fi[i]=0;
    adj=0;
}
inline void Solve(){
    cin>>n>>m>>k;
    for(int i=1;i<=k+1;i++) cin>>px[i]>>py[i];
    for(int i=1;i<=k+1;i++) ban[Id(px[i],py[i])]=1;
    for(int i=1;i<=k;i++){
        int d=abs(px[i]-px[i+1])+abs(py[i]-py[i+1]);
        if(d!=2){
            cout<<0<<endl;
            Clear();
            return ;
        }
    }
    for(int i=1;i<=k;i++){
        int id=Id(px[i],py[i]);
        if(px[i]==px[i+1]){
            int p=Id(px[i],py[i]+py[i+1]>>1);
            if(!ban[p]) AddEdge(p,id),AddEdge(id,p);
        }else if(py[i]==py[i+1]){
            int p=Id(px[i]+px[i+1]>>1,py[i]);
            if(!ban[p]) AddEdge(p,id),AddEdge(id,p);
        }else{
            int p=Id(px[i],py[i+1]),q=Id(px[i+1],py[i]);
            if(!ban[p]) AddEdge(p,id),AddEdge(id,p);
            if(!ban[q]) AddEdge(q,id),AddEdge(id,q);
        }
    }
    ban[Id(px[k+1],py[k+1])]=0;
    int ans=1;
    for(int i=1;i<=n*m;i++){
        if(vis[i]) continue ;
        // cout<<"# "<<i<<" : "<<endl;
        DFS(i);
        siz[i][1]>>=1;
        if(siz[i][0]==siz[i][1]) ans=2ll*ans%mod;
        else if(siz[i][0]==siz[i][1]+1) ans=1ll*f[i][1]*ans%mod;
        else assert(0);
    }
    cout<<ans<<endl;
    Clear();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}