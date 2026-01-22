#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e6+9;
const int p=998244353;

int fac[N],inv[N];
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%p;
        x=x*x%p;
        y>>=1;
    }
    return res;
}
void init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%p;
    inv[n]=qpow(fac[n],p-2);
    for(int i=n-1;~i;i--) inv[i]=inv[i+1]*(i+1)%p;
}
int C(int n,int m){
    return fac[n]*inv[n-m]%p*inv[m]%p;
}

signed main(){
    int r,g,b,k;
    cin>>r>>g>>b>>k;
    init(max(g+b,max(r+b,r+k)));
    cout<<C(g+b,g-k)*C(b+k,k)%p*C(r+b,r-k)%p<<endl;
}