#include<bits/stdc++.h>

using namespace std;

ifstream fin("council.in");
ofstream fout("council.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const int inf=1e9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}

int dis[N],imp[N],n,k;
inline void GetDis(){
	vector<int> vis(n+1,0);
	priority_queue<array<int,2>> q;
	for(int i=1;i<=n;i++) dis[i]=inf;
	for(int i=1;i<=k;i++) q.push({-(dis[imp[i]]=0),imp[i]});
	while(q.size()){
		int x=q.top()[1];
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(max(dis[x],w[i])<=dis[y]){
				q.push({-(dis[y]=max(dis[x],w[i])),y});
			}
		}
	}
}

int fa[N][lgN],mx[N][lgN],dep[N];
inline void DFS(int x){
	for(int k=1;k<lgN;k++){
		fa[x][k]=fa[fa[x][k-1]][k-1];
		mx[x][k]=max(mx[x][k-1],mx[fa[x][k-1]][k-1]);
	}
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x][0]) continue ;
		fa[y][0]=x,mx[y][0]=w[i];
		dep[y]=dep[x]+1;
		DFS(y);
	}
}
inline int MaxW(int x,int y){
	int ans=0;
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--){
		if(dep[fa[x][k]]>=dep[y]){
			ans=max(ans,mx[x][k]);
			x=fa[x][k];
		}
	}
	if(x==y) return ans;
	for(int k=lgN-1;~k;k--){
		if(fa[x][k]!=fa[y][k]){
			ans=max(ans,max(mx[x][k],mx[y][k]));
			x=fa[x][k],y=fa[y][k];
		}
	}
	return max(ans,max(mx[x][0],mx[y][0]));
}

struct Fenw{
	int lim,sft;
	vector<ll> tr;
	inline void Set(int _lim,int _beg){lim=_lim,sft=1-_beg,tr=vector<ll>(lim+1,0);}
	inline void Add(int x,ll k){x+=sft;tr[x]=tr[x-1]+k;}
	inline ll Ask(int l,int r){return tr[r+=sft]-tr[l+=sft-1];}
	inline void Clear(){tr.clear(),lim=sft=0;}
}tr[N][2][2],_tr[N][2][2];

ll ans;
vector<int> node[N],val[N],id[N],pos[N];
vector<int> _val[N],_id[N],_pos[N];
int up[N],vis[N],siz[N],typ[N],root;
inline void GetGrv(int x,int tot,int fa,int &grv){
	bool flag=1;
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue ;
		if(vis[y]) continue ;
		GetGrv(y,tot,x,grv);
		siz[x]+=siz[y];
		if(siz[y]>tot/2) flag=0;
	}
	if(tot-siz[x]>tot/2) flag=0;
	if(flag) grv=x;
}
inline void Init(int &x,int f,int tot){
	GetGrv(x,tot,-1,x);
	GetGrv(x,tot,-1,x);
	up[x]=f,vis[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(vis[y]) continue ;
		Init(y,x,siz[y]);
		node[x].insert(node[x].end(),node[y].begin(),node[y].end());
	}
	node[x].push_back(x);
	id[x]=val[x]=vector<int>(node[x].size());
	for(int i=0;i<node[x].size();i++) val[x][i]=max(dis[x],MaxW(node[x][i],x));
	iota(id[x].begin(),id[x].end(),0);
	sort(id[x].begin(),id[x].end(),[&x](int i,int j){return val[x][i]<val[x][j];});
	for(int p:{0,1}) for(int q:{0,1}) tr[x][p][q].Set(id[x].size()+1,0);
	for(int i=0;i<node[x].size();i++) pos[node[x][id[x][i]]].push_back(i);
	for(int i=0;i<id[x].size();i++){
		tr[x][typ[node[x][id[x][i]]]][0].Add(i,1);
		tr[x][!typ[node[x][id[x][i]]]][0].Add(i,0);
		tr[x][typ[node[x][id[x][i]]]][1].Add(i,val[x][id[x][i]]);
		tr[x][!typ[node[x][id[x][i]]]][1].Add(i,0);
		ans+=tr[x][!typ[node[x][id[x][i]]]][0].Ask(0,i-1)*val[x][id[x][i]];
	}
	if(f){
		_id[x]=_val[x]=vector<int>(node[x].size());
		for(int i=0;i<node[x].size();i++) _val[x][i]=max(dis[f],MaxW(node[x][i],f));
		iota(_id[x].begin(),_id[x].end(),0);
		sort(_id[x].begin(),_id[x].end(),[&x](int i,int j){return _val[x][i]<_val[x][j];});
		for(int p:{0,1}) for(int q:{0,1}) _tr[x][p][q].Set(_id[x].size()+1,0);
		for(int i=0;i<node[x].size();i++) _pos[node[x][_id[x][i]]].push_back(i);
		for(int i=0;i<_id[x].size();i++){
			_tr[x][typ[node[x][_id[x][i]]]][0].Add(i,1);
			_tr[x][!typ[node[x][_id[x][i]]]][0].Add(i,0);
			_tr[x][typ[node[x][_id[x][i]]]][1].Add(i,_val[x][_id[x][i]]);
			_tr[x][!typ[node[x][_id[x][i]]]][1].Add(i,0);
			ans-=_tr[x][!typ[node[x][_id[x][i]]]][0].Ask(0,i-1)*_val[x][_id[x][i]];
		}
	}
}
inline void Flip(int x){
	for(int i=0,u=x;i<pos[x].size();i++,u=up[u]){
		int j=pos[x][i];
		ans-=tr[u][!typ[x]][0].Ask(0,j-1)*val[u][id[u][j]];
		ans-=tr[u][!typ[x]][1].Ask(j+1,id[u].size()-1);
		ans+=tr[u][typ[x]][0].Ask(0,j-1)*val[u][id[u][j]];
		ans+=tr[u][typ[x]][1].Ask(j+1,id[u].size()-1);
		if(up[u]){
			int _j=_pos[x][i];
			ans+=_tr[u][!typ[x]][0].Ask(0,_j-1)*_val[u][_id[u][_j]];
			ans+=_tr[u][!typ[x]][1].Ask(_j+1,_id[u].size()-1);
			ans-=_tr[u][typ[x]][0].Ask(0,_j-1)*_val[u][_id[u][_j]];
			ans-=_tr[u][typ[x]][1].Ask(_j+1,_id[u].size()-1);
		}
	}
	typ[x]^=1;
}

inline void Clear(){
	for(int i=1;i<=n;i++){
		dis[i]=imp[i]=fi[i]=vis[i]=up[i]=siz[i]=typ[i]=0;
		node[i].clear();
		val[i].clear(),id[i].clear(),pos[i].clear();
		for(int j:{0,1}) for(int k:{0,1}) tr[i][j][k].Clear();
		_val[i].clear(),_id[i].clear(),_pos[i].clear();
		for(int j:{0,1}) for(int k:{0,1}) _tr[i][j][k].Clear();
	}
	adj=root=0;
	ans=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>typ[i],pos[i].reserve(20),_pos[i].reserve(20);
		for(int i=1,u,v,w;i<n;i++){
			cin>>u>>v>>w;
			AddEdge(u,v,w);
			AddEdge(v,u,w);
		}
		for(int i=1;i<=k;i++) cin>>imp[i];

		dep[1]=1,DFS(1);
		GetDis();
		Init(root=1,0,n);
		cout<<ans<<endl;
		for(int i=1;i<=n;i++){
			ll tmp=ans;
			Flip(i);
			cout<<ans<<endl;
			ans=tmp;
		}
		
		Clear();
	}
	
	return 0;
}