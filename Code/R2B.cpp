#include<bits/stdc++.h>

using namespace std;

#define int long long
const int inf=1e18;
const int mod=1e9+7;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        vector<int> a(n+1,0),b(m+1,0),s(n+1,0);
        for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
        for(int i=1;i<=m;i++) cin>>b[i];

        vector<vector<int>> f(n+1,vector<int>(m+1,inf));
        vector<vector<int>> g(n+1,vector<int>(m+1,0));
        for(int j=1;j<=m;j++) f[0][j]=0,g[0][j]=1;
        for(int j=1;j<=m;j++){
            unordered_map<int,int> cnt;
            cnt[f[0][j]]=g[0][j];
            for(int i=1,pos=0;i<=n;i++){
                while(s[i]-s[pos]>b[j]){
                    cnt[f[pos][j]]=(cnt[f[pos][j]]-g[pos][j]+mod)%mod;
                    pos++;
                }
                f[i][j]=min(f[i][j],f[i][j-1]);
                if(f[i][j-1]<f[i][j]) f[i][j]=f[i][j-1],g[i][j]=g[i][j-1];
                else if(f[i][j-1]==f[i][j]) g[i][j]=(g[i][j]+g[i][j-1])%mod;
                if(f[pos][j]+(m-j)<f[i][j]) f[i][j]=f[pos][j]+(m-j),g[i][j]=cnt[f[pos][j]];
                else if(f[i][j]==f[pos][j]+(m-j)) g[i][j]=(g[i][j]+cnt[f[pos][j]])%mod;
                cnt[f[i][j]]=(cnt[f[i][j]]+g[i][j])%mod;
            }
        }
        if(f[n][m]==inf) cout<<-1<<endl;
        else cout<<f[n][m]<<' '<<g[n][m]<<endl;
    }

    return 0;
}