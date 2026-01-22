#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int M=2e3+9;
const int mod=1e9+7;

int a[N],b[N],n;
int rrf[M<<1][M<<1],*rf[M<<1],**f;
void InitF(){
    f=rf+M;
    for(int i=0;i<(M<<1);i++) rf[i]=rrf[i]+M;
}

int fac[N],ifac[N];
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void InitC(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=QPow(fac[n],mod-2);
    for(int i=n-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m>n) return 0;
    else return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

    InitF();
    int alm=0,blm=0;
    for(int i=1;i<=n;i++) f[-a[i]][-b[i]]++;
    for(int i=1;i<=n;i++) alm=max(alm,a[i]),blm=max(blm,b[i]);
    for(int i=-alm;i<=alm;i++){
        for(int j=-blm;j<=blm;j++){
            f[i][j]=(f[i][j]+(f[i-1][j]+f[i][j-1])%mod)%mod;
        }
    }

    int ans=0;
    InitC(alm+blm<<1);
    for(int i=1;i<=n;i++){
        ans=(ans+f[a[i]][b[i]])%mod;
        ans=(ans-C(a[i]+b[i]<<1,a[i]<<1)+mod)%mod;
    }
    cout<<ans*QPow(2,mod-2)%mod<<endl;

    return 0;
}