#include<bits/stdc++.h>

using namespace std;

ifstream fin("mst.in");
ofstream fout("mst.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e1+9;
const int S=(1<<20)+9;
const int inf=1e9;

int mx[N][N],mn[N][N],mst[S],tsm[S],f[S][N],n,m;

inline int MST(){
	int ans=0;
	vector<int> vis(n+1,0),dis(n+1,-inf);
	dis[1]=0;
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=1;j<=n;j++) if(!vis[j]&&(!p||dis[j]>dis[p])) p=j;
		ans+=dis[p];
		vis[p]=1;
		for(int j=1;j<=n;j++) dis[j]=max(dis[j],mx[p][j]);
	}
	return ans;
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) mx[i][j]=-inf,mn[i][j]=inf;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		mx[u][v]=mx[v][u]=max(mx[u][v],w);
		mn[u][v]=mn[v][u]=min(mn[u][v],w);
	}

	for(int sta=0;sta<(1<<n);sta++){
		mst[sta]=inf,tsm[sta]=-inf;
		for(int i=!sta;i<=__builtin_popcount(sta);i++) f[sta][i]=inf;
	}
	for(int sta=0;sta<(1<<n);sta++){
		if(__builtin_popcount(sta)<=1) mst[sta]=tsm[sta]=0;
		else{
			for(int i=1;i<=n;i++){
				if(~sta>>i-1&1) continue ;
				for(int j=1;j<=n;j++){
					if(i==j) continue ;
					if(~sta>>j-1&1) continue ;
					mst[sta]=min(mst[sta],mn[i][j]+mst[sta^(1<<i-1)]);
					tsm[sta]=max(tsm[sta],mx[i][j]+tsm[sta^(1<<i-1)]);
				}
			}
		}
	}
	for(int sta=1;sta<(1<<n);sta++){
		if(mst[sta]==inf) continue ;
		for(int i=1;i<=n;i++){
			if(~sta>>i-1&1) continue ;
			for(int j=0;j<__builtin_popcount(sta);j++){
				f[sta][j+1]=min(f[sta][j+1],f[sta^(1<<i-1)][j]);
			}
		}
		for(int j=1;j<=__builtin_popcount(sta);j++){
			f[sta][0]=min(f[sta][0],f[sta][j]+j*(mst[sta]^tsm[sta]));
		}
	}

	cout<<f[(1<<n)-1][0]<<endl;

	return 0;
}