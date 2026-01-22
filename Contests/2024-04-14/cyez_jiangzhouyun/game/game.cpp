#include<bits/stdc++.h>
using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout

#define int long long

const int N=9;
const int p=998244353;

int a[N];
char c[N];
string s;int n;
int dp[N][N];

int calc(){
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(c[i]==s[j]) dp[i][j]=dp[i-1][j-1]+1;
			dp[i][j]=max(dp[i][j],max(dp[i][j-1],dp[i-1][j]));
		}
	}
	return dp[n][n];
}
int ans=0;
void dfs(int x){
	if(x==n+1){
		int k=calc();
		if(k>=n-2) ans++;
		return ;
	}
	for(int i=1;i<=a[x];i++){
		c[x]='A'+i-1;
		dfs(x+1);
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>s;s=" "+s;
	dfs(1);
	cout<<ans<<endl;
}
