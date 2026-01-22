#include<bits/stdc++.h>

using namespace std;

ifstream fin("roll.in");
ofstream fout("roll.out");
#define cin fin
#define cout fout

using ll=long long;

const int N=1e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
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
int fac[N],ifac[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m<0||m>n) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int a[N],n,m;
vector<vector<int>> f,g;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    if(m>1000){
        Init(m);
        f=vector<vector<int>>(n+1,vector<int>(m+1,0));
        f[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=(i==n?m:0);j<=m;j++){
                for(int k=(i==1?j:0);k<=j;k++) AddAs(f[i][j],1ll*f[i-1][j-k]*QPow(a[i],k)%mod*Inv(k+1)%mod*C(j,k)%mod);
            }
        }
        cout<<f[n][m]<<endl;
    }else{
        Init(m);
        f=vector<vector<int>>(n+1,vector<int>(m+1,0));
        g=vector<vector<int>>(m+1,vector<int>(m+1,0));
        f[0][0]=1;
        for(int j=0;j<=m;j++){
            for(int k=0;k<=j;k++) g[j][k]=1ll*C(j,k)*Inv(k+1)%mod;
        }
        for(int i=1;i<=n;i++){
            for(int j=(i==n?m:0);j<=m;j++){
                ll sum=0;
                for(int k=(i==1?j:0),pw=QPow(a[i],k);k<=j;k++,pw=1ll*pw*a[i]%mod){
                    sum+=1ll*f[i-1][j-k]*pw%mod*g[j][k]%mod;
                }
                f[i][j]=sum%mod;
            }
        }
        cout<<f[n][m]<<endl;
    }

    return 0;
}