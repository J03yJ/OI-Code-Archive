#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
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

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int f[N][2],fa[N],n;
inline void DFS(int x){
    int mul=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x,DFS(y);
        mul=1ll*mul*f[y][0]%mod;
    }
    f[x][0]=f[x][1]=mul;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        AddAs(f[x][0],1ll*mul*Inv(f[y][0])%mod*f[y][1]%mod);
    }
}

signed main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AddEdge(u,v);
        AddEdge(v,u);
    }

    DFS(1);

    cout<<f[1][0]<<endl;

    return 0;
}