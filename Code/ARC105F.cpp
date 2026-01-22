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
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int u[M],v[M],n,m;
int cnt[S],f[S],g[S],pw[M];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i];
    pw[0]=1;for(int i=1;i<=m;i++) pw[i]=Add(pw[i-1],pw[i-1]);

    for(int sta=0;sta<(1<<n);sta++){
        for(int i=1;i<=m;i++) if((sta>>u[i]-1&1)&&(sta>>v[i]-1&1)) cnt[sta]++;
        for(int tta=sta;;tta=sta&tta-1){
            AddAs(f[sta],pw[cnt[sta]-cnt[tta]-cnt[sta^tta]]);
            if(!tta) break ;
        }
    }
    for(int sta=0;sta<(1<<n);sta++){
        g[sta]=f[sta];
        for(int tta=sta&sta-1;tta>(sta>>1);tta=sta&tta-1){
            SubAs(g[sta],Mul(g[tta],f[sta^tta]));
        }
    }

    cout<<Mul(g[(1<<n)-1],Inv(2))<<endl;

    return 0;
}