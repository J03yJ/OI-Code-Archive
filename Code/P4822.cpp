#include<bits/stdc++.h>
using namespace std;

const int N=59;
int dp[N][N][N];

inline void chmin(int &x,int k){
	if(k<x) x=k;
}

signed main(){
	int n,m,K;
	cin>>n>>m>>K;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=0;k<=K;k++) dp[i][j][k]=1e9;
		}
		dp[i][i][0]=0;
		dp[i][i][1]=0;
	}
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		dp[x][y][0]=dp[y][x][0]=min(dp[x][y][0],z);
		dp[x][y][1]=dp[y][x][1]=min(dp[x][y][1],z/2);
	}
	
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int cnt=0;cnt<=K;cnt++){
					for(int p=0;p<=cnt;p++){
						chmin(dp[i][j][cnt],dp[i][k][p]+dp[k][j][cnt-p]);
					}
				}
			}
		}
	}
	
//	for(int cnt=0;cnt<=K;cnt++){
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=n;j++) cout<<dp[i][j][cnt]<<' ';
//			cout<<endl;
//		}
//		cout<<endl;
//	}
	
	int ans=1e9;
	for(int cnt=0;cnt<=K;cnt++) ans=min(ans,dp[1][n][cnt]);
	cout<<ans<<endl;
	return 0;
}
