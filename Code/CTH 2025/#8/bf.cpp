#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int M=2e5+9;
const ll inf=1e18;
const int mod=1e9+7;

ll d[3][M],ans;
int a[3][M],vis[3][M],n,m;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
inline void Dij(int si,int sj,ll dis[3][M]){
	for(int i:{0,1,2}) for(int j=1;j<=m;j++) dis[i][j]=inf,vis[i][j]=0;
	dis[si][sj]=a[si][sj];
	priority_queue<array<ll,3>> q;
	q.push({-dis[si][sj],si,sj});
	while(q.size()){
		int i=q.top()[1],j=q.top()[2];
		q.pop();
		if(vis[i][j]) continue ;
		vis[i][j]=1;
		for(int o:{0,1,2,3}){
			int ii=i+dx[o],jj=j+dy[o];
			if(ii<0||jj<1||ii>2||jj>m) continue ;
			if(dis[i][j]+a[ii][jj]<dis[ii][jj]){
				dis[ii][jj]=dis[i][j]+a[ii][jj];
				q.push({-dis[ii][jj],ii,jj});
			}
		}
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	for(int i=0;i<n;i++){
		for(int j=1;j<=m;j++){
			Dij(i,j,d);
			for(int p=0;p<n;p++){
				for(int q=1;q<=m;q++){
					if(i==p&&j==q) continue ;
					ans=(ans+d[p][q])%mod;
				}
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}