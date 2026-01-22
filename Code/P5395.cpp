#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ssiz(x) (signed)x.size()
const int mod=167772161;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

const int gmod=3;
const int invg=Inv(gmod);
using Poly=vector<int>;

void NTT(Poly &f,Poly &r,int lim,int flag){
    for(int i=0;i<lim;i++) if(i<r[i]) swap(f[i],f[r[i]]);
    for(int k=1;k<lim;k<<=1){
        int len=k<<1,gn=QPow(flag>0?gmod:invg,(mod-1)/len);
        for(int i=0;i<lim;i+=len){
            for(int j=0,g=1;j<k;j++,g=g*gn%mod){
                int tmp=f[i+j+k]*g%mod;
                f[i+j+k]=f[i+j]-tmp;
                if(f[i+j+k]<0) f[i+j+k]+=mod;
                f[i+j]=f[i+j]+tmp;
                if(f[i+j]>=mod) f[i+j]-=mod;
            }
        }
    }
    if(!~flag){
        int inv=Inv(lim);
        for(int &x:f) x=x*inv%mod;
    }
}
Poly Mul(Poly &f,Poly &g){
    int len=ssiz(f)+ssiz(g)-1,lim=1;
    while(lim<len) lim<<=1;
    f.resize(lim,0),g.resize(lim,0);

    Poly rev(lim,0),h(lim,0);
    for(int i=0;i<lim;i++){
        rev[i]=rev[i>>1]>>1;
        if(i&1) rev[i]|=lim>>1;
    }
    NTT(f,rev,lim,1),NTT(g,rev,lim,1);
    for(int i=0;i<lim;i++) h[i]=f[i]*g[i]%mod;
    NTT(h,rev,lim,-1);

    h.resize(len,0);
    return h;
}

const int N=2e5+9;
int fac[N],ifac[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'


    cin>>n;
    Poly f(n+1,0),g(n+1,0);
    fac[0]=1;for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=Inv(fac[n]);for(int i=n-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;

    for(int i=0;i<=n;i++) f[i]=ifac[i]*QPow(i,n)%mod;
    for(int i=0;i<=n;i++) g[i]=ifac[i]*QPow(mod-1,i)%mod;
    Poly h(Mul(f,g));

    for(int i=0;i<=n;i++) cout<<h[i]<<' ';cout<<endl;

    return 0;
}