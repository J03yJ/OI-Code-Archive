#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;

struct Data{
	int mx,mn,sum,h;
	Data(){}
	Data(int _mx,int _mn,int _sum,int _h){mx=_mx,mn=_mn,sum=_sum,h=_h;}
	inline friend Data operator +(Data l,Data r){
		Data res;
		res.mx=max(l.mx,r.mx+l.sum);
		res.mn=min(l.mn,r.mn+l.sum);
		res.sum=l.sum+r.sum;
		res.h=max(max(l.h,r.h),r.mx+l.sum-l.mn);
		return res;
	}
};

struct Node{
	int l,r;
	Data dat;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].dat=Data(max(k,0),min(k,0),k,max(k,0)),void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline Data Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

int a[N],n,q;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build(1,1,n);
	for(int i=1;i<=n;i++) Set(1,i,a[i]);

	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x;
			cin>>x;
			Set(1,x,a[x]=-a[x]);
		}else{
			int l,r;
			cin>>l>>r;
			int ans=r-l+1;
			auto tmp=Query(1,l,r);
			ans-=max(0,-tmp.mn);
			ans-=tmp.h-tmp.sum-max(0,-tmp.mn);
			cout<<ans<<endl;
		}
	}

	return 0;
}