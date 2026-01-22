#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;
const int inf=1e8;

struct Node{
	int l,r;
	int dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat)+tr[x].tag;}
inline void Push(int x,int k){tr[x].dat+=k,tr[x].tag+=k;}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}

vector<int> e[N];
int pos[N],n,m,q;
int bfn[N],fa[N],st[N],ed[N],bcnt;
inline void BFS(int x){
	queue<int> q;
	q.push(x);
	while(q.size()){
		int x=q.front();
		q.pop();
		bfn[x]=++bcnt;
		st[x]=n,ed[x]=0;
		if(fa[x]){
			st[fa[x]]=min(st[fa[x]],bfn[x]);
			ed[fa[x]]=max(ed[fa[x]],bfn[x]);
		}
		for(int y:e[x]){
			if(bfn[y]) continue ;
			fa[y]=x;
			q.push(y);
		}
	}
}
inline void Near(int x,int k){
	if(ed[x]) Modify(1,st[x],ed[x],k);
	if(fa[x]) Modify(1,bfn[fa[x]],bfn[fa[x]],k);
}
int vis[N],d[N];
inline void Add(int u){
	vis[u]=1;
	Modify(1,bfn[u],bfn[u],inf);
	if(d[u]>1) Near(u,1);
	for(int v:e[u]){
		if(d[v]==1&&vis[v]) Near(v,1);
		d[v]++;
	}
}
inline void Del(int u){
	vis[u]=0;
	Modify(1,bfn[u],bfn[u],-inf);
	if(d[u]>1) Near(u,-1);
	for(int v:e[u]){
		d[v]--;
		if(d[v]==1&&vis[v]) Near(v,-1);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m>>q;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int i=1;i<=n;i++) if(!bfn[i]) BFS(i);
	Build(1,1,n);
	Modify(1,1,n,-inf);
	for(int i=1,j=0;i<=n;Del(i),i++){
		while(j<n&&tr[1].dat<3) Add(++j);
		if(tr[1].dat<3) pos[i]=j;
		else pos[i]=j-1;
	}

	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		if(pos[l]>=r) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}

	return 0;
}