#include<bits/stdc++.h>

using namespace std;

ifstream fin("blue.in");
ofstream fout("blue.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e4+9;
const int M=1e5+9;

bitset<N> pre[N];
vector<vector<int>> scc;
vector<int> g[N],r[N],stk,node;
int dfn[N],low[N],ins[N],bel[N],mut[N],sf[N],tf[N],n,m,dcnt,scnt;
inline void Tarjan(int x){
	ins[x]=1;
	stk.push_back(x);
	dfn[x]=low[x]=++dcnt;
	for(int y:g[x]){
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		scnt++;
		scc.push_back(vector<int>());
		while(stk.size()){
			int p=stk.back();
			stk.pop_back();
			ins[p]=0;
			bel[p]=scnt;
			scc[scnt].push_back(p);
			if(p==x) break ;
		}
	}
	node.push_back(x);
}
inline void SFind(int x){
	sf[x]=1;
	if(x==n) return ;
	for(int y:g[x]){
		if(sf[y]) continue ;
		if(mut[bel[y]]) continue ;
		SFind(y);
	}
}
inline void TFind(int x){
	tf[x]=1;
	for(int y:r[x]){
		if(tf[y]) continue ;
		if(mut[bel[y]]) continue ;
		TFind(y);
	}
}
inline void Clear(){
	for(int i=1;i<=n;i++){
		g[i].clear(),r[i].clear(),pre[i].reset();
		dfn[i]=low[i]=ins[i]=bel[i]=mut[i]=sf[i]=tf[i]=0;
	}
	dcnt=scnt=0;
	node.clear();
	scc.clear();
}

inline void Solve(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		g[u].push_back(v);
		r[v].push_back(u);
	}

	scc.push_back(vector<int>());
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);

	for(int i=1;i<=scnt;i++){
		mut[i]=(scc[i].size()>1);
		for(int x:scc[i]){
			for(int y:g[x]) mut[i]|=mut[bel[y]];
		}
	}
	if(mut[bel[1]]){
		cout<<0<<endl;
		Clear();
		return ;
	}

	int p=0,err=0;
	SFind(1);
	for(int i=1;i<=n;i++){
		if(sf[i]&&!g[i].size()&&i!=n){
			if(p) err=1;
			else p=i;
		}
	}
	if(err){
		cout<<0<<endl;
		Clear();
		return ;
	}
	TFind(n);

	// for(int i=1;i<=n;i++) cout<<tf[i]<<' ';cout<<endl;
	vector<int> siv(n+1,0);
	for(int i=scnt;i>=1;i--){
		if(mut[i]) continue ;
		int x=scc[i].front();
		// bool flag=tf[x];
		// for(int y:g[x]) flag&=(tf[y]||y==p);
		// flag|=(x==n||x==p);
		// if(!flag){
		// 	cout<<"x "<<x<<endl;
		// 	continue ;
		// }
		pre[x].set(x,1);
		siv[x]=1;
		for(int y:r[x]) pre[x]|=pre[y],cout<<y<<'|'<<(siv[y]|!tf[y])<<' ';cout<<endl;
		cout<<x<<" : ";
		for(int j=1;j<=n;j++) cout<<pre[x][j];cout<<endl;
	}

	ll ans=0;
	if(!p&&sf[n]){
		for(int i=1;i<=n;i++){
			if(!sf[i]||i==n) ans+=n;
			else ans+=(pre[n]^(pre[n]&pre[i])).count();
			if(!tf[i]&&pre[i].any()) assert(0);
		}
	}else{
		ans=(pre[n]^(pre[n]&pre[p])).count();
		for(int j=1;j<=n;j++) cout<<pre[p][j];cout<<endl;
		for(int j=1;j<=n;j++) cout<<pre[n][j];cout<<endl;
		queue<int> q;
		q.push(p);
		vector<int> vis(n+1,0);
		vis[p]=1;
		bitset<N> tmp;
		tmp.reset();
		while(q.size()){
			int x=q.front();
			q.pop();
			cout<<x<<' '<<siv[x]<<endl;
			tmp.set(x);
			for(int y:r[x]){
				if(vis[y]) continue ;
				vis[y]=1;
				q.push(y);
			}
		}
		tmp&=pre[n];
		for(int j=1;j<=n;j++) cout<<tmp[j];cout<<endl;
		cout<<pre[n].count()<<' '<<(pre[n]^tmp).count()<<endl;
	}
	
	cout<<ans<<' '<<p<<endl;

	Clear();
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}