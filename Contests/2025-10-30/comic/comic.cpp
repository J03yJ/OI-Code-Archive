#include<bits/stdc++.h>

using namespace std;

ifstream fin("comic.in");
ofstream fout("comic.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int M=1e6+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

int fac[M],ifac[M];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}

int a[N],n,q,id;
vector<int> e[N];
int fa[N],siz[N],dep[N],hson[N];
inline void GetHSon(int x){
	siz[x]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>=siz[hson[x]]) hson[x]=y;
	}
}
int dfn[N],top[N],dcnt;
inline void GetTop(int x,int t){
	top[x]=t;
	dfn[x]=++dcnt;
	if(hson[x]) GetTop(hson[x],t);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetTop(y,y);
	}
}

struct Node{
	int l,r,dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=Add(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){AddAs(tr[x].dat,Mul(tr[x].r-tr[x].l+1,k)),AddAs(tr[x].tag,k);}
inline void PushDown(int x){if(tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=0;}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,tr[x].l,mid),Build(x<<1|1,mid+1,tr[x].r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline int Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Add(Query(x<<1,l,r),Query(x<<1|1,l,r));
}

inline void MSubT(int x,int k){return Modify(1,dfn[x],dfn[x]+siz[x]-1,k);}
inline int QSubT(int x){return Query(1,dfn[x],dfn[x]+siz[x]-1);}
inline void MPath(int u,int v,int k){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		Modify(1,dfn[top[u]],dfn[u],k);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	Modify(1,dfn[u],dfn[v],k);
}
inline int QPath(int u,int v){
	int sum=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		AddAs(sum,Query(1,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	AddAs(sum,Query(1,dfn[u],dfn[v]));
	return sum;
}

signed main(){
	cin>>id>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++) cin>>a[i],SubAs(a[i],0);
	cin>>q;
	
	GetHSon(1);
	GetTop(1,1);
	Build(1,1,n);
	for(int i=1;i<=n;i++) Modify(1,dfn[i],dfn[i],a[i]);
	Init(1e6);
	
	int lst=0;
	while(q--){
		int op,u,v,k;
		cin>>op;
		if(op==1){
			cin>>u>>v>>k;
			u^=lst,v^=lst,SubAs(k,0);
			MPath(u,v,k);
		}else if(op==2){
			cin>>u>>k;
			u^=lst,SubAs(k,0);
			MSubT(u,k);
		}else if(op==3){
			cin>>u>>v>>k;
			u^=lst,v^=lst;
			int ans=QPath(u,v);
			ans=QPow(ans,k);
			MulAs(ans,ifac[k]);
			cout<<ans<<endl;
			lst=ans;
		}else if(op==4){
			cin>>u>>k;
			u^=lst;
			int ans=QSubT(u);
			ans=QPow(ans,k);
			MulAs(ans,ifac[k]);
			cout<<ans<<endl;
			lst=ans;
		}
	}

	return 0;
}