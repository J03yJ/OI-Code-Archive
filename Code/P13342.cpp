#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

ll ans[N<<1];
int u[N],v[N],w[N],ql[N<<1],qr[N<<1],n,m,q;

int fa[N];
set<int> node[N];
vector<int> qry[N];
vector<array<int,3>> seg[N];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}

struct Node{
	int l,r;
	ll tag;
}tr[N<<2];
inline void Push(int x,ll k){tr[x].tag+=k;}
inline void PushDown(int x){if(tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=0;}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,tr[x].l,mid),Build(x<<1|1,mid+1,r);
}
inline void Modify(int x,int l,int r,ll k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
}
inline ll Query(int x,int pos){
	if(tr[x].l==tr[x].r) return tr[x].tag;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos); 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m>>q;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i],u[i]++,v[i]++;
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i],ql[i]++,qry[++qr[i]].push_back(i);
	for(int i=1;i<=n;i++){
		node[i].insert(i);
		fa[i]=i;
	}

	ll sum=0;
	vector<int> ord(m);
	iota(ord.begin(),ord.end(),1);
	sort(ord.begin(),ord.end(),[](int i,int j){return w[i]<w[j];});
	for(int i:ord){
		if(Find(u[i])==Find(v[i])) continue ;
		u[i]=Find(u[i]),v[i]=Find(v[i]);
		if(node[u[i]].size()<node[v[i]].size()) swap(u[i],v[i]);
		fa[v[i]]=u[i];
		vector<array<int,2>> rg;
		for(int x:node[v[i]]){
			auto it=node[u[i]].lower_bound(x);
			auto jt=it==node[u[i]].begin()?node[u[i]].end():prev(it);
			if(it!=node[u[i]].end()) rg.push_back({x,*it});
			if(jt!=node[u[i]].end()) rg.push_back({*jt,x});
		}
		sum+=w[i];
		sort(rg.begin(),rg.end(),[](auto x,auto y){return x[1]<y[1];});
		int l=0;
		for(auto t:rg){
			if(t[0]<=l) continue ;
			seg[t[1]].push_back({l+1,t[0],w[i]});
			l=t[0];
		}
		node[u[i]].insert(node[v[i]].begin(),node[v[i]].end());
		node[v[i]].clear();
	}

	Build(1,1,n);
	for(int i=1;i<=n;i++){
		for(auto t:seg[i]) Modify(1,t[0],t[1],t[2]);
		for(int j:qry[i]) ans[j]=sum-Query(1,ql[j]);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	return 0;
}