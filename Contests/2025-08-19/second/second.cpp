#include<bits/stdc++.h>

using namespace std;

ifstream fin("second.in");
ofstream fout("second.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const int T=4e2+9;

ll ans[N];
int a[N],b[N],n;
int op[N],qu[N],qv[N],q;
vector<int> e[N];

struct Blk{
	int blk[N],L[N],R[N],a[N],b[N],ia[N],ib[N],B;
	ll w[N],pre[T][T];
	inline void Init(){
		B=sqrt(n);
		for(int i=1;i<=n;i++) ia[a[i]]=ib[b[i]]=i;
		for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
		for(int i=1;i<=n;i++) R[blk[i]]=i;
		for(int i=n;i>=1;i--) L[blk[i]]=i;
		for(int i=1;i<=n;i++) w[i]=0;
		for(int i=1;i<=blk[n];i++){
			for(int j=1;j<=blk[n];j++) pre[i][j]=0;
		}
	}
	inline void Insert(int x,ll k){
		w[x]+=k;
		for(int i=blk[a[x]];i<=blk[n];i++) pre[blk[b[x]]][i]+=k;
	}
	inline ll Query(int x,int y){
		if(!x||!y) return 0;
		ll ans=0;
		for(int i=1;i<blk[y];i++) ans+=pre[i][blk[x]-1];
		for(int i=L[blk[y]];i<=y;i++) if(a[ib[i]]<=R[blk[x]-1]) ans+=w[ib[i]];
		for(int i=L[blk[x]];i<=x;i++) if(b[ia[i]]<=y) ans+=w[ia[i]];
		return ans;
	}
	inline ll Query(ll sx,ll sy,ll tx,ll ty){
		return Query(tx,ty)-Query(tx,sy-1)-Query(sx-1,ty)+Query(sx-1,sy-1);
	}
}b1,b2;
inline void BInit(){
	for(int i=1;i<=n;i++){
		b1.a[i]=a[i],b1.b[i]=n-b[i]+1;
		b2.a[i]=n-a[i]+1,b2.b[i]=b[i];
	}
	b1.Init(),b2.Init();
}
inline void BInsert(int x,ll k){
	b1.Insert(x,k);
	b2.Insert(x,k);
}
inline ll BQuery(int x,int y){
	return b1.Query(x-1,n-y)+b2.Query(n-x,y-1);
}

int anc[N][lgN];
int siz[N],fa[N],dfn[N],idfn[N],dep[N],dcnt;
inline void GetInfo(int x){
	siz[x]=1;
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetInfo(y);
		siz[x]+=siz[y];
	}
}
inline void InitLCA(){
	for(int i=1;i<=n;i++) anc[i][0]=fa[i];
	for(int k=1;k<lgN;k++){
		for(int i=1;i<=n;i++) anc[i][k]=anc[anc[i][k-1]][k-1];
	}
}
inline int LCA(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int k=lgN-1;~k;k--) if(dep[anc[u][k]]>=dep[v]) u=anc[u][k];
	if(u==v) return u;
	for(int k=lgN-1;~k;k--) if(anc[u][k]!=anc[v][k]) u=anc[u][k],v=anc[v][k];
	return anc[u][0];
}

vector<tuple<ll*,int,int,ll>> opt[N],ope[N];
ll tw[N],pw[N],sub[N],usub[N],cnt[N];
inline void GetPointW(int x,ll s){
	tw[x]=BQuery(a[x],b[x]);
	pw[x]=s+tw[x]*(siz[x]-1);
	cnt[x]=1ll*siz[x]*(siz[x]-1);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		BInsert(x,siz[x]-siz[y]);
		GetPointW(y,s+tw[x]*(siz[x]-siz[y]));
		BInsert(x,siz[y]-siz[x]);
		cnt[x]-=1ll*siz[y]*(siz[y]-1);
	}
	BInsert(x,siz[x]-1);
	for(auto t:opt[x]){
		ll *trg=get<0>(t),w=get<3>(t);
		int x=get<1>(t),y=get<2>(t);
		*trg+=w*BQuery(x,y);
	}
	BInsert(x,1-siz[x]);
	for(auto t:ope[x]){
		ll *trg=get<0>(t),w=get<3>(t);
		int x=get<1>(t),y=get<2>(t);
		*trg+=w*BQuery(x,y);
	}
}

vector<tuple<ll*,int,int,ll>> opr[N];

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1) cin>>qu[i];
		else cin>>qu[i]>>qv[i];
	}

	dep[1]=1,GetInfo(1);
	InitLCA();
	
	BInit();
	for(int i=1;i<=q;i++){
		if(op[i]!=2) continue ;
		int lca=LCA(qu[i],qv[i]);
		opt[qu[i]].push_back(make_tuple(&ans[i],a[lca],b[lca],2));
		opt[qv[i]].push_back(make_tuple(&ans[i],a[lca],b[lca],2));
		ope[lca].push_back(make_tuple(&ans[i],a[lca],b[lca],-2));
	}
	GetPointW(1,0);
	ans[0]=accumulate(pw+1,pw+n+1,0ll);
	
	for(int i=1;i<=n;i++){
		opr[dfn[i]-1].push_back(make_tuple(&sub[i],a[i],b[i],-1));
		opr[dfn[i]+siz[i]-1].push_back(make_tuple(&sub[i],a[i],b[i],1));
		opr[dfn[i]-1].push_back(make_tuple(&usub[i],a[fa[i]],b[fa[i]],-1));
		opr[dfn[i]+siz[i]-1].push_back(make_tuple(&usub[i],a[fa[i]],b[fa[i]],1));
	}
	for(int i=1;i<=n;i++){
		BInsert(idfn[i],cnt[idfn[i]]);
		for(auto t:opr[i]){
			ll *trg=get<0>(t),w=get<3>(t);
			int x=get<1>(t),y=get<2>(t);
			*trg+=w*BQuery(x,y);
		}
	}
	for(int i=1;i<=n;i++){
		sub[idfn[i]]+=siz[idfn[i]]*tw[idfn[i]];
		usub[idfn[i]]+=siz[idfn[i]]*tw[fa[idfn[i]]];
		sub[idfn[i]]+=sub[fa[idfn[i]]];
		usub[idfn[i]]+=usub[fa[idfn[i]]];
	}
	for(int i=1;i<=q;i++){
		if(op[i]==1){
			ans[i]+=ans[0];
			ans[i]+=-pw[qu[i]]+tw[qu[i]]-sub[qu[i]]+usub[qu[i]];
		}else if(op[i]==2){
			ans[i]+=ans[0];
			ans[i]+=-pw[qu[i]]+tw[qu[i]]-sub[qu[i]]+usub[qu[i]];
			ans[i]+=-pw[qv[i]]+tw[qv[i]]-sub[qv[i]]+usub[qv[i]];
		}
	}

	for(int i=0;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}