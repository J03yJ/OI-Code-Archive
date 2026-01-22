#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const int mod=998244353;

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

int typ,n;
vector<int> e[N];

namespace Case1{
	struct Zint{
		int x,z;
		Zint(){}
		Zint(int _x){x=_x?_x:1,z=_x?0:1;}
		Zint(int _x,int _z){*this=Zint(_x),z+=_z;}
		inline Zint friend operator +(Zint a,Zint b){
			if(a.z>b.z) return b;
			else if(a.z<b.z) return a;
			else return Zint(Add(a.x,b.x),a.z);
		}
		inline Zint friend operator -(Zint a){return Zint(Sub(0,a.x),a.z);}
		inline Zint friend operator -(Zint a,Zint b){return a+(-b);}
		inline Zint friend operator *(Zint a,Zint b){return Zint(Mul(a.x,b.x),a.z+b.z);}
		inline Zint friend operator /(Zint a,Zint b){return Zint(Mul(a.x,Inv(b.x)),a.z-b.z);}
		inline int Val(){return assert(z>=0),!z?x:0;}
	};

	int fa[N],to[N];
	inline void Init(int lim){iota(fa+1,fa+lim+1,1);}
	inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
	inline void Merge(int x,int y){fa[Find(y)]=Find(x);}
	
	Zint f[N];
	inline void Solve(){
		Init(n);
		int ans=0;
		for(int u=1;u<=n;u++){
			f[u]=Zint(1);
			for(int v:e[u]){
				if(v>u) continue ;
				Zint tmp(1);
				for(int r=Find(v);to[r];r=Find(r)){
					tmp=tmp*(f[r])/(f[r]+Zint(1));
					Merge(to[r],r);
				}
				f[Find(v)]=f[Find(v)]*tmp;
				f[u]=f[u]*(f[Find(v)]+Zint(1));
				to[Find(v)]=u;
			}
			AddAs(ans,f[u].Val());
		}
		cout<<ans<<endl;
	}
}

namespace Case2{
	struct Node{
		int lc,rc,tag;
		array<int,2> dat;
	}tr[N<<6];
	#define lc(x) tr[x].lc
	#define rc(x) tr[x].rc
	#define tag(x) tr[x].tag
	#define dat(x) tr[x].dat

	int trs[N<<6],cnt,tot;
	inline int Allc(int len){
		int x=tot?trs[tot--]:++cnt;
		tag(x)=0,dat(x)={0,len};
		return x;
	}
	inline void DeAllc(int x){
		trs[++tot]=x;
		lc(x)=rc(x)=tag(x)=0;
		dat(x)={0,0};
	}
	inline array<int,2> Calc(array<int,2> a,array<int,2> b){
		if(a[0]^b[0]) return min(a,b);
		else return {a[0],a[1]+b[1]};
	}
	inline void PushUp(int x,int L,int R){
		int mid=L+R>>1;
		dat(x)=Calc(lc(x)?dat(lc(x)):array<int,2>({0,mid-L+1}),rc(x)?dat(rc(x)):array<int,2>({0,R-mid}));
		dat(x)[0]+=tag(x);
	}
	inline void Push(int x,int k){dat(x)[0]+=k,tag(x)+=k;}
	inline void Modify(int &x,int L,int R,int l,int r,int k){
		if(!x) x=Allc(R-L+1);
		if(l<=L&&R<=r) return Push(x,k);
		int mid=L+R>>1;
		if(l<=mid) Modify(lc(x),L,mid,l,r,k);
		if(r>mid) Modify(rc(x),mid+1,R,l,r,k);
		PushUp(x,L,R);
	}
	inline array<int,2> Query(int x,int L,int R,int l,int r){
		if(!x) return {0,min(R,r)-max(L,r)+1};
		if(l<=L&&R<=r) return dat(x);
		int mid=L+R>>1;
		array<int,2> res;
		if(r<=mid) res=Query(lc(x),L,mid,l,r);
		else if(l>mid) res=Query(rc(x),mid+1,R,l,r);
		else res=Calc(Query(lc(x),L,mid,l,r),Query(rc(x),mid+1,R,l,r));
		res[0]+=tag(x);
		return res;
	}
	inline void Merge(int &x,int &y,int L,int R){
		if(!x||!y) return x=x|y,void();
		tag(x)+=tag(y);
		if(L==R){
			PushUp(x,L,R);
			DeAllc(y);
			return ;
		}
		int mid=L+R>>1;
		Merge(lc(x),lc(y),L,mid),Merge(rc(x),rc(y),mid+1,R);
		PushUp(x,L,R);
		DeAllc(y);
	}

