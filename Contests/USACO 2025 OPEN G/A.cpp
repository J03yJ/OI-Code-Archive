#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e6+9;
const int mod=1e9+7;
inline int QPow(int x,ll y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int fac[N],ifac[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m>n||m<0) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

ll t;
int n,k;
char c[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>k>>n>>t;
    for(int i=1;i<=n;i++) cin>>c[i];

    Init(n);
    int cnt=0,ans=1;
    for(int i=n;i>=1;i--){
        if(c[i]=='O') cnt++;
        else{
            ans=1ll*ans*C(cnt,k)%mod;
            cnt-=k;
        }
    }
    if(cnt) ans=0;
    
    cout<<QPow(ans,t)<<endl;
    
    return 0;
}