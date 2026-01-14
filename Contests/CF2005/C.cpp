#include<bits/stdc++.h>

using namespace std;

#define int long long
const int inf=1e18;
const int N=2e3+9;
string s[N];
int sc[N][5],cnt[N][5],ed[N][5];
int dp[N][5];
void ChMax(int &x,int y){
    if(y>x) x=y;
}

signed main(){
    int T;
    cin>>T;
    string t="narek";
    while(T--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>s[i];
        for(int i=1;i<=n;i++){
            for(int k=0;k<5;k++){
                int cur=k,cnt1=0,cnt2=0;
                for(int j=0;j<m;j++){
                    if(s[i][j]==t[cur]){
                        cur++;
                        if(cur==5) cnt1+=5,cur=0;
                    }
                    if(t.find(s[i][j])){
                        cnt2++;
                    }
                }
                ed[i][k]=cur;
                sc[i][k]=cnt1;
                cnt[i][k]=cnt2;
            }
        }
        for(int i=0;i<=n;i++){
            for(int k=0;k<5;k++) dp[i][k]=-inf;
        }
        dp[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int k=0;k<5;k++){
                ChMax(dp[i][ed[i][k]],dp[i-1][k]+2*sc[i][k]-cnt[i][k]);
                ChMax(dp[i][ed[i][k]],dp[i-1][ed[i][k]]);
                // cout<<2*sc[i][k]<<' '<<cnt[i][k]<<endl;
            }
            // for(int k=0;k<5;k++) cout<<dp[i][k]<<' ';
            // cout<<endl;
        }
        int ans=0;
        for(int k=0;k<5;k++) ChMax(ans,dp[n][k]);
        cout<<ans<<endl;
    }
    return 0;
}