	int f[N];
	struct Tree{
		vector<int> e[N];
		inline vector<int>& operator [](int x){return e[x];}
		int fa[N],elr[N<<1],pos[N<<1],root,ecnt;
		inline void DFS(int x){
			elr[++ecnt]=x;
			pos[x]=ecnt;
			for(int y:e[x]){
				if(fa[x]==y) continue ;
				fa[y]=x;
				DFS(y);
				elr[++ecnt]=x;
			}
		}
		int mn[N<<1][lgN],lg[N<<1];
		inline void Init(int r){
			root=r,DFS(r);
			for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
			for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
			for(int k=1;k<=lg[ecnt];k++){
				for(int i=1;i<=ecnt-(1<<k)+1;i++){
					mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
				}
			}
		}
		inline int LCA(int x,int y){
			x=pos[x],y=pos[y];
			if(x>y) swap(x,y);
			int k=lg[y-x+1];
			return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
		}
	}t0,t1;
	inline void Init(int lim){iota(f+1,f+lim+1,1);}
	inline int Find(int x){return x==f[x]?x:f[x]=Find(f[x]);}
	inline void Merge(int x,int y){f[Find(y)]=Find(x);}
	inline void GetT0(){
		Init(n);
		for(int i=1;i<=n;i++){
			for(int j:e[i]){
				if(j>i) continue ;
				t0[i].push_back(Find(j));
				Merge(i,Find(j));
			}
		}
		t0.Init(n);
	}
	inline void GetT1(){
		Init(n);
		for(int i=n;i>=1;i--){
			for(int j:e[i]){
				if(j<i) continue ;
				t1[i].push_back(Find(j));
				Merge(i,Find(j));
			}
		}
		t1.Init(1);
	}
	int fa[N],dep[N],siz[N],hson[N];
	inline void GetHSon(int x){
		siz[x]=1;
		for(int y:t1[x]){
			fa[y]=x;
			dep[y]=dep[x]+1;
			GetHSon(y);
			siz[x]+=siz[y];
			if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
		}
	}
	int dfn[N],top[N],dcnt;
	inline void GetTop(int x,int t){
		top[x]=t;
		dfn[x]=++dcnt;
		if(hson[x]) GetTop(hson[x],t);
		for(int y:t1[x]){
			if(y==hson[x]) continue ;
			GetTop(y,y);
		}
	}

	int root[N],ans;
	vector<array<int,2>> mdf[N];
	inline void AddToRoot(int &root,int x,int k){
		while(x){
			Modify(root,1,n,dfn[top[x]],dfn[x],k);
			x=fa[top[x]];
		}
	}
	inline array<int,2> QueryToRoot(int root,int x){
		array<int,2> res={INT_MAX,0};
		while(x){
			res=Calc(res,Query(root,1,n,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		return res;
	}
	inline void Work(int x){
		for(int y:t0[x]){
			Work(y);
			Merge(root[x],root[y],1,n);
		}
		Modify(root[x],1,n,dfn[x],dfn[x],-1);
		for(auto t:mdf[x]) AddToRoot(root[x],t[0],t[1]);
		array<int,2> res=QueryToRoot(root[x],x);
		if(res[0]==1) AddAs(ans,res[1]);
	}

	inline void Solve(){
		GetT0(),GetT1();
		GetHSon(1),GetTop(1,1);
		for(int i=1;i<=n;i++){
			mdf[i].push_back({i,2});
			for(int j:t0[i]) mdf[t0.LCA(i,j)].push_back({t1.LCA(i,j),-1});
			for(int j:t1[i]) mdf[t0.LCA(i,j)].push_back({t1.LCA(i,j),-1});
		}
		Work(n);
		cout<<ans<<endl;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>typ>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	if(typ==1) Case1::Solve();
	else Case2::Solve();

	return 0;
}