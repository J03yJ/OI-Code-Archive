#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const ll inf=1e18;

ll k;
struct Node{
	int l,r;
	ll sum,pmin,nmin,ktag,btag,atag;
	bool cov;
	inline int Len(){return r-l+1;}
}tr[N<<2];

inline void PushUp(int x){
	tr[x].sum=tr[x<<1].sum+tr[x<<1|1].sum;
	tr[x].pmin=min(tr[x<<1].pmin,tr[x<<1|1].pmin);
	tr[x].nmin=min(tr[x<<1].nmin,tr[x<<1|1].nmin);
}
inline void PushCov(int x,ll tk,ll tb){
	tr[x].cov=1,tr[x].atag=0;
	tr[x].ktag=tk,tr[x].btag=tb;
	tr[x].sum=tb*tr[x].Len()+tk*tr[x].Len()*(tr[x].Len()-1)/2;
	tr[x].pmin=min(tb+tr[x].l*k,tb+(tr[x].Len()-1)*tk+tr[x].r*k);
	tr[x].nmin=min(tb-tr[x].l*k,tb+(tr[x].Len()-1)*tk-tr[x].r*k);
}
inline void PushAdd(int x,ll ta){
	tr[x].atag+=ta;
	tr[x].sum+=ta*tr[x].Len();
	tr[x].pmin+=ta;
	tr[x].nmin+=ta;
}
inline void PushDown(int x){
	if(tr[x].cov){
		PushCov(x<<1,tr[x].ktag,tr[x].btag);
		PushCov(x<<1|1,tr[x].ktag,tr[x].btag+tr[x].ktag*tr[x<<1].Len());
		tr[x].cov=tr[x].ktag=tr[x].btag=0;
	}
	if(tr[x].atag){
		PushAdd(x<<1,tr[x].atag);
		PushAdd(x<<1|1,tr[x].atag);
		tr[x].atag=0;
	}
}

int a[N],n,q;
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].cov=tr[x].ktag=tr[x].btag=0;
	if(tr[x].l==tr[x].r){
		tr[x].sum=a[tr[x].l];
		tr[x].pmin=a[tr[x].l]+tr[x].l*k;
		tr[x].nmin=a[tr[x].l]-tr[x].l*k;
		return ;
	}
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void RAdd(int x,int l,int r,ll k){
	if(l<=tr[x].l&&tr[x].r<=r) return PushAdd(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) RAdd(x<<1,l,r,k);
	if(r>mid) RAdd(x<<1|1,l,r,k);
	PushUp(x);
}
inline void RCover(int x,int l,int r,ll k,ll b){
	if(l<=tr[x].l&&tr[x].r<=r) return PushCov(x,k,b);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) RCover(x<<1,l,r,k,b);
	else if(l>mid) RCover(x<<1|1,l,r,k,b);
	else{
		RCover(x<<1,l,mid,k,b);
		RCover(x<<1|1,mid+1,r,k,b+k*(mid-l+1));
	}
	PushUp(x);
}
inline ll PMin(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].pmin;
	ll ans=inf;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) ans=min(ans,PMin(x<<1,l,r));
	if(r>mid) ans=min(ans,PMin(x<<1|1,l,r));
	return ans;
}
inline ll NMin(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].nmin;
	ll ans=inf;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) ans=min(ans,NMin(x<<1,l,r));
	if(r>mid) ans=min(ans,NMin(x<<1|1,l,r));
	return ans;
}
inline int FindL(int x,int l,int r,ll t){
	if(tr[x].nmin>t) return r+1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return FindL(x<<1,l,r,t);
	else if(l>mid) return FindL(x<<1|1,l,r,t);
	else{
		int p=FindL(x<<1,l,r,t);
		return p==r+1?FindL(x<<1|1,l,r,t):p;
	}
}
inline int FindR(int x,int l,int r,ll t){
	if(tr[x].pmin>t) return l-1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return FindR(x<<1,l,r,t);
	else if(l>mid) return FindR(x<<1|1,l,r,t);
	else{
		int p=FindR(x<<1|1,l,r,t);
		return p==l-1?FindR(x<<1,l,r,t):p;
	}
}
inline ll Sum(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].sum;
	ll ans=0;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) ans+=Sum(x<<1,l,r);
	if(r>mid) ans+=Sum(x<<1|1,l,r);
	return ans;
}

struct Seg{
	int l,r;
	Seg(){}
	Seg(int _l,int _r){l=_l,r=_r;}
	inline friend bool operator <(Seg x,Seg y){return x.l<y.l;}
};
multiset<Seg> o;
inline auto Split(int p){
	if(p>n) return o.end();
	auto it=o.lower_bound(Seg(p,0));
	if(it!=o.end()&&it->l==p) return it;
	it--;
	int l=it->l,r=it->r;
	o.erase(it);
	o.insert(Seg(l,p-1));
	return o.insert(Seg(p,r));
}
inline void Assign(int l,int r){
	auto rt=Split(r+1),lt=Split(l);
	ll cur=inf;
	for(auto it=lt;it!=rt;it++){
		int p=FindL(1,it->l,it->r,cur);
		if(p>it->l) RCover(1,it->l,p-1,k,cur+it->l*k);
		cur=min(cur,NMin(1,it->l,it->r));
	}
	cur=inf;
	for(auto it=prev(rt);;it--){
		int p=FindR(1,it->l,it->r,cur);
		if(p<it->r) RCover(1,p+1,it->r,-k,cur-(p+1)*k);
		cur=min(cur,PMin(1,it->l,it->r));
		if(it==lt) break ;
	}
	o.erase(lt,rt);
	o.insert(Seg(l,r));
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	Build(1,1,n);
	for(int i=1;i<=n;i++) o.insert(Seg{i,i});

	while(q--){
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1) cout<<Sum(1,l,r)<<endl;
		else if(op==2){
			int c;
			cin>>c;
			RAdd(1,l,r,c);
			Split(r+1),Split(l);
		}else Assign(l,r);
	}

	return 0;
}