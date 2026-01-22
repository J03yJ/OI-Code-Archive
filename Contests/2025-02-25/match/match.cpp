#include<bits/stdc++.h>

using namespace std;

ifstream fin("match.in");
ofstream fout("match.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e2+9;
const int V=5e2+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}

int w[N],n,lim,c;
int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
inline void ClearEdge(){
    for(int i=1;i<=n;i++) fi[i]=0;
    adj=0;
}

inline void Insert(int x,int f[N][V]){
    cout<<f<<" : "<<endl;
    for(int i=n;i>=1;i--){
        for(int j=lim;j>=0;j--){
            f[i][j]=1ll*f[i][j]*(w[x]+1)%mod;
            for(int k=min(j,w[x]);k>=0;k--) AddAs(f[i][j],f[i-1][j-k]);
        }
    }
    f[0][0]=1ll*f[0][0]*(w[x]+1)%mod;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=lim;j++) cout<<f[i][j]<<' ';cout<<endl;
    }
    cout<<endl;
}
int f[N][V],g[N][V],fa[N],dep[N],ans[V];
inline void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS(y);
    }
}
inline void SubT(int x,vector<int> &v){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        SubT(y,v);
    }
    v.push_back(x);
}
bool vis[N];
inline void Calc(int u,int v){
    vector<int> p,q;
    dep[v]=fa[v]=0,DFS(v),SubT(u,p);
    dep[u]=fa[u]=0,DFS(u),SubT(v,q);
    int dis=dep[v];
    // if(dis>1) return ;

    int fac=1;
    for(int i=1;i<=n;i++) vis[i]=0;
    for(int x:p) vis[x]=1;
    for(int x:q) vis[x]=1;
    for(int i=1;i<=n;i++) if(!vis[i]) fac=1ll*fac*(w[i]+1)%mod;
    memset(f,0,sizeof f),f[0][0]=1;
    for(int x:p) Insert(x,f);
    memset(g,0,sizeof g),g[0][0]=1;
    for(int x:q) Insert(x,g);

    cout<<u<<' '<<v<<" : "<<endl;
    for(int x:p) cout<<x<<' ';cout<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=lim;j++) cout<<f[i][j]<<' ';cout<<endl;
    }
    for(int x:q) cout<<x<<' ';cout<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=lim;j++) cout<<g[i][j]<<' ';cout<<endl;
    }
    for(int i=1;i<=n;i++){
        fac=1ll*fac*i%mod;
        for(int j=0;j<=lim;j++){
            if(!f[i][j]) continue ;
            for(int k=0;k<=lim;k++){
                if(!g[i][k]) continue ;
                cout<<i<<' '<<j+k<<'('<<j<<','<<k<<')'<<" : "<<f[i][j]<<' '<<g[i][k]<<' '<<fac<<endl;
                if(dis&1) AddAs(ans[j+k],1ll*f[i][j]*g[i][k]%mod*fac%mod);
                else SubAs(ans[j+k],1ll*f[i][j]*g[i][k]%mod*fac%mod);
            }
        }
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>c;
        for(int i=1;i<=n;i++) cin>>w[i],lim+=w[i];
        lim=max(c,lim);
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            AddEdge(u,v);
            AddEdge(v,u);
        }

        for(int u=1;u<=n;u++) for(int v=u+1;v<=n;v++) Calc(u,v);
        for(int i=0;i<=c;i++) cout<<ans[i]<<' ',ans[i]=0;cout<<endl;
    }

    return 0;
}