#include<bits/stdc++.h>

using namespace std;

ifstream fin("road.in");
ofstream fout("road.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=3e3+9;
const int M=N*N;
const int lgN=2e1;

int u[M],v[M],w[M],m;
multiset<int> e[N<<1],vtx;
int id[N<<1],fa[N<<1][lgN],dep[N<<1],val[N<<1],n,q,tot;
inline int Find(int x){return id[x]==x?x:id[x]=Find(id[x]);}
inline void Merge(int x,int y){id[Find(y)]=Find(x);}

int dfn[N<<1],low[N<<1],dcnt;
vector<vector<int>> edcc;
vector<int> stk;
inline void Tarjan(int x,int fa){
	stk.push_back(x);
	dfn[x]=low[x]=++dcnt;
	for(int y:e[x]){
		if(y==fa&&e[x].count(fa)==1) continue ;
		if(!dfn[y]){
			Tarjan(y,x);
			low[x]=min(low[x],low[y]);
		}else low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		edcc.push_back(vector<int>());
		while(stk.size()){
			int p=stk.back();
			stk.pop_back();
			edcc.back().push_back(p);
			if(p==x) break ;
		}
	}
}
inline void Clear(){
	dcnt=0;
	for(int x:vtx) dfn[x]=low[x]=0;
	stk.clear();
}

inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
	if(x==y) return x;
	for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
	return fa[x][0];
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i];

	tot=n;
	vector<int> p(m);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return w[i]<w[j];});
	for(int i=1;i<=n;i++) id[i]=i,vtx.insert(i);
	for(int i=0;i<m;i++){
		if(Find(u[p[i]])==Find(v[p[i]])) continue ;
		e[Find(u[p[i]])].insert(Find(v[p[i]]));
		e[Find(v[p[i]])].insert(Find(u[p[i]]));
		for(int x:vtx) if(!dfn[x]) Tarjan(x,0);
		Clear();
		for(vector<int> &v:edcc){
			if(v.size()==1) continue ;
			val[++tot]=w[p[i]];
			id[tot]=tot;
			for(int x:v){
				fa[Find(x)][0]=tot;
				Merge(tot,x);
				vtx.erase(x);
			}
			for(int x:v){
				for(int y:e[x]){
					if(Find(y)==tot) continue ;
					e[y].erase(x);
					e[y].insert(tot);
					e[tot].insert(y);
				}
				e[x].clear();
			}
			vtx.insert(tot);
		}
		edcc.clear();
	}
	for(int i=tot;i;i--) if(!fa[i][0]) dep[i]=1;
	for(int i=tot;i;i--) if(fa[i][0]) dep[i]=dep[fa[i][0]]+1;
	for(int k=1;k<lgN;k++){
		for(int i=1;i<=tot;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
	}

	cin>>q;
	while(q--){
		int u,v;
		cin>>u>>v;
		if(Find(u)!=Find(v)) cout<<-1<<endl;
		else cout<<val[LCA(u,v)]<<endl;
	}

	return 0;
}