#include<bits/stdc++.h>

using namespace std;

const int N=16;
const int inf=1e9;

int dp[(1<<N)+9][N+9];

string debug(int x,int k,int p){
    p=k-p;
    string s="";
    for(int i=k-1;~i;i--){
        if(i==p||i==p-1) s+='.';
        else if(x>>i&1) s+='B';
        else s+='W';
    }
    return s;
}

int main(){
    int n;
    cin>>n;
    int a=0,b=0;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='B') a|=(1<<i-1);
    }
    // cout<<a<<endl;
    // a<<=2;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='B') b|=(1<<i-1);
    }
    // b<<=2;

    // cout<<a<<' '<<b<<endl;
    // cout<<debug(a,n+2,n+1)<<' '<<debug(b,n+2,n+1)<<endl;

    for(int sta=0;sta<(1<<(n+2));sta++) for(int i=1;i<=n+1;i++) dp[sta][i]=inf;
    dp[a][n+1]=0;
    queue<pair<int,int>> q;
    q.push({a,n+1});
    while(q.size()){
        int sta=q.front().first,x=q.front().second;
        q.pop();
        // cout<<sta<<endl;
        // cout<<debug(sta,n+2,x)<<' '<<x<<' '<<dp[sta][x]<<endl;
        for(int i=1;i<=n+1;i++){
            if(abs(i-x)<=1) continue ;
            int tta=sta;
            tta|=(sta>>i-1&3)<<x-1;
            // cout<<" : "<<sta<<' '<<i<<' '<<(sta>>i-1&3)<<' '<<debug(tta,n+2,i)<<endl;
            tta^=(sta>>i-1&3)<<i-1;
            if(dp[tta][i]!=inf) continue ;
            dp[tta][i]=dp[sta][x]+1;
            q.push({tta,i});
        }
    }

    if(dp[b][n+1]==inf) cout<<-1<<endl;
    else cout<<dp[b][n+1]<<endl;

    return 0;
}