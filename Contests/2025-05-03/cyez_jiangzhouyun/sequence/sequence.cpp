#include<bits/stdc++.h>

using namespace std;

ifstream fin("sequence.in");
ofstream fout("sequence.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e3+9;
const int mod=998244353;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
inline int Inv(int x){return QPow(x,mod-2);}
int fac[N],ifac[N];
inline void InitFac(int lim){
    fac[0]=1;for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
    ifac[lim]=Inv(fac[lim]);for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
    if(m<0||m>n) return 0;
    else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

int a[N],f[N][N],g[N][N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int ans=0;
    sort(a+1,a+n+1,greater<int>());
    for(int i=n;i>=1;i--){
        g[i][n+1]=1;
        for(int j=n,k=i;j>i;j--){
            while(k<=n&&a[j]+a[k]>a[i]) k++;
            AddAs(f[i][j],g[j][max(j+1,k)]);;
            g[i][j]=Add(g[i][j+1],f[i][j]);
            AddAs(ans,f[i][j]);
        }
    }

    cout<<Add(ans,n)<<endl;

    return 0;
}