#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout

const int N=24;
int a[N+9];
vector<int> dp[2][N+9];
vector<pair<int,int>> cnt[2][N+9];

signed main(){
	int n,m,K;
	cin>>n>>m>>K;
	m/=20;
	int mid=(n+1)/2;
	for(int i=1;i<=n;i++) cin>>a[i];

	dp[0][0].push_back(0);
	for(int i=1;i<=mid;i++){
		for(int j=m-1;~j;j--){
			if(!dp[0][j].size()) continue ;
			vector<int> tmp,ftmp;
			for(int x:dp[0][j]){
				tmp.push_back(x+a[i]);
				ftmp.push_back(x+a[i]*a[i]+1);
			}
			for(int x:tmp) dp[0][j].push_back(x);
			for(int x:ftmp) dp[0][j+1].push_back(x);
		}
	}
	
	dp[1][0].push_back(0);
	for(int i=mid+1;i<=n;i++){
		for(int j=m-1;~j;j--){
			if(!dp[1][j].size()) continue ;
			vector<int> tmp,ftmp;
			for(int x:dp[1][j]){
				tmp.push_back(x+a[i]);
				ftmp.push_back(x+a[i]*a[i]+1);
			}
			for(int x:tmp) dp[1][j].push_back(x);
			for(int x:ftmp) dp[1][j+1].push_back(x);
		}
	}
	
	for(int k:{0,1}){
		for(int j=0;j<=m;j++){
			sort(dp[k][j].begin(),dp[k][j].end());
			for(int x:dp[k][j]){
				if(!cnt[k][j].size()||cnt[k][j].back().first!=x) cnt[k][j].push_back({x,1});
				else cnt[k][j].back().second++;
			}
			cnt[k][j].push_back({1e9+7,0});
		}
	}
	
	int ans=0;
	for(int i=0;i<=m;i++){
		for(pair<int,int> x:cnt[0][i]){
			for(int j=0;i+j<=m;j++){
				pair<int,int> y=*lower_bound(cnt[1][j].begin(),cnt[1][j].end(),make_pair(K-x.first,0ll));
				if(y.first+x.first!=K) continue ;
				ans+=y.second*x.second;
			}
		}
	}
	
	cout<<ans<<endl;
	return 0;
}
