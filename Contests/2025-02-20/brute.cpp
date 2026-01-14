#include<bits/stdc++.h>

using namespace std;

ifstream fin("brute.in");
ofstream fout("brute.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}

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

int a[N],n;

namespace Brute{
    const int N=2e3+9;
    ll f[N][N],res[N][N];
    int ans[N];
    inline void Solve(){
        const int p=Inv(n-1);
        f[1][a[1]]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!f[i][j]) continue ;
                f[i][j]=f[i][j]%mod*p%mod;
                ll sum=0;
                for(int k=1;k<=n;k++){
                    if(k==i) continue ;
                    int tmp=min(j,a[k]);
                    if(k>i) f[k][tmp]+=f[i][j];
                    else res[k][tmp]+=f[i][j];
                    sum+=j-tmp;
                }
                AddAs(ans[i],sum%mod*f[i][j]%mod);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=a[i];j++) AddAs(ans[i],res[i][j]%mod*j%mod);
        }
        for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    }
}
namespace Up{
    inline bool Check(){
        for(int i=1;i<n;i++) if(a[i]>a[i+1]) return 0;
        return 1;
    }
    int f[N],ans[N];
    inline void Solve(){
        const int p=Inv(n-1);
        f[1]=1;
        int sum=1;
        for(int i=2;i<=n;i++){
            f[i]=1ll*p*sum%mod;
            AddAs(sum,f[i]);
        }
        sum=0;
        for(int i=n;i>=1;i--){
            ans[i]=1ll*sum*p%mod*a[1]%mod;
            AddAs(sum,f[i]);
        }
        for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    }
}
namespace Down{
    inline bool Check(){
        for(int i=1;i<n;i++) if(a[i]<a[i+1]) return 0;
        return 1;
    }
    int f[N],ans[N];
    inline void Solve(){
        const int p=Inv(n-1);
        f[1]=1;
        int sum=1;
        for(int i=2;i<=n;i++){
            f[i]=1ll*p*sum%mod;
            AddAs(sum,f[i]);
        }
        int asum=0,fsum=0;
        for(int i=n;i>=1;i--){
            ans[i]=Add(1ll*p*fsum%mod,1ll*f[i]*p%mod*Sub(1ll*(n-i)*a[i]%mod,asum)%mod);
            AddAs(fsum,1ll*a[i]*f[i]%mod);
            AddAs(asum,a[i]);
        }
        for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    
    if(Down::Check()) Down::Solve();
    else if(Up::Check()) Up::Solve();
    else Brute::Solve();

    return 0;
}