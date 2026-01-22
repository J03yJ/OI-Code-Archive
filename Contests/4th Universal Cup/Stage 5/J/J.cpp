#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

vector<int> e[N],stk;
vector<vector<int>> vdcc;
int dfn[N],low[N],n,m,dcnt;
inline void Tarjan(int x,int fa){
	bool flag=0;
	stk.push_back(x);
	dfn[x]=low[x]=++dcnt;
	for(int y:e[x]){
		if(y==fa) continue ;
		if(!dfn[y]){
			Tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				flag=1;
				vdcc.push_back(vector<int>());
				while(stk.size()){
					int p=stk.back();
					stk.pop_back();
					vdcc.back().push_back(p);
					if(p==y) break ;
				}
				vdcc.back().push_back(x);
			}
		}else low[x]=min(low[x],dfn[y]);
	}
	if(!flag&&!~fa) vdcc.push_back({x});
}
inline void Solve(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,-1);

	vector<int> cnt(n+1,0),du(n+1,0);
	for(auto &v:vdcc){
		if(v.size()<=2) for(int x:v) du[x]=1;
		else for(int x:v) cnt[x]++;
	}

	bool flag=0;
	for(int x=1;x<=n;x++) if(cnt[x]>1&&!du[x]) cout<<x<<' ',flag=1;
	if(!flag) cout<<"Empty";
	cout<<endl;
	
	dcnt=0;
	for(int i=1;i<=n;i++) e[i].clear(),dfn[i]=low[i]=0;
	vdcc.clear();
	stk.clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}