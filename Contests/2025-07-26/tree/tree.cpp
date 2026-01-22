#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout	
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],dep[N],siz[N],hson[N],n,m;
inline void GetHSon(int x){
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
}
int dfn[N],idfn[N],top[N],dcnt;
inline void GetDFN(int x,int t){
	top[x]=t;
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
	if(hson[x]) GetDFN(hson[x],t);
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetDFN(y,y);
	}
}

inline int KthAnc(int x,int k){
	while(k>=dep[x]-dep[top[x]]+1){
		k-=dep[x]-dep[top[x]]+1;
		x=fa[top[x]];
	}
	return idfn[dfn[x]-k];
}
inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
inline int Dist(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}

pii fmx[N],smx[N];
inline void LongUp(int x){
	fmx[x]=smx[x]={0,x};
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		LongUp(y);
		pii tmp={fir(fmx[y])+1,sec(fmx[y])};
		if(tmp>fmx[x]) smx[x]=fmx[x],fmx[x]=tmp;
		else if(tmp>smx[x]) smx[x]=tmp;
	}
}
inline void LongDown(int x,pii dwn){
	if(dwn>fmx[x]) smx[x]=fmx[x],fmx[x]=dwn;
	else if(dwn>smx[x]) smx[x]=dwn;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		int z=sec(fmx[x]);
		if(dfn[y]<=dfn[z]&&dfn[z]<dfn[y]+siz[y]) LongDown(y,{fir(smx[x])+1,sec(smx[x])});
		else LongDown(y,{fir(fmx[x])+1,sec(fmx[x])});
	}
}

int fsum[N],gsum[N];
#define fsum(l,r) (fsum[r]^fsum[l-1])
#define gsum(l,r) (gsum[r]^gsum[l-1])

struct Node{
	int l,r,f,g,flp;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define f(x) tr[x].f
#define g(x) tr[x].g
#define flp(x) tr[x].flp

inline void PushUp(int x){
	f(x)=f(x<<1)^f(x<<1|1);
	g(x)=g(x<<1)^g(x<<1|1);
}
inline void Push(int x){
	flp(x)^=1;
	f(x)^=fsum(l(x),r(x));
	g(x)^=gsum(l(x),r(x));
}
inline void PushDown(int x){
	if(!flp(x)) return ;
	Push(x<<1),Push(x<<1|1);
	flp(x)=0;
}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,flp(x)=0,f(x)=g(x)=0;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Flip(int x,int l,int r){
	if(l>r) return ;
	if(l<=l(x)&&r(x)<=r) return Push(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Flip(x<<1,l,r);
	if(r>mid) Flip(x<<1|1,l,r);
	PushUp(x);
}
inline int F(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return f(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(r<=mid) return F(x<<1,l,r);
	else if(l>mid) return F(x<<1|1,l,r);
	else return F(x<<1,l,mid)^F(x<<1|1,mid+1,r);
}
inline int G(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return g(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(r<=mid) return G(x<<1,l,r);
	else if(l>mid) return G(x<<1|1,l,r);
	else return G(x<<1,l,mid)^G(x<<1|1,mid+1,r);
}

int root=1;
inline void FlipSubT(int x){
	if(dfn[root]<dfn[x]||dfn[root]>=dfn[x]+siz[x]) Flip(1,dfn[x],dfn[x]+siz[x]-1);
	else if(root==x) Flip(1,1,n);
	else{
		int y=KthAnc(root,dep[root]-dep[x]-1);
		Flip(1,1,dfn[y]-1);
		Flip(1,dfn[y]+siz[y],n);
	}
}
inline void FlipPath(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		Flip(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	Flip(1,dfn[x],dfn[y]);
}
inline int QPath(int x,int y){
	int ans=G(1,1,n);
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans^=G(1,dfn[top[x]],dfn[x]);
		ans^=F(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	ans^=G(1,dfn[x],dfn[y]);
	ans^=F(1,dfn[x],dfn[y]);
	return ans;
}

signed main(){
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}
	GetHSon(1);
	GetDFN(1,1);
	LongUp(1);
	LongDown(1,{0,1});

	int p=sec(fmx[1]),q=sec(fmx[p]);
	int len=Dist(p,q);
	int r=dep[p]>dep[q]?p:q;
	vector<int> mid={KthAnc(r,len>>1),KthAnc(r,len+1>>1)};
	if(mid.front()==mid.back()) mid.pop_back();
	auto Q=[&mid](int x)->int{
		int p=0;
		for(int q:mid) if(!p||Dist(x,q)<Dist(x,p)) p=q;
		return QPath(x,p);
	};

	for(int i=1;i<=n;i++) fsum[i]=fsum[i-1]^fir(fmx[idfn[i]]);
	for(int i=1;i<=n;i++) gsum[i]=gsum[i-1]^fir(smx[idfn[i]]);
	Build(1,1,n);
	Flip(1,1,n);

	while(m--){
		int op,x,y,r;
		cin>>op;
		if(op==1){
			cin>>x>>y>>r;
			FlipPath(x,y);
			cout<<Q(root=r)<<endl;
		}else if(op==2){
			cin>>x>>r;
			FlipSubT(x);
			cout<<Q(root=r)<<endl;
		}
	}

	return 0;
}