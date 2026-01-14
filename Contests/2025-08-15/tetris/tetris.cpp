#include<bits/stdc++.h>

using namespace std;

ifstream fin("tetris.in");
ofstream fout("tetris.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=6e5+9;
const int inf=1e9+7;

namespace SgT{
	struct Node{
		int l,r;
		ll tag;
		array<ll,4> dat;
	}tr[N<<2];
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define dat(x) tr[x].dat
	#define tag(x) tr[x].tag

	inline array<ll,4> Merge(array<ll,4> x,array<ll,4> y){
		if(x[0]>y[0]) return x;
		else if(y[0]>x[0]) return y;
		else{
			if(x[2]+1==y[1]) return {x[0],x[1],y[2],x[3]+y[3]};
			else return {x[0],x[1],y[2],x[3]+y[3]+1};
		}
	}

	inline void PushUp(int x){dat(x)=Merge(dat(x<<1),dat(x<<1|1));}
	inline void Push(int x,ll k){tag(x)=k,dat(x)={k,l(x),r(x),0};}
	inline void PushDown(int x){if(~tag(x)) Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=-1;}
	inline void Build(int x,int l,int r){
		l(x)=l,r(x)=r,dat(x)={0,l(x),r(x),0},tag(x)=-1;
		if(l(x)==r(x)) return ;
		int mid=l(x)+r(x)>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Assign(int x,int l,int r,ll k){
		if(l<=l(x)&&r(x)<=r) return Push(x,k);
		int mid=l(x)+r(x)>>1;
		PushDown(x);
		if(l<=mid) Assign(x<<1,l,r,k);
		if(r>mid) Assign(x<<1|1,l,r,k);
		PushUp(x);
	}
	inline array<ll,4> Query(int x,int l,int r){
		if(l<=l(x)&&r(x)<=r) return dat(x);
		int mid=l(x)+r(x)>>1;
		PushDown(x);
		if(r<=mid) return Query(x<<1,l,r);
		else if(l>mid) return Query(x<<1|1,l,r);
		else return Merge(Query(x<<1,l,mid),Query(x<<1|1,mid+1,r));
	}
}

int bl[N],br[N],bh[N],p[N],n;
ll bs[N];

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>bl[i]>>br[i]>>bh[i];

		int ans=0;
		SgT::Build(1,-3e5,3e5);
		for(int i=1;i<=n;i++){
			br[i]--;
			if(bl[i]>br[i]) continue ;
			if(!bh[i]) continue ;
			array<ll,4> tmp=SgT::Query(1,bl[i],br[i]);
			SgT::Assign(1,bl[i],br[i],(bs[i]=tmp[0])+bh[i]);
		}
		iota(p+1,p+n+1,1);
		sort(p+1,p+n+1,[](int i,int j){return bs[i]<bs[j];});
		SgT::Build(1,-3e5,3e5);
		for(int t=1;t<=n;t++){
			int i=p[t];
			if(bl[i]>br[i]) continue ;
			if(!bh[i]) continue ;
			array<ll,4> tmp=SgT::Query(1,bl[i],br[i]);
			ans+=tmp[3];
			if(tmp[1]!=bl[i]&&bl[i]>0){
				if(SgT::Query(1,bl[i]-1,bl[i]-1)[0]>=tmp[0]) ans++;
			}
			if(tmp[2]!=br[i]&&br[i]<2e5){
				if(SgT::Query(1,br[i]+1,br[i]+1)[0]>=tmp[0]) ans++;
			}
			SgT::Assign(1,bl[i],br[i],tmp[0]+bh[i]);
		}

		cout<<ans<<endl;

	}

	return 0;
}