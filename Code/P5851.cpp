#include<bits/stdc++.h>

using namespace std;

const int N=3e2+9;

int w[N][N][N],dp[N][N];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int val,l,r;
        cin>>val>>l>>r;
        for(int j=l;j<=r;j++) w[l][r][j]=val;
    }
    for(int k=1;k<=n;k++){
        for(int len=1;len<=n;len++){
            for(int i=1;i<=n-len+1;i++){
                int j=i+len-1;
                w[i][j][k]=max(w[i][j][k],w[i+1][j][k]);
                w[i][j][k]=max(w[i][j][k],w[i][j-1][k]);
            }
        }
    }
    for(int len=1;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            for(int k=i;k<=j;k++){
                dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j]+w[i][j][k]);
            }
        }
    }

    cout<<dp[1][n]<<endl;

    return 0;
}