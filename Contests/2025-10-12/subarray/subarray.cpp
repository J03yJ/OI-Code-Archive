#include<bits/stdc++.h>

using namespace std;

ifstream fin("subarray.in");
ofstream fout("subarray.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using bint=__int128;
const ll mod=114514191981000001;
const ll base=19260817;
const int N=1e5+9;
const int SQ=4e2+9;
const int CB=5e1+9;

inline void AddAs(ll &x,ll y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(ll &x,ll y){if((x-=y)<0) x+=mod;}
inline void MulAs(ll &x,ll y){x=bint(x)*y%mod;}
inline ll Add(ll x,ll y){if((x+=y)>=mod) x-=mod;return x;}
inline ll Sub(ll x,ll y){if((x-=y)<0) x+=mod;return x;}
inline ll Mul(ll x,ll y){return bint(x)*y%mod;}
inline ll QPow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

ll h[N];
int a[N],ia[N],oi[N],oj[N],len[N],ans[N],n,m,q,B,T;
vector<vector<int>> b;

ll pw[N],ipw[N];
inline void InitBase(int lim){
	const ll ibase=Inv(base);
	pw[0]=ipw[0]=1;
	for(int i=1;i<=lim;i++){
		pw[i]=Mul(pw[i-1],base);
		ipw[i]=Mul(ipw[i-1],ibase);
	}
}
inline ll Hash(vector<int> &v){
	ll res=0;
	for(int i=0;i<v.size();i++) AddAs(res,Mul(v[i],pw[i]));
	return res;
}

ll v[N],pv[N],bpv[SQ];
int blk[N],L[SQ],R[SQ];
inline void InitBlock(){
	B=ceil(sqrt(n));
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;
	iota(v+1,v+n+1,1);
	for(int i=1;i<=n;i++) pv[i]=Add(i>L[blk[i]]?pv[i-1]:0,Mul(pw[i-1],v[i]));
	for(int i=1;i<=blk[n];i++) bpv[i]=Add(bpv[i-1],pv[R[i]]);
}
inline void Modify(int x,ll k){
	ll dlt=Mul(pw[x-1],Sub(k,v[x]));
	for(int i=x;i<=R[blk[x]];i++) AddAs(pv[i],dlt);
	for(int i=blk[x];i<=blk[n];i++) AddAs(bpv[i],dlt);
	v[x]=k;
}
inline ll Query(int x){return x?Add(bpv[blk[x]-1],pv[x]):0;}
inline ll QHash(int l,int r){return Mul(ipw[l-1],Sub(Query(r),Query(l-1)));}

const int S=3301;
struct Table{
	vector<array<ll,2>> t[S];
	inline ll& Get(ll key){
		ll x=key%S;
		for(auto &p:t[x]) if(p[0]==key) return p[1];
		t[x].push_back({key,0});
		return t[x].back()[1];
	}
	inline ll Find(ll key){
		ll x=key%S;
		for(auto &p:t[x]) if(p[0]==key) return p[1];
		return 0;
	}
};

Table id[CB];

int fa[N];
inline void InitDSU(){iota(fa+1,fa+q+1,1);}
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	cin>>n>>m>>q;
	b.resize(q+1);
	iota(a+1,a+n+1,1);
	iota(ia+1,ia+n+1,1);
	for(int i=1;i<=m;i++) cin>>oi[i]>>oj[i];
	for(int i=1;i<=q;i++){
		cin>>len[i];
		b[i].resize(len[i],0);
		for(int &x:b[i]) cin>>x;
		ans[i]=-1;
	}

	InitDSU();
	InitBase(n);
	T=ceil(cbrt(n)/2);
	vector<int> qry;
	for(int i=1;i<=q;i++){
		h[i]=Hash(b[i]);
		if(len[i]<=T){
			if(id[len[i]].Find(h[i])) Merge(id[len[i]].Find(h[i]),i);
			else id[len[i]].Get(h[i])=i;
		}else qry.push_back(i);
	}

	InitBlock();
	for(int x:qry){
		if(~ans[x]) continue ;
		if(ia[b[x].back()]-ia[b[x].front()]+1!=len[x]) continue ;
		if(QHash(ia[b[x].front()],ia[b[x].back()])==h[x]) ans[x]=0;
	}
	for(int len=1;len<=T;len++){
		for(int i=1;i<=n-len+1;i++){
			int x=id[len].Find(QHash(i,i+len-1));
			if(x&&!~ans[x]) ans[x]=0;
		}
	}
	for(int i=1;i<=m;i++){
		int tmp=a[oi[i]]^a[oj[i]];
		for(int p:{oi[i],oj[i]}){
			int trg=tmp^a[p];
			Modify(p,a[p]=trg);
			ia[trg]=p;
			for(int len=1;len<=min(T,n-p+1);len++){
				for(int j=max(1,p-len+1);j<=p;j++){
					int x=id[len].Find(QHash(j,j+len-1));
					if(x&&!~ans[x]) ans[x]=i;
				}
			}
		}
		for(int x:qry){
			if(~ans[x]) continue ;
			if(ia[b[x].back()]-ia[b[x].front()]+1!=len[x]) continue ;
			if(QHash(ia[b[x].front()],ia[b[x].back()])==h[x]) ans[x]=i;
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[Find(i)]<<endl;

	return 0;
}