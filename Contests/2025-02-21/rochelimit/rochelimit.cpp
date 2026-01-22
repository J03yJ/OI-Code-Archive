#include<bits/stdc++.h>

using namespace std;

ifstream fin("rochelimit.in");
ofstream fout("rochelimit.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e7+9;
const int mod=998244389;
inline void AddAs(ll &x,ll y){x+=y;if(x>=mod) x-=mod;}
inline ll Add(ll x,ll y){x+=y;if(x>=mod) x-=mod;return x;}
inline void SubAs(ll &x,ll y){x-=y;if(x<0) x+=mod;}
inline ll Sub(ll x,ll y){x-=y;if(x<0) x+=mod;return x;}
inline ll QPow(ll x,ll y,ll m=mod){
    y%=m-1,x%=m;
    ll res=1;
    while(y){
        if(y&1) res=res*x%m;
        x=x*x%m;
        y>>=1;
    }
    return res;
}
inline ll Inv(ll x,ll m=mod){return QPow(x,m-2,m);}
inline ll Neg(ll x,ll m=mod){return x?m-x:0;}
inline ll Root(ll a,ll b,ll m){return Neg(b%m,m)*Inv(a%m,m)%m;}

ll n,k,c;
namespace Subtask1{
    ll a,b;
    inline ll F(ll p,ll k,ll c,ll x0){
        ll ans=(k&1?Add(QPow(p-1,k),1):Sub(QPow(p-1,k),1))*Inv(p)%mod;
        if(k%p*x0%p==c) k&1?SubAs(ans,1):AddAs(ans,1);
        return ans;
    }
    inline void Solve(){
        cin>>a>>b;
        ll ans=1,tmp=n;
        for(ll p=2;p*p<=tmp;p++){
            if(tmp%p) continue ;
            ll cnt=0;
            while(!(tmp%p)) cnt++,tmp/=p;
            ans=ans*QPow(QPow(p,k-1),cnt-1)%mod;
            ans=ans*F(p,k,c%p,Root(a,b,p))%mod;
        }
        if(tmp!=1){
            ll p=tmp,cnt=1;
            ans=ans*QPow(QPow(p,k-1),cnt-1)%mod;
            ans=ans*F(p,k,c%p,Root(a,b,p))%mod;
        }
        cout<<ans<<endl;
    }
}
namespace Subtask2{
    int fac[N],ifac[N];
    inline void Init(int lim){
        fac[0]=1;for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
        ifac[lim]=Inv(fac[lim]);for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
    }
    inline ll C(ll n,ll m){
        if(m<0||n<m) return 0;
        else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
    }

    ll a1,b1,a2,b2;
    inline ll G(ll p,ll k,ll c,ll x0,ll x1){
        ll ans=Sub(QPow(p-2,k),QPow(Neg(2),k))*Inv(p)%mod;
        ll tmp=0;
        for(int i=(k*x0%p-c+p)%p*Inv((x0-x1+p)%p,p)%p;i<=k;i+=p) AddAs(tmp,C(k,i));
        return k&1?Sub(ans,tmp):Add(ans,tmp);
    }
    inline void Solve(){
        Init(k);
        cin>>a1>>a2>>b1>>b2;
        ll ans=1,tmp=n;
        for(ll p=2;p*p<=tmp;p++){
            if(tmp%p) continue ;
            ll cnt=0;
            while(!(tmp%p)) cnt++,tmp/=p;            
            ans=ans*QPow(QPow(p,k-1),cnt-1)%mod;
            ans=ans*G(p,k,c%p,Root(a1,Neg(a2,p),p),Root(b1,Neg(b2,p),p))%mod;
        }
        if(tmp!=1){
            ll p=tmp,cnt=1;
            ans=ans*QPow(QPow(p,k-1),cnt-1)%mod;
            ans=ans*G(p,k,c%p,Root(a1,Neg(a2,p),p),Root(b1,Neg(b2,p),p))%mod;
        }
        cout<<ans<<endl;
    }
}

signed main(){
    int T;
    cin>>n>>k>>c>>T;
    T==1?Subtask1::Solve():Subtask2::Solve();

    return 0;
}
