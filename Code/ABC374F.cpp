#include<bits/stdc++.h>

using namespace std;

#define int long long
#define Allc(x) x.begin(),x.end()
const int inf=1e18;

signed main(){
    int n,k,x;
    cin>>n>>k>>x;

    vector<int> t(n),clk;
    for(int &x:t) cin>>x;
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++) clk.push_back(t[i]+j*x);
    }
    sort(Allc(clk));
    clk.erase(unique(Allc(clk)),clk.end());

    int m=clk.size();
    vector<vector<int>> dp(m+1,vector<int>(n,inf));
    dp[0][0]=0;
    int res=inf;
    for(int i=0,nxt=0;i<m;i++){
        while(nxt<m&&clk[nxt]<clk[i]+x) nxt++;
        for(int j=0;j<n;j++){
            if(dp[i][j]>inf/2) continue ;
            dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
            for(int d=j,tmp=dp[i][j];d<min(j+k,n);d++){
                if(clk[i]<t[d]) break ;
                tmp+=(clk[i]-t[d]);
                if(d==n-1) res=min(res,tmp);
                else dp[nxt][d+1]=min(dp[nxt][d+1],tmp);
            }
        }
    }
    cout<<res<<endl;

    return 0;
}