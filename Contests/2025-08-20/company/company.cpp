#include<bits/stdc++.h>

using namespace std;

ifstream fin("company.in");
ofstream fout("company.out");
#define cin fin
#define cout fout
#define endl '\n'

#define double long double
const int N=15+9;
const int S=(1<<15)+9;
const double eps=1e-10;

int n;
double x[N],y[N],w[N],d[N][N];
inline void InitDist(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) d[i][j]=hypotl(x[i]-x[j],y[i]-y[j]);
	}
}

int vis[N];
double dis[N],sum[S];
inline double MST(vector<int> &node){
	double ans=0;
	if(!node.size()) return ans;
	int root=node.front();
	for(int u:node) vis[u]=0,dis[u]=d[root][u];
	vis[root]=1;
	for(int t=1;t<node.size();t++){
		int p=0;
		for(int u:node) if(!vis[u]&&(!p||dis[p]>dis[u])) p=u;
		vis[p]=1;
		ans+=dis[p];
		for(int u:node) dis[u]=min(dis[u],d[p][u]);
	}
	return ans;
}
double mst[S],f[S],g[S];
inline void InitMST(){
	for(int sta=0;sta<(1<<n);sta++){
		vector<int> node;
		sum[sta]=0;
		for(int i=1;i<=n;i++) if(sta>>i-1&1) sum[sta]+=w[i],node.push_back(i);
		mst[sta]=MST(node);
	}
}

signed main(){
	int Tid,T;
	cin>>Tid>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>w[i];
		
		InitDist();
		InitMST();

		for(int sta=0;sta<(1<<n);sta++){
			f[sta]=(sum[sta]-mst[sta])/__builtin_popcount(sta);
			g[sta]=-1e18;
		}
		g[0]=1e18;
		for(int sta=0;sta<(1<<n);sta++){
			int nsta=(1<<n)-1^sta;
			for(int tta=nsta;;tta=tta-1&nsta){
				g[tta|sta]=max(g[tta|sta],min(g[tta],f[sta]));
				if(!tta) break ;
			}
		}
		
		cout<<fixed<<setprecision(9)<<g[(1<<n)-1]<<endl;
	}

	return 0;
}