#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pii=pair<int,int>;
const int N=5e3+9;

vector<int> e[N];
int d[N],n,m;
inline void BFS(int s=1){
	vector<pii> a;
	a.push_back({0,s});
	for(int t=0;;t++){
		vector<int> wt(n+1,1e9);
		for(pii p:a){
			int x=sec(p),w=fir(p);
			if(x==n){
				cout<<t<<' '<<w<<endl;
				return ;
			}
			int y=e[x][t%d[x]];
			wt[x]=min(wt[x],w+1);
			wt[y]=min(wt[y],w);
		}
		a.clear();
		a.reserve(n);
		for(int i=1;i<=n;i++) if(wt[i]!=1e9) a.push_back({wt[i],i});
	}
}

inline void Clear(){
	for(int i=1;i<=n;i++){
		e[i].clear();
		d[i]=0;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			d[u]++,d[v]++;
			e[u].push_back(v);
			e[v].push_back(u);
		}

		BFS(1);

		Clear();
	}

	return 0;
}