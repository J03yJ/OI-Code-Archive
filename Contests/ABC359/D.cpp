#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;
const int p=998244353;

int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}


int n,k,cnt;
string s,t;

int dp[N],ldp[N];

bool check(string s,int l,int r){
    for(int k=0;k<r-l+1;k++){
        if(s[l+k]!=s[r-k]) return 0;
    }
    return 1;
}

int solve(){
    t=s;
    int ans=0;
    for(int i=0;i<(1<<(k-1));i++) ldp[i]=1;
    for(int i=1;i<=n-k+1;i++){
        t=s;
        for(int sta=0;sta<(1<<k);sta++){
            bool err=0;
            for(int j=0;j<k;j++){
                if(s[i+j]!='?'&&(sta>>j&1)){
                    err=1;
                    break ;
                }
                if(s[i+j]=='?'){
                    if(sta>>j&1) t[i+j]='A';
                    else t[i+j]='B';
                }
            }
            if(err) continue ;
            if(!check(t,i,i+k-1)) dp[sta]=ldp[sta&((1<<(k-1))-1)];
            // cout<<t<<' '<<sta<<' '<<dp[sta]<<' '<<ldp[sta&((1<<(k-1))-1)]<<' '<<check(t,i,i+k-1)<<' '<<i<<' '<<i+k-1<<endl;
        }
        memset(ldp,0,sizeof(ldp));
        for(int sta=0;sta<(1<<k);sta++) ldp[sta>>1]=(ldp[sta>>1]+dp[sta])%p;
        // cout<<endl;
        memset(dp,0,sizeof(dp));
    }
    for(int i=0;i<(1<<(k-1));i++) ans=(ans+ldp[i])%p;
    return ans;
}

int main(){
    cin>>n>>k;cin>>s;s=" "+s;
    cnt=0;
    for(int i=1;i<=n;i++) if(s[i]=='?') cnt++;
    cout<<solve()<<endl;
}