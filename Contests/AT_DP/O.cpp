#include<bits/stdc++.h>

using namespace std;

const int N=21;
const int p=1e9+7;

int a[N+9][N+9];
int f[(1<<N)+9];
vector<int> S[N];

signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
    for(int sta=0;sta<(1<<n);sta++){
        int cnt=0;
        for(int i=0;i<n;i++) if((sta>>i)&1) cnt++;
        S[cnt].push_back(sta);
    }

    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int sta:S[i-1]){
            for(int j=1;j<=n;j++){
                if((sta>>(j-1))&1) continue ;
                if(!a[i][j]) continue ;
                f[sta|(1<<j-1)]=(f[sta|(1<<j-1)]+f[sta])%p;
                // cout<<(sta|(1<<j-1))<<endl;
            }
            // cout<<i<<" : a["<<sta<<"] = "<<f[sta]<<endl;
        }
    }
    cout<<f[(1<<n)-1]<<endl;

    return 0;
}