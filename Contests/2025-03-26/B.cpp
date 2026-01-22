#include<bits/stdc++.h>

using namespace std;

using bint=__int128;
using ll=long long;

inline bint QPow(bint x,bint y,bint mod){
    bint res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
inline bint Phi(bint n){
    bint res=n;
    for(bint i=2;i*i<=n;i++){
        if(n%i) continue ;
        res=res/i*(i-1);
        while(n%i==0) n/=i;
    }
    if(n!=1) res=res/n*(n-1);
    return res;
}
inline void ExGCD(bint a,bint b,bint &x,bint &y){
    if(!b){
        x=1,y=0;
        return ;
    }
    ExGCD(b,a%b,x,y);
    bint z=x;
    x=y;
    y=z-(a/b)*y;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        ll a,n;
        cin>>a>>n;
        ll phi=Phi(n),g=__gcd(n,phi);
        for(bint k=phi,w=QPow(a,phi,n);k<phi+phi;k++,w=1ll*w*a%n){
            if((k-w)%g) continue ;
            bint p,q;
            ExGCD(n/g,phi/g,p,q);
            p*=(k-w)/g,q*=(k-w)/g;
            q=-q;
            bint mod=1ll*n*phi/g;
            bint x=k+q*phi%mod;
            x=(x%mod+mod)%mod;
            cout<<(ll)x<<endl;
            break ;
        }
    }

    return 0;
}