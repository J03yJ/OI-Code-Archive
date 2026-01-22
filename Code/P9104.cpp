#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;

int a[N],b[N],xl[N],xr[N],yl[N],yr[N],px[N],py[N],typ[N],n,m,q;
vector<int> s[N];
ll ans[N];

namespace SgT1{
	struct Node{
		int l,r,cnt,flp;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].cnt=tr[x<<1].cnt+tr[x<<1|1].cnt;}
	inline void Push(int x){tr[x].cnt=tr[x].r-tr[x].l+1-tr[x].cnt,tr[x].flp^=1;}
	inline void PushDown(int x){if(tr[x].flp) Push(x<<1),Push(x<<1|1),tr[x].flp=0;}
	inline void Build(int x,int l,int r){
		tr[x].l=l,tr[x].r=r,tr[x].cnt=tr[x].flp=0;
		if(tr[x].l==tr[x].r) return ;
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Flip(int x,int l,int r){
		if(l<=tr[x].l&&tr[x].r<=r) return Push(x);
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(l<=mid) Flip(x<<1,l,r);
		if(r>mid) Flip(x<<1|1,l,r);
		PushUp(x);
	}
	inline int Query(int x,int l,int r){
		if(l<=tr[x].l&&tr[x].r<=r) return tr[x].cnt;
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(r<=mid) return Query(x<<1,l,r);
		else if(l>mid) return Query(x<<1|1,l,r);
		else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
	}
}
namespace SgT2{
	struct Node{
		int l,r;
		ll val,sum,tag;
	}tr[N<<2];
	inline void PushUp(int x){
		tr[x].val=min(tr[x<<1].val,tr[x<<1|1].val);
		tr[x].sum=max(tr[x<<1].sum,tr[x<<1|1].sum);
	}
	inline void Push(int x,ll k){tr[x].sum+=k,tr[x].tag+=k;}
	inline void PushDown(int x){if(tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=0;}
	inline void Build(int x,int l,int r,vector<ll> &v,vector<ll> &s){
		tr[x].l=l,tr[x].r=r,tr[x].tag=0;
		if(tr[x].l==tr[x].r) return tr[x].val=v[tr[x].l],tr[x].sum=s[tr[x].l],void();
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid,v,s),Build(x<<1|1,mid+1,r,v,s);
		PushUp(x);
	}
	inline void ModifyV(int x,int pos,ll k){
		if(tr[x].l==tr[x].r) return tr[x].val+=k,void();
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) ModifyV(x<<1,pos,k);
		else ModifyV(x<<1|1,pos,k);
		PushUp(x);
	}
	inline void ModifyS(int x,int l,int r,ll k){
		if(l>r) return ;
		if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(l<=mid) ModifyS(x<<1,l,r,k);
		if(r>mid) ModifyS(x<<1|1,l,r,k);
		PushUp(x);
	}
	inline int LowerBound(int x,ll k){
		if(tr[x].l==tr[x].r) return tr[x].l+(tr[x].val>k);
		PushDown(x);
		if(tr[x<<1].val<=k) return LowerBound(x<<1,k);
		else return LowerBound(x<<1|1,k);
	}
	inline void Print(int x){
		if(tr[x].l==tr[x].r) return cout<<tr[x].l<<'/'<<tr[x].val<<'|'<<tr[x].sum<<' ',void();
		PushDown(x);
		Print(x<<1),Print(x<<1|1);
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m>>q;
	for(int i=1;i<=m;i++) cin>>xl[i]>>yl[i]>>xr[i]>>yr[i];
	for(int i=1;i<=q;i++) cin>>px[i]>>py[i],s[px[i]].push_back(i);

	vector<array<int,3>> seg;
	for(int i=1;i<=m;i++){
		seg.push_back({xl[i],yl[i],yr[i]});
		seg.push_back({xr[i]+1,yl[i],yr[i]});
	}
	sort(seg.begin(),seg.end());
	SgT1::Build(1,1,n);
	for(int i=1,j=0;i<=n;i++){
		while(j<seg.size()&&seg[j][0]<=i) SgT1::Flip(1,seg[j][1],seg[j][2]),j++;
		a[i]=SgT1::Query(1,1,n);
		for(int k:s[i]) typ[k]=SgT1::Query(1,py[k],py[k]),SgT1::Flip(1,py[k],py[k]);
		for(int k:s[i]) SgT1::Flip(1,py[k],py[k]);
	}
	seg.clear();
	for(int i=1;i<=m;i++){
		seg.push_back({yl[i],xl[i],xr[i]});
		seg.push_back({yr[i]+1,xl[i],xr[i]});
	}
	sort(seg.begin(),seg.end());
	SgT1::Build(1,1,n);
	for(int i=1,j=0;i<=n;i++){
		while(j<seg.size()&&seg[j][0]<=i) SgT1::Flip(1,seg[j][1],seg[j][2]),j++;
		b[i]=n-SgT1::Query(1,1,n);
	}

	vector<ll> t(n+1,0),c(n+1,0),tmp(b,b+n+1);
	for(int i=1;i<=n;i++){
		t[0]+=a[i],c[0]++;
		if(a[i]+1<=n) c[a[i]+1]--;
	}
	sort(tmp.begin()+1,tmp.end(),greater<int>());
	for(int i=1;i<=n;i++) t[i]=t[i-1]-(c[i]+=c[i-1])+tmp[i];

	ll sum=accumulate(a+1,a+n+1,0ll);

	SgT2::Build(1,1,n,tmp,t);
	ans[0]=max(sum,SgT2::tr[1].sum);
	for(int i=1;i<=q;i++){
		if(typ[i]==0){
			int pos=SgT2::LowerBound(1,--b[py[i]])-1;
			SgT2::ModifyV(1,pos,-1);
			SgT2::ModifyS(1,pos,n,-1);
			SgT2::ModifyS(1,1,a[px[i]]++,1);
			sum++;
		}else{
			int pos=SgT2::LowerBound(1,b[py[i]]++);
			SgT2::ModifyV(1,pos,1);
			SgT2::ModifyS(1,pos,n,1);
			SgT2::ModifyS(1,1,--a[px[i]],-1);
			sum--;
		}
		ans[i]=max(sum,SgT2::tr[1].sum);
	}

	for(int i=0;i<=q;i++) cout<<1ll*n*n-ans[i]<<endl;

	return 0;
}