#include<bits/stdc++.h>

using namespace std;

#define int long long
const int inf=1e18;

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
        for(int j=1;j<=m;j++) f[0][j]=0;
        for(int j=1;j<=m;j++){
            for(int i=1,pos=0;i<=n;i++){
                while(s[i]-s[pos]>b[j]) pos++;
                f[i][j]=min(f[i][j],f[i][j-1]);
                f[i][j]=min(f[i][j],f[pos][j]+(m-j));
                // cout<<f[i][j]<<' ';
            }
            // cout<<endl;
        }
        if(f[n][m]==inf) cout<<-1<<endl;
        else cout<<f[n][m]<<endl;
    }

    return 0;
}