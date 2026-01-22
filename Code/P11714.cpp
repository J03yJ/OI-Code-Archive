#include<bits/stdc++.h>

using namespace std;

const int N=15+9;
const int M=(1<<15)+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}

int c[N][N],f[M],g[M],n,m;
int cnt[M][N];
inline void InitESum(){
    for(int sta=0;sta<(1<<n);sta++){
        for(int i=1;i<=n;i++){
            if(~sta>>i-1&1) continue ;
            for(int j=1;j<=n;j++) cnt[sta][j]+=c[i][j];
        }
    }
}
inline int ESum(int sta,int tta){
    int sum=0;
    for(int i=1;i<=n;i++) if(tta>>i-1&1) sum+=cnt[sta][i];
    return sum;
}

int pwr[N*N];
inline void InitPow(int lim){
    pwr[0]=1;
    for(int i=1;i<=lim;i++) pwr[i]=Add(pwr[i-1],pwr[i-1]);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++) cin>>u>>v,c[u][v]++;

    InitESum();
    InitPow(m);
    for(int sta=0;sta<(1<<n);sta++){
        g[sta]=pwr[ESum(sta,sta)];
        for(int tta=sta&sta-1;tta;tta=sta&tta-1){
            SubAs(g[sta],1ll*pwr[ESum(sta,sta^tta)]*g[tta]%mod);
        }
    }
    for(int sta=0;sta<(1<<n);sta++){
        f[sta]=g[sta];
        int rta=sta^(sta&-sta);
        for(int tta=rta&rta-1;rta;tta=rta&tta-1){
            AddAs(f[sta],1ll*g[rta^tta]*f[tta|(sta&-sta)]%mod);
            if(!tta) break ;
        }
    }
    
    cout<<f[(1<<n)-1]<<endl;

    return 0;
}