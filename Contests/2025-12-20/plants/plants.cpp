#include<bits/stdc++.h>
#include"plants.h"

using namespace std;

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const int inf=1e9+7;

namespace Seg1{
	struct Data{
		int mn,l,r,p,len;
		Data(){}
		Data(int _mn,int _l,int _r,int _p,int _len){
			mn=_mn,l=_l,r=_r,p=_p,len=_len;
		}
		inline friend Data operator +(Data x,Data y){
			if(x.mn!=y.mn) return x.mn<y.mn?x:y;
			Data z(x.mn,x.l,y.r,y.l,y.l-x.r);
			if(x.len>z.len) z.len=x.len,z.p=x.p;
			if(y.len>z.len) z.len=y.len,z.p=y.p;
			return z;
		}
	};
	struct Node{
		int l,r,tag;
		Data dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
	inline void Push(int x,int k){tr[x].dat.mn+=k,tr[x].tag+=k;}
	inline void PushDown(int x){
		if(!tr[x].tag) return ;
		Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag);
		tr[x].tag=0;
	}
	inline void Build(int x,int l,int r,vector<int> &v){
		tr[x].l=l,tr[x].r=r,tr[x].tag=0;
		if(tr[x].l==tr[x].r) return tr[x].dat=Data(v[l],l,l,-1,-1),void();
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid,v),Build(x<<1|1,mid+1,r,v);
		PushUp(x);
	}
	inline void Modify(int x,int l,int r,int k){
		if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(l<=mid) Modify(x<<1,l,r,k);
		if(r>mid) Modify(x<<1|1,l,r,k);
		PushUp(x);
	}
}
struct Seg2{
	struct Node{
		int l,r,dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
	inline void Build(int x,int l,int r,int k){
		tr[x].l=l,tr[x].r=r;
		if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid,k),Build(x<<1|1,mid+1,r,k);
		PushUp(x);
	}
	inline void Set(int x,int pos,int k){
		if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) Set(x<<1,pos,k);
		else Set(x<<1|1,pos,k);
		PushUp(x);
	}
	inline int Query(int x,int l,int r){
		if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
		int mid=tr[x].l+tr[x].r>>1,ans=-inf;
		if(l<=mid) ans=max(ans,Query(x<<1,l,r));
		if(r>mid) ans=max(ans,Query(x<<1|1,l,r));
		return ans;
	}
}Tmx,Tmn;

vector<int> a,ia;
int lp[lgN][N],rp[lgN][N],n,k;
ll len[lgN][N],ren[lgN][N];
void init(int _k,vector<int> r){
	n=r.size(),k=_k;
	a.resize(n),ia.resize(n);

	Seg1::Build(1,0,n-1,r);
	for(int i=n-1;~i;i--){
		Seg1::Data x=Seg1::tr[1].dat;
		x=x+Seg1::Data(x.mn,x.l+n,x.r+n,x.p+n,x.len);
		int p=x.p%n;
		a[p]=i,ia[i]=p;
		Seg1::Modify(1,p,p,inf);
		if(p-k+1>=0) Seg1::Modify(1,p-k+1,p,-1);
		else Seg1::Modify(1,0,p,-1),Seg1::Modify(1,n+p-k+1,n-1,-1);
	}

	Tmx.Build(1,0,n-1,-1);
	for(int i=0;i<n;i++){
		if(ia[i]+k-1<n) lp[0][i]=Tmx.Query(1,ia[i],ia[i]+k-1);
		else lp[0][i]=max(Tmx.Query(1,ia[i],n-1),Tmx.Query(1,0,ia[i]+k-1-n));
		Tmx.Set(1,ia[i],i);
	}
	Tmn.Build(1,0,n-1,-n);
	for(int i=n-1;~i;i--){
		if(ia[i]+k-1<n) rp[0][i]=-Tmn.Query(1,ia[i],ia[i]+k-1);
		else rp[0][i]=-max(Tmn.Query(1,ia[i],n-1),Tmn.Query(1,0,ia[i]+k-1-n));
		Tmn.Set(1,ia[i],-i);
	}

	for(int i=0;i<n;i++){
		if(lp[0][i]>=0) len[0][i]=(ia[lp[0][i]]-ia[i]+n)%n;
		if(rp[0][i]<n) ren[0][i]=(ia[rp[0][i]]-ia[i]+n)%n;
	}
	for(int k=1;k<=__lg(n);k++){
		for(int i=0;i<n;i++){
			if(lp[k-1][i]>=0){
				lp[k][i]=lp[k-1][lp[k-1][i]];
				len[k][i]=len[k-1][i]+len[k-1][lp[k-1][i]];
			}else lp[k][i]=-1;
			if(rp[k-1][i]<n){
				rp[k][i]=rp[k-1][rp[k-1][i]];
				ren[k][i]=ren[k-1][i]+ren[k-1][rp[k-1][i]];
			}else rp[k][i]=n;
		}
	}
}
inline ll LApr(int x,int y){
	ll sum=0;
	for(int k=__lg(n);~k;k--){
		if(lp[k][x]>=y) sum+=len[k][x],x=lp[k][x];
	}
	return sum+k-1;
}
inline ll RApr(int x,int y){
	ll sum=0;
	for(int k=__lg(n);~k;k--){
		if(rp[k][x]<=y) sum+=ren[k][x],x=rp[k][x];
	}
	return sum+k-1;
}
int compare_plants(int x,int y){
	int f=1;
	if(a[x]<a[y]) swap(x,y),f=-1;
	if(LApr(a[x],a[y])>=(y-x+n)%n||RApr(a[y],a[x])>=(x-y+n)%n) return f;
	else return 0;
}