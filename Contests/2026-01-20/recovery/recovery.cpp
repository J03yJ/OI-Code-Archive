#include<bits/stdc++.h>

using namespace std;

ifstream fin("recovery.in");
ofstream fout("recovery.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
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

struct Vec{
	int a[2];
	Vec(){memset(a,0,sizeof a);}
	Vec(int x,int y){a[0]=x,a[1]=y;}
	inline int& operator [](int p){return a[p];}
	friend inline Vec operator +(Vec A,Vec B){return Vec(Add(A[0],B[0]),Add(A[1],B[1]));}
};
struct Node{
	int l,r;
	Vec dat;
	int tag;
}tr[N<<2];

int pw[N];
inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
inline void Push(int x,int k){
	tr[x].tag+=k;
	tr[x].dat[0]=tr[x].dat[1]=Mul(pw[k-1],Add(tr[x].dat[0],tr[x].dat[1]));
}
inline void PushDown(int x){
	if(tr[x].tag){
		Push(x<<1,tr[x].tag);
		Push(x<<1|1,tr[x].tag);
		tr[x].tag=0;
	}
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].dat=Vec(0,0),tr[x].tag=0;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,Vec k){
	if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline Vec Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

int a[N],c[N],id[N],pmx[N],n;
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	int mx=0;
	vector<int> p;
	for(int i=1;i<=n;i++){
		mx=max(mx,a[i]);
		if(a[i]==mx) p.push_back(i),c[i]=1;
		else c[i]=0;
	}
	p.push_back(n+1);
	for(int i=0;i+1<p.size();i++){
		for(int j=p[i];j+1<p[i+1];j++){
			swap(a[j],a[j+1]);
			swap(c[j],c[j+1]);
		}
	}
	for(int i=1;i<=n;i++){
		id[a[i]]=i;
		pmx[i]=max(pmx[i-1],a[i]);
	}
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=Mul(2,pw[i-1]);

	Build(1,0,n+1);
	Set(1,n+1,{1,0});
	for(int i=n,cur=0;i>=1;i--){
		if(c[id[i]]){
			cur=pmx[id[i]-1];
			Push(1,1);
		}else{
			Vec v=Query(1,id[i],id[i]),u=Query(1,id[i],n+1);
			if(i<=cur) AddAs(v[0],u[0]);
			AddAs(v[1],u[1]);
			Set(1,id[i],v);
		}
	}

	cout<<Add(tr[1].dat[0],tr[1].dat[1])<<endl;
}

signed main(){
	int o,T;
	cin>>o>>T;
	while(T--) Solve();
	
	return 0;
}