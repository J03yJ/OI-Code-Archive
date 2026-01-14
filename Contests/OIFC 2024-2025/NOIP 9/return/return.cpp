#include<bits/stdc++.h>

using namespace std;

ifstream fin("return.in");
ofstream fout("return.out");
#define cin fin
#define cout fout

#define int long long
const int N=6e7+9;
const int mod=1e9+7;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int n,m,k,ans;
signed fac[N],ifac[N];
void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=fac[i-1]*i%mod;
    ifac[lim]=QPow(fac[lim],mod-2);
    for(int i=lim-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}
int C(int n,int m){
    if(m>n||n<0||m<0) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

signed main(){
    cin>>n>>m>>k;
    Init(N-9);
    for(int i=0;i<n-m;i++){
        int tmp=1ll*fac[n-2]*ifac[n]%mod;
        tmp=tmp*C(n,i)%mod;
        tmp=tmp*(n-m-1)%mod;
        tmp=tmp*C(n-i,k)%mod;
        tmp=tmp*C(n-m-2,n-1-m-i)%mod;
        tmp=tmp*C(m+i-2,n-2-k)%mod;
        ans=(ans+tmp)%mod;
    }
    cout<<ans<<endl;

    return 0;
}