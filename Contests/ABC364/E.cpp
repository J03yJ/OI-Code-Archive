#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e4+9;
const int K=109;

int a[N],b[N];
int dp[N][K];

signed main(){
    int n,x,y,ans=0;
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    memset(dp,0x3f,sizeof dp);
    for(int i=0;i<=x;i++) dp[i][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=x;j>=a[i];j--){
            for(int k=n;k>=1;k--){
                dp[j][k]=min(dp[j][k],dp[j-a[i]][k-1]+b[i]);
                if(dp[j][k]<=y) ans=max(ans,k);
            }
        }
    }

    if(ans<n) ans++;
    cout<<ans<<endl;

    return 0;
}