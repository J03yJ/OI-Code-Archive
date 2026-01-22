#include<bits/stdc++.h>

using namespace std;

ifstream fin("dag.in");
ofstream fout("dag.out");
#define cin fin
#define cout fout

const int N=5e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}
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

int qn[N],qk[N],f[N],g[N],F[N],G[N],ans[N];
vector<int> q[N];

int fac[N],ifac[N],pw2[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
    pw2[0]=1;
    for(int i=1;i<=lim;i++) pw2[i]=Add(pw2[i-1],pw2[i-1]);
}
inline int C(int n,int m){
    if(m<0||m>n) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline int Solve(int n,int k){
    int f=0;
    for(int t=0;t<=n/(k+1);t++){
        int x=1ll*C(n-k*t,t)*pw2[n-(k+1)*t]%mod;
        int y=1ll*C(n-k*t-1,t)*pw2[n-(k+1)*t-1]%mod;
        AddAs(f,t&1?Sub(y,x):Sub(x,y));
    }
    int g=0;
    for(int t=0;t<=n/(k+1);t++){
        int x=1ll*C(n-k*t,t)*Add(1ll*t*pw2[n-(k+1)*t]%mod,1ll*(n-(k+1)*t)*pw2[n-(k+1)*t-1]%mod)%mod;
        int y=1ll*C(n-k*t-1,t)*Add(1ll*t*pw2[n-(k+1)*t-1]%mod,1ll*(n-(k+1)*t-1)*pw2[n-(k+1)*t-2]%mod)%mod;
        AddAs(g,t&1?Sub(y,x):Sub(x,y));
    }
    return 1ll*g*Inv(f)%mod;
}

signed main(){
    int m;
    cin>>m;

    Init(5e5);
    const int B=7e2;
    for(int i=1;i<=m;i++){
        cin>>qn[i]>>qk[i];
        if(qk[i]<=B) q[qk[i]].push_back(i);
        else ans[i]=Solve(qn[i],qk[i]);
    }

    for(int i=1;i<=2e5;i++){
        if(!q[i].size()) continue ;
        int n=0;
        for(int j:q[i]) n=max(n,qn[j]);
        f[0]=F[0]=1,g[0]=G[0]=0;
        for(int j=1;j<=n;j++){
            f[j]=j>i?Sub(F[j-1],F[j-i-1]):F[j-1];
            g[j]=j>i?Sub(G[j-1],G[j-i-1]):G[j-1];
            AddAs(g[j],f[j]);
            F[j]=Add(F[j-1],f[j]);
            G[j]=Add(G[j-1],g[j]);
        }
        for(int j:q[i]) ans[j]=1ll*g[qn[j]]*Inv(f[qn[j]])%mod;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}