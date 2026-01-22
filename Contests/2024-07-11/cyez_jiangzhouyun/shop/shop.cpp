#include<bits/stdc++.h>

using namespace std;

ifstream fin("shop.in");
ofstream fout("shop.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;
const int inf=1e9+9;

int a[N],b[N],p[N],dp[N][20];
bool cmp(int i,int j){
    return a[j]*(b[i]+1)<a[i]*(b[j]+1);
}

signed main(){
    int n,T;
    cin>>n>>T;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

    for(int i=1;i<=n;i++) p[i]=i;
    sort(p+1,p+n+1,cmp);

    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        dp[i][0]=0;
        for(int j=1;j<=i&&j<20;j++){
            if(i>j) dp[i][j]=min(dp[i-1][j],min(dp[i-1][j-1]+a[p[i]]*(dp[i-1][j-1]+1)+b[p[i]]+1,T+1));
            else dp[i][j]=min(dp[i-1][j-1]+a[p[i]]*(dp[i-1][j-1]+1)+b[p[i]],T+1);
            // cout<<dp[i][j]<<' ';
        }
        // cout<<endl;
    }
    
    for(int i=min(n,19ll);~i;i--){
        if(dp[n][i]<=T){
            cout<<i<<endl;
            break ;
        }
    }

    return 0;
}