#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;
const int inf=1e9+7;

int a[N],n,q;

struct Node{
	int l,r,mx;
	ll sum,d;
	inline int Len(){return r-l+1;}
}tr[N<<2];
inline void PushUp(int x){tr[x].mx=max(tr[x<<1].mx,tr[x<<1|1].mx);}
inline void Push(int x,ll b,ll k){tr[x].sum+=b,tr[x].d+=k;}
inline void PushDown(int x){
	if(!tr[x].sum&&!tr[x].d) return ;
	Push(x<<1,tr[x].sum,tr[x].d);
	Push(x<<1|1,tr[x].sum+tr[x<<1].Len()*tr[x].d,tr[x].d);
	tr[x].sum=tr[x].d=0;
}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].mx=k,void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll b,ll k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,b,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) Modify(x<<1,l,r,b,k);
	else if(l>mid) Modify(x<<1|1,l,r,b,k);
	else{
		Modify(x<<1,l,mid,b,k);
		Modify(x<<1|1,mid+1,r,b+(mid-l+1)*k,k);
	}
	PushUp(x);
}
inline ll Query(int x,int pos){
	if(tr[x].l==tr[x].r) return tr[x].sum;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos);
}
inline int LFind(int x,int l,int r,int k){
	if(tr[x].mx<=k) return r+1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return LFind(x<<1,l,r,k);
	else if(l>mid) return LFind(x<<1|1,l,r,k);
	else{
		int res=LFind(x<<1,l,r,k);
		return res>r?LFind(x<<1|1,l,r,k):res;
	}
}
inline int RFind(int x,int l,int r,int k){
	if(tr[x].mx<=k) return l-1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return RFind(x<<1,l,r,k);
	else if(l>mid) return RFind(x<<1|1,l,r,k);
	else{
		int res=RFind(x<<1|1,l,r,k);
		return res<l?RFind(x<<1,l,r,k):res;
	}
}
inline void Insert(int l,int k){if(l>0) Modify(1,1,l,1ll*k*l,-k);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build(1,1,n);
	Insert(n,inf);
	Insert(n,-(inf-*max_element(a+1,a+n+1)));
	for(int i=1;i<=n;i++) Set(1,i,a[i]);
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int lst=0;
		while(stk.size()&&a[i]>a[stk.back()]){
			Insert(i-stk.back()-1,-(a[stk.back()]-lst));
			lst=a[stk.back()];
			stk.pop_back();
		}
		Insert(i-(stk.size()?stk.back():0)-1,-(a[i]-lst));
		stk.push_back(i);
	}
	int lst=0;
	while(stk.size()){
		Insert(n-stk.back(),-(a[stk.back()]-lst));
		lst=a[stk.back()];
		stk.pop_back();
	}

	while(q--){
		char op;int k;
		cin>>op>>k;
		if(op=='?'){
			cout<<Query(1,k)<<endl;
		}else if(op=='+'){
			int lp=RFind(1,1,k,a[k]),rp=LFind(1,k,n,a[k]);
			Insert(rp-lp-1,1);
			Insert(rp-k-1,-1);
			Insert(k-lp-1,-1);
			Set(1,k,++a[k]);
		}
	}

	return 0;
}