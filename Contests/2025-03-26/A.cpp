#include<bits/stdc++.h>

using namespace std;

using ll=long long;

int mod;
inline ll QPow(ll x,ll y){
    ll res=1;
    x%=mod;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
inline ll F(ll n,ll k){
    if(n==1) return 1;
    ll res=F(n>>1,k);
    res=res*(1+QPow(k,n>>1))%mod;
    if(n&1) res=(res*k%mod+1)%mod;
    return res;
}
inline ll G(ll a,ll b){
    if(!b) return a;
    else return G(b,a%b);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    ll a,b;
    cin>>a>>b>>mod;

    ll g=G(a,b);
    ll res=F(a,10)*F(b/g,QPow(10,g))%mod;

    cout<<res<<endl;

    return 0;
}