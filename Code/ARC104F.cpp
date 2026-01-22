#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e2+9;
const int mod=1e9+7;

int f[N][N][N],a[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]=min(a[i],n);

    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) f[i+1][i][j]=1;
    for(int len=1;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            for(int p=i;p<=j;p++){
                for(int k=1;k<=n;k++){
                    f[i][j][k]+=1ll*f[i][p-1][min(k,a[p])]*f[p+1][j][min(k,a[p])-1]%mod;
                    if(f[i][j][k]>=mod) f[i][j][k]-=mod;
                }
            }
        }
    }

    cout<<f[1][n][n]<<endl;

    return 0;
}