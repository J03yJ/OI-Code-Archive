#include<bits/stdc++.h>

using namespace std;

const int M=1e2+9;
const int N=2e5+9;
const int mod=998244353;

int dp[N][M],pos[M],cnt,n,k;
int u[N],v[N],w[N],m;

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        pos[++cnt]=u[i];
        pos[++cnt]=v[i];
        w[i]=1;
    }

    if(!m){
        cout<<1<<endl;
        return 0;
    }

    pos[++cnt]=1;
    sort(pos+1,pos+cnt+1);
    cnt=unique(pos+1,pos+cnt+1)-pos-1;
    for(int i=1;i<=cnt;i++){
        m++;
        u[m]=pos[i];
        v[m]=pos[i%cnt+1];
        w[m]=(v[m]-u[m]+n)%n;
    }
    for(int i=1;i<=m;i++){
        u[i]=lower_bound(pos+1,pos+cnt+1,u[i])-pos;
        v[i]=lower_bound(pos+1,pos+cnt+1,v[i])-pos;
    }

    int ans=0;
    dp[0][1]=1;
    for(int i=0;i<=k;i++){
        for(int j=1;j<=m;j++) if(i+w[j]<=k) dp[i+w[j]][v[j]]=(dp[i+w[j]][v[j]]+dp[i][u[j]])%mod;    }
    for(int i=0;i<=k;i++){
        for(int j=1;j<=cnt;j++){
            if(i+(pos[j%cnt+1]-pos[j]+n)%n>k) ans=(ans+dp[i][j])%mod;
        }
    }

    cout<<ans<<endl;
    
    return 0;
}