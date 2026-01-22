#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e2+9;
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

int fac[N],ifac[N];
inline void InitFac(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
    if(m>n||m<0) return 0;
    else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

int f[N][N],n,m;
struct CPow{
    int p[2][N],base;
    CPow(){}
    CPow(int b){base=b,Init();}
    inline void Init(){
        p[0][0]=p[1][0]=1;
        for(int i=1;i<=n;i++) p[0][i]=Mul(base,p[0][i-1]);
        for(int i=1;i<=n;i++) p[1][i]=Mul(p[0][n],p[1][i-1]);
    }
    inline int Pow(int k){
        return Mul(p[0][k%n],p[1][k/n]);
    }
};

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    InitFac(n);
    for(int k=1;k<=m;k++){
        CPow p1(m-k),p2(m);
        for(int v=1;v<=n;v++){
            f[k][v]=QPow(m,C(v,2));
            for(int i=1;i<v;i++){
                SubAs(f[k][v],Mul(C(v-1,i-1),Mul(f[k][i],Mul(p1.Pow(i*(v-i)),p2.Pow(C(v-i,2))))));
            }
        }
    }

    int ans=Mul(Sub(n,m+1),QPow(m,C(n,2)));
    for(int k=1;k<=m;k++){
        CPow p1(m-k),p2(m);
        for(int v=1;v<=n;v++){
            AddAs(ans,Mul(C(n,v),Mul(f[k][v],Mul(p1.Pow(v*(n-v)),p2.Pow(C(n-v,2))))));
        }
    }

    cout<<ans<<endl;

    return 0;
}