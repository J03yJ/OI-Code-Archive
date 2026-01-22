#include<bits/stdc++.h>

using namespace std;

const int N=17+9;
const int M=17*17+9;
const int S=(1<<17)+9;
const int mod=998244353;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}

int u[M],v[M],n,m;

int fa[N],comp[S],f[S];
inline void Init(){for(int i=1;i<=n;i++) fa[i]=i;}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i];

    for(int sta=0;sta<(1<<n);sta++){
        Init();
        for(int i=1;i<=m;i++){
            if(~sta>>u[i]-1&1) continue ;
            if(~sta>>v[i]-1&1) continue ;
            Merge(u[i],v[i]);
        }
        for(int i=1;i<=n;i++){
            if(~sta>>i-1&1) continue ;
            if(fa[i]!=i) continue ;
            comp[sta]++;
        }
    }
    f[0]=1;
    for(int sta=1;sta<(1<<n);sta++){
        for(int tta=sta;tta;tta=tta-1&sta){
            if(comp[tta]&1) AddAs(f[sta],f[sta^tta]);
            else SubAs(f[sta],f[sta^tta]);
        }
    }
    cout<<f[(1<<n)-1]<<endl;

    return 0;
}