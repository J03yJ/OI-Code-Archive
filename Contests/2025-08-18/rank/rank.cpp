#include<bits/stdc++.h>

using namespace std;

ifstream fin("rank.in");
ofstream fout("rank.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using bint=__int128;
const int N=2e5+9;
const int HB=96;
const int LB=0;

int a[N],n;
int b[N],rk[N],val[N],ans[N],q;
vector<int> qry[N];

struct Node{
	int l,r;
	ll vmx,vmn,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define vmx(x) tr[x].vmx
#define vmn(x) tr[x].vmn
#define tag(x) tr[x].tag

inline void PushUp(int x){
	vmx(x)=max(vmx(x<<1),vmx(x<<1|1));
	vmn(x)=min(vmn(x<<1),vmn(x<<1|1));
}
inline void Push(int x,ll k){
	vmn(x)+=k,vmx(x)+=k,tag(x)+=k;
}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(x<<1,tag(x));
	Push(x<<1|1,tag(x));
	tag(x)=0;
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return vmx(x)=vmn(x)=val[l(x)],void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Add(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return Push(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Add(x<<1,l,r,k);
	if(r>mid) Add(x<<1|1,l,r,k);
	PushUp(x);
}
inline void LSh(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r){
		if(vmx(x)-vmx(x)/2==vmn(x)-vmn(x)/2) return Push(x,vmx(x)/2-vmx(x));
	}
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) LSh(x<<1,l,r);
	if(r>mid) LSh(x<<1|1,l,r);
	PushUp(x);
}
inline ll Query(int x,int pos){
	if(l(x)==r(x)) return vmx(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos);
}
inline int Find(int x,ll k){
	if(l(x)==r(x)) return l(x)-(k<=vmx(x));
	if(k<=vmx(x<<1)) return Find(x<<1,k);
	else return Find(x<<1|1,k);
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>b[i]>>rk[i],rk[i]=n-rk[i]+1,val[i]=b[i];
	for(int i=1;i<=q;i++) qry[rk[i]].push_back(i);

	sort(val+1,val+q+1);
	Build(1,1,q);
	for(int i=1;i<=n;i++){
		int p=Find(1,a[i]);
		if(p){
			Add(1,1,p,a[i]+1);
			LSh(1,1,p);
		}
		for(int j:qry[i]){
			int p=lower_bound(val+1,val+q+1,b[j])-val;
			ans[j]=Query(1,p)-b[j];
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}