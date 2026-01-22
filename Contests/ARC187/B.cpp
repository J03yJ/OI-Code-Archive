#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e3+9;
const int mod=998244353;

int a[N],mn[N][N],mx[N][N],n,m;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    
    mn[0][m]=1,mx[n+1][1]=1;
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            for(int j=m;j>=1;j--) mn[i][j]=(mn[i][j+1]+mn[i-1][j])%mod;
            for(int j=m;j>=1;j--) mn[i][j]=(mn[i][j]+mn[i-1][j]*(m-j)%mod)%mod;
        }else{
            for(int j=1;j<a[i];j++) mn[i][j]=mn[i-1][j];
            for(int j=a[i];j<=m;j++) mn[i][a[i]]=(mn[i][a[i]]+mn[i-1][j])%mod;
        }
    }
    for(int i=n;i>=1;i--){
        if(a[i]==-1){
            for(int j=1;j<=m;j++) mx[i][j]=(mx[i][j-1]+mx[i+1][j])%mod;
            for(int j=1;j<=m;j++) mx[i][j]=(mx[i][j]+mx[i+1][j]*(j-1)%mod)%mod;
        }else{
            for(int j=m;j>a[i];j--) mx[i][j]=mx[i+1][j];
            for(int j=a[i];j>=1;j--) mx[i][a[i]]=(mx[i][a[i]]+mx[i+1][j])%mod;
        }
    }

    int ans=1;
    for(int i=1;i<=n;i++) if(a[i]==-1) ans=ans*m%mod;
    for(int i=1;i<n;i++){
        for(int j=m,sum=0;j>=2;j--){
            sum=(sum+mn[i][j])%mod;
            ans=(ans+sum*mx[i+1][j-1]%mod)%mod;
        }
    }
    cout<<ans<<endl;

    return 0;
}