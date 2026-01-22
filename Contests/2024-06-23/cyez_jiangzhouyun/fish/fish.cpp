#include<bits/stdc++.h>

using namespace std;

ifstream fin("fish.in");
ofstream fout("fish.out");
#define cin fin
#define cout fout

const int N=1e7+9;
#define int long long

int n,p;
int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}

int f[N],s[N],in[N],po[N];

signed main(){
    cin>>n>>p;
    const int k=qpow(2,p-2);
    in[0]=po[0]=1;
    for(int i=1;i<=n;i++) in[i]=k*in[i-1]%p,po[i]=2ll*po[i-1]%p;
    for(int i=n;i>=1;i--){
        int k=(i+1)/2;
        if(i==n) k--;
        s[i]=(s[i]+s[i+1])%p;
        f[i]=in[k];
        f[i]=f[i]*(p+1-s[i])%p;
        s[i-(i+1)/2]=(f[i]+s[i-(i+1)/2])%p;
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=(ans+po[n]*f[i]%p*i%p)%p;
    cout<<ans<<endl;
    return 0;
}