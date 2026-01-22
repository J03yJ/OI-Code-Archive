#include<bits/stdc++.h>

using namespace std;

ifstream fin("mexsumsum.in");
ofstream fout("mexsumsum.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;

int a[N],n,q;

namespace DS1{
	struct Node{
		int lc,rc,mn;
	}tr[N<<5];
	
	int root[N],cnt;
	inline int Allc(){return ++cnt;}
	inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
	inline void PushUp(int x){tr[x].mn=min(tr[tr[x].lc].mn,tr[tr[x].rc].mn);}
	inline void Set(int &x,int L,int R,int pos,int k){
		x=Clone(x);
		if(L==R) return tr[x].mn=k,void();
		int mid=L+R>>1;
		if(pos<=mid) Set(tr[x].lc,L,mid,pos,k);
		else Set(tr[x].rc,mid+1,R,pos,k);
		PushUp(x);
	}
	inline int Query(int x,int L,int R,int lim){
		if(!x||L==R) return L;
		int mid=L+R>>1;
		if(tr[tr[x].lc].mn<lim) return Query(tr[x].lc,L,mid,lim);
		else return Query(tr[x].rc,mid+1,R,lim);
	}
}
namespace DS2{
	struct Node{
		int lc,rc,len;
		ll sum,hsum,tag,htag,cnt;
	}tr[N<<7];
	
	int root[N],cnt;
	inline int Allc(){return ++cnt;}
	inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
	inline void PushUp(int x){
		tr[x].sum=tr[tr[x].lc].sum+tr[tr[x].rc].sum;
		tr[x].hsum=tr[tr[x].lc].hsum+tr[tr[x].rc].hsum;
	}
	inline void Push(int x,ll tg,ll htg,ll c){
		tr[x].hsum+=tr[x].sum*c+tr[x].len*htg;
		tr[x].sum+=tr[x].len*tg;
		tr[x].htag+=tr[x].tag*c+htg;
		tr[x].tag+=tg;
		tr[x].cnt+=c;
	}
	inline void PushDown(int x){
		if(!tr[x].tag&&!tr[x].htag&&!tr[x].cnt) return ;
		tr[x].lc=Clone(tr[x].lc);
		tr[x].rc=Clone(tr[x].rc);
		Push(tr[x].lc,tr[x].tag,tr[x].htag,tr[x].cnt);
		Push(tr[x].rc,tr[x].tag,tr[x].htag,tr[x].cnt);
		tr[x].tag=tr[x].htag=tr[x].cnt=0;
	}
	inline void Build(int &x,int L,int R){
		x=Allc(),tr[x].len=R-L+1;
		if(L==R) return ;
		int mid=L+R>>1;
		Build(tr[x].lc,L,mid),Build(tr[x].rc,mid+1,R);
		PushUp(x);
	}
	inline void Modify(int &x,int L,int R,int l,int r,ll k){
		x=Clone(x);
		if(l<=L&&R<=r) return Push(x,k,0,0),void();
		PushDown(x);
		int mid=L+R>>1;
		if(l<=mid) Modify(tr[x].lc,L,mid,l,r,k);
		if(r>mid) Modify(tr[x].rc,mid+1,R,l,r,k);
		PushUp(x);
	}
	inline ll Query(int x,int L,int R,int l,int r,ll tg=0,ll htg=0,ll c=0){
		Node p=tr[x];
		p.hsum+=p.sum*c+p.len*htg;
		p.sum+=p.len*tg;
		p.htag+=p.tag*c+htg;
		p.tag+=tg;
		p.cnt+=c;

		if(l<=L&&R<=r) return p.hsum;
		int mid=L+R>>1;
		if(r<=mid) return Query(tr[x].lc,L,mid,l,r,p.tag,p.htag,p.cnt);
		else if(l>mid) return Query(tr[x].rc,mid+1,R,l,r,p.tag,p.htag,p.cnt);
		else return Query(tr[x].lc,L,mid,l,r,p.tag,p.htag,p.cnt)+Query(tr[x].rc,mid+1,R,l,r,p.tag,p.htag,p.cnt);
	}
}

vector<int> vpos[N];
vector<array<int,2>> rg[N];
inline void InitMex(){for(int i=1;i<=n;i++) DS1::Set(DS1::root[i]=DS1::root[i-1],0,n,a[i],i);}
inline int Mex(int l,int r){return DS1::Query(DS1::root[r],0,n,l);}
inline void GetRange(){
	InitMex();
	for(int i=1;i<=n;i++){
		if(!a[i]) rg[1].push_back({i,i});
		vpos[a[i]].push_back(i);
	}
	for(int i=0;i<=n;i++) sort(vpos[i].begin(),vpos[i].end());
	for(int i=1;i<=n;i++){
		sort(rg[i].begin(),rg[i].end(),[](auto x,auto y){return x[0]^y[0]?x[0]>y[0]:x[1]<y[1];});
		vector<array<int,2>> tmp;
		for(auto t:rg[i]){
			if(tmp.size()&&tmp.back()[1]<=t[1]) continue ;
			tmp.push_back(t);
		}
		rg[i]=tmp;
		for(auto t:rg[i]){
			auto lp=upper_bound(vpos[i].begin(),vpos[i].end(),t[0]);
			auto rp=lower_bound(vpos[i].begin(),vpos[i].end(),t[1]);
			if(lp!=vpos[i].begin()){
				int l=*--lp;
				rg[Mex(l,t[1])].push_back({l,t[1]});
			}
			if(rp!=vpos[i].end()){
				int r=*rp;
				rg[Mex(t[0],r)].push_back({t[0],r});
			}
		}
	}
}

vector<array<int,2>> mdf[N];
inline void InitQuery(){
	DS2::Build(DS2::root[0],1,n);
	for(int i=1;i<=n;i++){
		int lim=0;
		sort(rg[i].begin(),rg[i].end());
		for(auto t:rg[i]){
			mdf[t[1]].push_back({lim+1,t[0]});
			lim=t[0];
		}
	}
	vector<int> tmp;
	for(int i=1;i<=n;i++) if(a[i]) tmp.push_back(i);
	for(int i=1;i<=n;i++){
		auto p=lower_bound(tmp.begin(),tmp.end(),i);
		if(p==tmp.end()) continue ;
		mdf[*p].push_back({i,i});
	}
	for(int i=1;i<=n;i++){
		DS2::root[i]=DS2::root[i-1];
		for(auto t:mdf[i]) DS2::Modify(DS2::root[i],1,n,t[0],t[1],1);
		DS2::Push(DS2::root[i],0,0,1);
	}
}
inline ll Query(int l,int r){return DS2::Query(DS2::root[r],1,n,l,r);}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	GetRange();
	InitQuery();

	ll ans=0;
	while(q--){
		ll l,r;
		cin>>l>>r;
		l=(l^ans)%n+1;
		r=(r^ans)%n+1;
		if(l>r) swap(l,r);
		cout<<(ans=(unsigned)Query(l,r))<<endl;
	}

	return 0;
}