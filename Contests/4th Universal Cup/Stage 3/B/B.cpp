#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e2+9;
const ll inf=1e18;

vector<int> e[N];
ll f[N][N][N],tmp[N][N],a[N];
int fa[N],siz[N],n;
inline void DFS(int x){
	siz[x]=1;
	for(int i=1;i<=n;i++) f[x][1][i]=i*a[x];
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		for(int i=1;i<=siz[x]+siz[y];i++){
			for(int j=1;j<=n;j++) tmp[i][j]=inf;
		}
		for(int i=1;i<=siz[x];i++){
			for(int j=1;j<=siz[y];j++){
				for(int k=1;k<=n;k++){
					if(j+k<=n) tmp[i][k]=min(tmp[i][k],f[x][i][k]+f[y][j][j+k]);
					tmp[i+j][k]=min(tmp[i+j][k],f[x][i][k]+f[y][j][j]);
				}
			}
		}
		for(int i=1;i<=siz[x]+siz[y];i++){
			for(int j=1;j<=n;j++) f[x][i][j]=tmp[i][j];
		}
		siz[x]+=siz[y];
	}
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	DFS(1);
	
	ll ans=inf;
	for(int i=1;i<=n;i++) ans=min(ans,f[1][i][i]);
	
	cout<<ans<<endl;
	
	for(int i=1;i<=n;i++) e[i].clear();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}