#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("kings.in");
ofstream fout("kings.out");
#define cin fin
#define cout fout

const int N=5e5+9;
const int inf=1e18;

int fi[N],ne[N],to[N],w[N],adj;
void adeg(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}

int dis[N],siz[N];
bool edge[N];
void dfs(int x){
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		dis[y]=dis[x]+w[i];
		dfs(y);
		siz[x]+=siz[y];
	}
	if(!fi[x]) edge[x]=1;
}

struct node{
	int l,r;
	int dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void pushup(int x){
	dat(x)=min(dat(2*x),dat(2*x+1))+tag(x);
}
void pushdown(int x){
	tag(2*x)+=tag(x);
	dat(2*x)+=tag(x);
	tag(2*x+1)+=tag(x);
	dat(2*x+1)+=tag(x);
	tag(x)=0;
}

void build(int x,int l,int r){
	l(x)=l;r(x)=r;tag(x)=0;
	if(l(x)==r(x)){
		if(edge[l(x)]) dat(x)=dis[l(x)];
		else dat(x)=inf;
		return ;
	}
	int mid=l(x)+r(x)>>1;
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
	pushup(x);
}
void modify(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r){
		tag(x)+=k;
		dat(x)+=k;
		return ;
	}
	pushdown(x);
	int mid=l(x)+r(x)>>1;
	if(l<=mid) modify(2*x,l,r,k);
	if(r>mid) modify(2*x+1,l,r,k);
	pushup(x);
}
int query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x);
	int mid=l(x)+r(x)>>1,ans=inf;
	pushdown(x);
	if(l<=mid) ans=min(ans,query(2*x,l,r));
	if(r>mid) ans=min(ans,query(2*x+1,l,r));
	return ans;
}

int u[N],l[N],r[N],ans[N],n;
vector<int> Q[N];

void solve(int x){
	for(int i:Q[x]){
		ans[i]=query(1,l[i],r[i]);
	}
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		modify(1,1,n,w[i]);
		modify(1,y,y+siz[y]-1,-2*w[i]);
		solve(y);
		modify(1,1,n,-w[i]);
		modify(1,y,y+siz[y]-1,2*w[i]);
	}
}

signed main(){
	int q;
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		if(x>y) swap(x,y);
		adeg(x,y,z);
	}
	dfs(1);
	build(1,1,n);
	for(int i=1;i<=q;i++){
		cin>>u[i]>>l[i]>>r[i];
		Q[u[i]].push_back(i);
	}
	solve(1);
	for(int i=1;i<=q;i++){
		if(ans[i]>inf/2) cout<<"N0T-FOUND"<<endl;
		else cout<<ans[i]<<endl;
	}
	return 0;
}
