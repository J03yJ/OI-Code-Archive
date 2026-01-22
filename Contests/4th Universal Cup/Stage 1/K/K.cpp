#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const ll inf=1e18;

struct Node{
	int l,r;
	ll dat,atag,ctag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define atag(x) tr[x].atag
#define ctag(x) tr[x].ctag

inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
inline void PushAdd(int x,ll k){dat(x)+=k,atag(x)+=k;}
inline void PushCov(int x,ll k){dat(x)=ctag(x)=k,atag(x)=0;}
inline void PushDown(int x){
	if(~ctag(x)) PushCov(x<<1,ctag(x)),PushCov(x<<1|1,ctag(x)),ctag(x)=-1;
	if(atag(x)) PushAdd(x<<1,atag(x)),PushAdd(x<<1|1,atag(x)),atag(x)=0;
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,dat(x)=atag(x)=0,ctag(x)=-1;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void AddVal(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return PushAdd(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) AddVal(x<<1,l,r,k);
	if(r>mid) AddVal(x<<1|1,l,r,k);
	PushUp(x);
}
inline void Cover(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return PushCov(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Cover(x<<1,l,r,k);
	if(r>mid) Cover(x<<1|1,l,r,k);
	PushUp(x);
}
inline int LowerBound(int x,ll k){
	if(l(x)==r(x)) return l(x)+(dat(x)<k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(k<=dat(x<<1)) return LowerBound(x<<1,k);
	else return LowerBound(x<<1|1,k);
}
inline ll Get(int x,int pos){
	if(l(x)==r(x)) return dat(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Get(x<<1,pos);
	else return Get(x<<1|1,pos);
}
inline void Set(int x,int pos,ll k){
	if(l(x)==r(x)) return dat(x)=k,void();
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}

int a[N],ql[N],qr[N],ans[N],n,q,d;
vector<int> qry[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i],qry[qr[i]].push_back(i);

	Build(1,1,n);
	Cover(1,1,n,inf);
	for(int i=1;i<=n;i++){
		Set(1,i,d);
		int lp=LowerBound(1,a[i]);
		int rp=LowerBound(1,a[i]*2);
		if(rp<=n) AddVal(1,rp,n,-a[i]);
		if(lp<rp) Cover(1,lp,rp-1,a[i]-1);
		for(int j:qry[i]) ans[j]=Get(1,ql[j]);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}