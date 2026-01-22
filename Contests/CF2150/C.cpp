#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const ll inf=1e18;

int v[N],a[N],b[N],ia[N],ib[N],n;

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
inline void PushA(int x,ll k){atag(x)+=k,dat(x)+=k;}
inline void PushC(int x,ll k){ctag(x)=dat(x)=k,atag(x)=0;}
inline void PushDownA(int x){if(atag(x)) PushA(x<<1,atag(x)),PushA(x<<1|1,atag(x)),atag(x)=0;}
inline void PushDownC(int x){if(ctag(x)!=-inf) PushC(x<<1,ctag(x)),PushC(x<<1|1,ctag(x)),ctag(x)=-inf;}
inline void PushDown(int x){PushDownC(x),PushDownA(x);}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,atag(x)=dat(x)=0,ctag(x)=-inf;
	if(l(x)==r(x)) return dat(x)=0,void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Add(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return PushA(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Add(x<<1,l,r,k);
	if(r>mid) Add(x<<1|1,l,r,k);
	PushUp(x);
}
inline void Cover(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return PushC(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Cover(x<<1,l,r,k);
	if(r>mid) Cover(x<<1|1,l,r,k);
	PushUp(x);
}
inline ll Max(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(r<=mid) return Max(x<<1,l,r);
	else if(l>mid) return Max(x<<1|1,l,r);
	else return max(Max(x<<1,l,r),Max(x<<1|1,l,r));
}
inline int UpperBound(int x,ll k){
	if(l(x)==r(x)) return l(x)+(dat(x)<=k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(dat(x<<1)>k) return UpperBound(x<<1,k);
	else return UpperBound(x<<1|1,k);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>v[i];
		for(int i=1;i<=n;i++) cin>>a[i],ia[a[i]]=i;
		for(int i=1;i<=n;i++) cin>>b[i],ib[b[i]]=i;

		Build(1,1,n);
		for(int i=1;i<=n;i++){
			int x=b[i];
			ll pre=ia[x]>1?Max(1,1,ia[x]-1):0;
			int pos=max(ia[x]-1,UpperBound(1,pre-v[x]));
			if(pos>ia[x]) Cover(1,ia[x],pos-1,pre);
			if(pos<=n) Add(1,pos,n,v[x]);
		}

		cout<<dat(1)<<endl;
	}

	return 0;
}