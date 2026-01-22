#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

struct Node{
	int l,r;
	ll dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
inline void Push(int x,ll k){dat(x)+=k,tag(x)+=k;}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(x<<1,tag(x)),Push(x<<1|1,tag(x));
	tag(x)=0;
}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return Push(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline int Find(int x){
	if(l(x)==r(x)) return l(x)+(dat(x)>0);
	PushDown(x);
	if(dat(x<<1)<=0) return Find(x<<1);
	else return Find(x<<1|1);
}

int n,q,len;
ll a[N],t[N],u,r;
inline void Add(int x,ll k){while(x<=n) t[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=t[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
inline ll Query(){return Ask(min(n,Find(1)+len-1));}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>u>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	len=min(u,ll(n));
	Build(1,1,n-len+1);
	for(int i=1;i<=n;i++){
		int l=max(2,i-len+1),r=min(i,n-len+1);
		Modify(1,l,r,a[i]);
		Add(i,a[i]);
	}
	Modify(1,1,n,-r);
	Modify(1,1,1,r+1);

	cout<<Query()<<endl;

	cin>>q;
	while(q--){
		int i;ll k;
		cin>>i>>k;
		int l=max(2,i-len+1),r=min(i,n-len+1);
		Modify(1,l,r,k-a[i]);
		Add(i,k-a[i]);
		a[i]=k;
		cout<<Query()<<endl;
	}

	return 0;
}