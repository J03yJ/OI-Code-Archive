#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;
const int inf=1e9+7;

vector<int> b[N];
int a[N],ql[N],qr[N],ans[N],p[N],ip[N],n,q;

multiset<array<int,2>> ls,rs;
namespace Fenw{
	int tr[N];
	inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
	inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}
}
namespace SgT{
	struct Node{
		int tag;
		array<int,2> dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
	inline void Push(int x,int k){tr[x].dat[0]+=k,tr[x].tag+=k;}
	inline void PushDown(int x){
		if(tr[x].tag){
			Push(x<<1,tr[x].tag);
			Push(x<<1|1,tr[x].tag);
			tr[x].tag=0;
		}
	}
	inline void Build(int x,int L,int R){
		if(L==R) return tr[x].dat={-inf,L},void();
		int mid=L+R>>1;
		Build(x<<1,L,mid),Build(x<<1|1,mid+1,R);
		PushUp(x);
	}
	inline void Modify(int x,int L,int R,int l,int r,int k){
		if(l>r) return ;
		if(l<=L&&R<=r) return Push(x,k);
		PushDown(x);
		int mid=L+R>>1;
		if(l<=mid) Modify(x<<1,L,mid,l,r,k);
		if(r>mid) Modify(x<<1|1,mid+1,R,l,r,k);
		PushUp(x);
	}
	inline void Set(int x,int L,int R,int pos,array<int,2> k){
		if(L==R) return tr[x].dat=k,void();
		PushDown(x);
		int mid=L+R>>1;
		if(pos<=mid) Set(x<<1,L,mid,pos,k);
		else Set(x<<1|1,mid+1,R,pos,k);
		PushUp(x);
	}
}
namespace TgS{
	struct Data{
		int a,b,p;
		Data(){}
		Data(int _a,int _b,int _p){a=_a,b=_b,p=_p;}
		inline friend Data operator +(Data x,Data y){
			if(y.b<=x.a) y.b=-inf,y.p=-inf;
			if(x.b>y.b) return Data(max(x.a,y.a),x.b,x.p);
			else return Data(max(x.a,y.a),y.b,y.p);
		}
	};
	struct Node{
		Data dat=Data(-inf,-inf,-inf);
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
	inline void Set(int x,int L,int R,int pos,Data k){
		if(L==R) return tr[x].dat=k,void();
		int mid=L+R>>1;
		if(pos<=mid) Set(x<<1,L,mid,pos,k);
		else Set(x<<1|1,mid+1,R,pos,k);
		PushUp(x);
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]=min(a[i],n);
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

	iota(p+1,p+q+1,1);
	sort(p+1,p+q+1,[](int i,int j){
		return ql[i]^ql[j]?ql[i]<ql[j]:qr[i]>qr[j];
	});
	for(int i=1;i<=q;i++) ip[p[i]]=i;
	for(int i=1;i<=n;i++) b[a[i]].push_back(i);

	SgT::Build(1,1,q);
	ls.insert({-inf,0});
	rs.insert({inf,q+1});
	for(int i=1;i<=n;i++) Fenw::Add(i,1);
	for(int i=1,j=0;i<=q;i++){
		if(qr[p[i]]<=qr[p[j]]) TgS::Set(1,1,q,i,TgS::Data(-inf,qr[p[i]],i));
		else{
			ls.insert({ql[p[i]],i});
			rs.insert({qr[p[i]],i});
			TgS::Set(1,1,q,i,TgS::Data(qr[p[i]],-inf,-inf));
			SgT::Set(1,1,q,i,{Fenw::Ask(ql[p[i]],qr[p[i]]),i});
			j=i;
		}
	}

	for(int v=n;~v;v--){
		for(int i:b[v]){
			Fenw::Add(i,-1);
			int lp=(*rs.lower_bound({i,0}))[1];
			int rp=(*--ls.lower_bound({i+1,0}))[1];
			SgT::Modify(1,1,q,lp,rp,-1);
		}
		while(SgT::tr[1].dat[0]>=v){
			int i=SgT::tr[1].dat[1];
			ans[p[i]]=v;
			ls.erase({ql[p[i]],i});
			rs.erase({qr[p[i]],i});
			SgT::Set(1,1,q,i,{-inf,i});
			TgS::Set(1,1,q,i,TgS::Data(-inf,-inf,-inf));
			while(true){
				int j=TgS::tr[1].dat.p;
				if(j==-inf) break ;
				TgS::Set(1,1,q,j,TgS::Data(qr[p[j]],-inf,-inf));
				ls.insert({ql[p[j]],j});
				rs.insert({qr[p[j]],j});
				SgT::Set(1,1,q,j,{Fenw::Ask(ql[p[j]],qr[p[j]]),j});
			}
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}