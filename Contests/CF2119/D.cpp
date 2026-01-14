#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e3+9;

int mod;
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
#define Inv(x) QPow(x,mod-2)

int f[N][N],n;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>mod;
        f[n+1][0]=1;
        for(int i=n;i>=1;i--){
            for(int j=0;j<=n-i+1;j++){
                if(j) AddAs(f[i][j],f[i+1][j-1]);
                AddAs(f[i][j],Mul(Mul(f[i+1][j],i),j+1));
            }
        }
        int ans=0;
        for(int i=0;i<=n;i++) AddAs(ans,f[1][i]);
        cout<<ans<<endl;
        for(int i=1;i<=n+1;i++) for(int j=0;j<=n;j++) f[i][j]=0;
    }

    return 0;
}