#include<bits/stdc++.h>

using namespace std;

ifstream fin("wet.in");
ofstream fout("wet.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

struct Fenw{
	int lim;
	ll tr[N];
	inline void Init(int _lim){lim=_lim;}
	inline void Add(int x,ll k){while(x<=lim) tr[x]+=k,x+=x&-x;}
	inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline ll Ask(int l,ll r){return Ask(r)-Ask(l-1);}
}tsiz,tsum;
inline void Insert(int x,int k){tsum.Add(x,1ll*x*k),tsiz.Add(x,k);}
struct SgT{
	struct Node{
		int l,r;
		int dat,tag;
	}tr[N<<2];

	inline void Push(int x,int k){tr[x].dat=k,tr[x].tag=k;}
	inline void PushDown(int x){if(~tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=-1;}
	inline void Build(int x,int l,int r){
		tr[x].l=l,tr[x].r=r,tr[x].tag=-1;
		if(tr[x].l==tr[x].r) return ;
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	}
	inline void Cover(int x,int l,int r,int k){
		if(l>r) return ;
		if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(l<=mid) Cover(x<<1,l,r,k);
		if(r>mid) Cover(x<<1|1,l,r,k);
	}
	inline int Get(int x,int pos){
		if(tr[x].l==tr[x].r) return tr[x].dat;
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) return Get(x<<1,pos);
		else return Get(x<<1|1,pos);
	}
}tcov;

vector<int> s[N],e[N];
vector<array<int,3>> seg;
vector<array<int,2>> rins;
vector<array<int,3>> rcov;
int a[N],fa[N],dep[N],ans[N],n,m,Tid;
inline void DFS(int x){
	int r1=rins.size(),r2=rcov.size();
	for(int i:s[x]){
		int j=tcov.Get(1,i),y=seg[j][0],l=seg[j][1],r=seg[j][2],p,q;
		if(!j) continue ;
		if(l+dep[x]-dep[y]>i) continue ;
		p=seg.size(),seg.push_back({y,l,i-1});
		q=seg.size(),seg.push_back({x,i+1,r});
		Insert(r-l+1+dep[y],-1);
		rins.push_back({r-l+1+dep[y],1});
		tcov.Cover(1,l,i-1,p);
		tcov.Cover(1,i,i,0);
		tcov.Cover(1,i+1,r,q);
		rcov.push_back({l,r,j});
		Insert(i-l+dep[y],1);
		Insert(r-i+dep[x],1);
		rins.push_back({i-l+dep[y],-1});
		rins.push_back({r-i+dep[x],-1});
	}
	ans[x]=tsum.Ask(dep[x],m+1)-tsiz.Ask(dep[x],m+1)*dep[x];
	for(int y:e[x]){
		dep[y]=dep[x]+1;
		DFS(y);
	}
	while(rins.size()>r1){
		auto t=rins.back();
		rins.pop_back();
		Insert(t[0],t[1]);
	}
	while(rcov.size()>r2){
		auto t=rcov.back();
		rcov.pop_back();
		tcov.Cover(1,t[0],t[1],t[2]);
	}
}

signed main(){
	cin>>Tid>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i],s[a[i]].push_back(i);
	for(int i=2;i<=n;i++) cin>>fa[i],e[fa[i]].push_back(i);

	dep[1]=1;
	seg.push_back({-1,-1,-1});
	seg.push_back({1,1,m});
	tcov.Build(1,1,m);
	tcov.Cover(1,1,m,1);
	tsum.Init(m+1),tsiz.Init(m+1);
	Insert(m+1,1);
	DFS(1);

	for(int i=1;i<=n;i++) cout<<ans[i]<<" \n"[i==n];

	return 0;
}