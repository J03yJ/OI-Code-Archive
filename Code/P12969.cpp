#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;

int n,q;
ll a[N],pre[N];

struct Node{
	int l,r,tag;
	array<int,2> dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
inline void Push(int x,int k){tag(x)+=k,dat(x)[0]+=k;}
inline void PushDown(int x){if(tag(x)) Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return dat(x)={(int)pre[l(x)],l(x)},void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r) return Push(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline array<int,2> Get(int x,int pos){
	if(l(x)==r(x)) return dat(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Get(x<<1,pos);
	else return Get(x<<1|1,pos);
}
inline int GetPoint(int p){return Get(1,p)[0]-(p>1?Get(1,p-1)[0]:0);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]--;

	partial_sum(a+1,a+n+1,pre+1);
	if(pre[n]!=-1){
		while(~(q--)) cout<<0<<' '<<0<<endl;
		return 0;
	}

	Build(1,1,n);
	cout<<1<<' '<<dat(1)[1]%n<<endl;
	while(q--){
		int i,j;
		cin>>i>>j;
		if(i>j) swap(i,j);
		i++,j++;
		Modify(1,i,j-1,GetPoint(j)-GetPoint(i));
		cout<<1<<' '<<dat(1)[1]%n<<endl;
	}

	return 0;
}