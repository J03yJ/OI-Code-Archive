#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e6+9;
const int mod=1e9+7;
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

int f[N][2],c[N],v[N],n,m;
int fac[N],ifac[N],inv[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
    for(int i=1;i<=lim;i++) inv[i]=Mul(ifac[i],fac[i-1]);
}
inline int C(int n,int m){
    if(m<0||m>n) return 0;
    else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>c[i]>>v[i];

    Init(n);
    f[1][0]=1,f[1][1]=0;
    for(int i=1;i<m;i++){
        int len=c[i+1]-c[i]-1,dv=v[i+1]-v[i]+1;
        int w[2][2]={{0,0},{0,0}};
        for(int j=0,t=1;j<=len;j++,MulAs(t,Mul(dv-1+j,inv[j]))) AddAs(w[0][0],Mul(t,C(len,j)));
        for(int j=0,t=1;j<=len;j++,MulAs(t,Mul(dv+j,inv[j]))) AddAs(w[0][1],Mul(t,C(len,j)));
        SubAs(w[0][1],w[0][0]);
        for(int j=0,t=1;j<=len;j++,MulAs(t,Mul(dv-2+j,inv[j]))) AddAs(w[1][0],Mul(t,C(len,j)));
        for(int j=0,t=1;j<=len;j++,MulAs(t,Mul(dv-1+j,inv[j]))) AddAs(w[1][1],Mul(t,C(len,j)));
        SubAs(w[1][1],w[1][0]);
        if(dv==0){
            w[0][1]=QPow(2,len);
            w[0][0]=w[1][0]=w[1][1]=0;
        }else if(dv==1){
            AddAs(w[1][1],w[1][0]);
            w[1][0]=0;
        }
        for(int p:{0,1}) for(int q:{0,1}) AddAs(f[i+1][q],Mul(w[p][q],f[i][p]));
    }

    cout<<Add(f[m][0],f[m][1])<<endl;

    return 0;
}