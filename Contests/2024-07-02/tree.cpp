#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define rep0(i,r) for (int i=0,i##end=r;i<i##end;++i)
#define rep(i,l,r) for (int i=l;i<=r;++i)
#define per(i,r,l) for (int i=r;i>=l;--i)
#define pr pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
const int N=30,S=1<<21;
int G[N][N],fa[N],block[S],cnt[S],dp[S][N];
int getfa(int u){ return fa[u]==u?u:fa[u]=getfa(fa[u]); }
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m; scanf("%d%d",&n,&m);
	rep(i,1,m){
		int u,v; scanf("%d%d",&u,&v);
		G[u][v]=G[v][u]=1;
	}
	rep(s,1,(1<<n)-1){
		rep(i,1,n) fa[i]=i;
		rep(i,1,n)
			rep(j,1,n)
				if ((s>>i-1&1)&&(s>>j-1&1)&&G[i][j]) fa[getfa(i)]=getfa(j);
		int t=0;
		rep(i,1,n)
			if (s>>i-1&1){
				++cnt[s];
				if (!t) t=i;
				if (getfa(i)==getfa(t)) block[s]|=1<<i-1;
			}
	}
	rep(s,1,(1<<n)-1)
		rep(i,1,n)
			if (s>>i-1&1){
				int t=block[s^(1<<i-1)];
				if (t==0) dp[s][i]=1;
				rep(j,1,n)
					if (G[i][j]&&(block[s^(1<<i-1)]>>j-1&1))
						dp[s][i]=max(dp[s][i],dp[s^t][i]+dp[t][j]+cnt[t]);
			}
	cout<<dp[(1<<n)-1][1]<<endl;
	return 0;
}
