#include<bits/stdc++.h>

using namespace std;

ifstream fin("physics.in");
ofstream fout("physics.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e6+9;
const int mod=998244353;

int fac[N],ifac[N];
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)
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

string s;
int c[N],sum[N],mus[N],n;

signed main(){
    cin>>s;
    n=s.size();
    s.insert(s.begin(),'#');
    
    int ans=0,cnt=0,tot=0;
    for(char c:s) if(c=='+') cnt++;
    for(char c:s) if(c=='?') tot++;
    Init(tot);
    for(int k=0;k<=tot;k++) sum[k]=C(tot,k);
    for(int k=tot;~k;k--) sum[k]=(sum[k]+sum[k+1])%mod;
    for(int k=0;k<=tot;k++) mus[k]=C(tot-1,k);
    for(int k=tot;~k;k--) mus[k]=(mus[k]+mus[k+1])%mod;
    for(int i=1;i<=cnt+tot;i++){
        int k=max(0,i-cnt);
        if(s[i]=='-') ans=(ans+sum[k])%mod;
        else if(s[i]=='?') ans=(ans+mus[k])%mod;
    }

    cout<<ans<<endl;

    return 0;
}