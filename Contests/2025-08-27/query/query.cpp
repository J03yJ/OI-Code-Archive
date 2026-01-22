#include<bits/stdc++.h>

using namespace std;

ifstream fin("query.in");
ofstream fout("query.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}

ll dis[N];
int fa[N],n,m;
inline void GetDis(int x,int fa){
	if(!~fa) dis[x]=0;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue ;
		dis[y]=dis[x]+w[i];
		GetDis(y,x);
	}
}
inline void GetFa(int x){
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		GetFa(y);
	}
}

bool isr[N];
ll mxdep[N],dmt[N],ans[N];
inline void GetMaxDep(int x,int fa){
	mxdep[x]=0;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue ;
		if(isr[y]) continue ;
		GetMaxDep(y,x);
		dmt[x]=max(dmt[x],dmt[y]);
		dmt[x]=max(dmt[x],mxdep[x]+mxdep[y]+w[i]);
		mxdep[x]=max(mxdep[x],mxdep[y]+w[i]);
	}
}
inline int E(int u,int v){
	for(int i=fi[u];i;i=ne[i]) if(to[i]==v) return w[i];
	return 0;
}

signed main(){
	cin>>n;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		AddEdge(u,v,w);
		AddEdge(v,u,w);
	}
	
	vector<int> root;
	GetDis(1,-1);
	int p=max_element(dis+1,dis+n+1)-dis;
	GetDis(p,-1),GetFa(p);
	int q=max_element(dis+1,dis+n+1)-dis;
	ll diam=dis[q];
	while(q){
		isr[q]=1;
		root.push_back(q);
		q=fa[q];
	}
	
	for(int u:root) GetMaxDep(u,-1);
	vector<ll> pdmt(root.size(),0),pdep(root.size(),0);
	for(int i=0;i<root.size();i++){
		pdmt[i]=max(i>0?pdmt[i-1]:0ll,dmt[root[i]]);
		pdmt[i]=max(pdmt[i],(i>0?pdep[i-1]+E(root[i],root[i-1]):0ll)+mxdep[root[i]]);
		pdep[i]=max(i>0?pdep[i-1]+E(root[i],root[i-1]):0ll,mxdep[root[i]]);
	}
	vector<ll> sdmt(root.size(),0),sdep(root.size(),0);
	for(int i=root.size()-1;~i;i--){
		sdmt[i]=max(i+1<root.size()?sdmt[i+1]:0ll,dmt[root[i]]);
		sdmt[i]=max(sdmt[i],(i+1<root.size()?sdep[i+1]+E(root[i],root[i+1]):0ll)+mxdep[root[i]]);
		sdep[i]=max(i+1<root.size()?sdep[i+1]+E(root[i],root[i+1]):0ll,mxdep[root[i]]);
	}

	cin>>m;
	vector<array<ll,3>> op;
	for(int i=0;i+1<root.size();i++){
		ll lim=E(root[i],root[i+1]);
		ll sec=max(pdmt[i],sdmt[i+1]);
		op.push_back({lim,0,lim});
		op.push_back({lim-(diam-sec),1,lim});
		op.push_back({lim-(diam-sec),2,sec});
	}
	for(int i=1,x;i<=m;i++){
		cin>>x;
		op.push_back({x,3,i});
	}

	multiset<ll> s,t;
	sort(op.begin(),op.end(),greater<array<ll,3>>());
	t.insert(1e18);
	s.insert(0);
	for(auto o:op){
		if(o[1]==0) s.insert(o[2]);
		else if(o[1]==1) s.erase(s.find(o[2]));
		else if(o[1]==2) t.insert(o[2]);
		else if(o[1]==3) ans[o[2]]=min(diam,min(diam-(*s.rbegin()-o[0]),*t.begin()));
	}

	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

	return 0;
}