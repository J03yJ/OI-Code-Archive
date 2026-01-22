#include<bits/stdc++.h>

using namespace std;

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout
#define endl '\n'

using uint=unsigned;
const int N=2e5+9;

int a[N],ia[N],ql[N],qr[N],n,c,q;

uint ans[N];
vector<array<int,3>> mdf[N];
vector<array<int,2>> qry[N];

inline int MyLog(int x){return x>0?__lg(x):-1;}

struct Node{
	int l,r;
	uint sm,ad,hs,ct,ht;
	inline uint Len(){return r-l+1;}
}tr[N<<2];

inline void PushUp(int x){
	tr[x].sm=tr[x<<1].sm+tr[x<<1|1].sm;
	tr[x].hs=tr[x<<1].hs+tr[x<<1|1].hs;
}
inline void Push(int x,uint k,uint ct,uint ht){
	tr[x].hs+=ct*tr[x].sm+ht*tr[x].Len();
	tr[x].ht+=ct*tr[x].ad+ht;
	tr[x].sm+=k*tr[x].Len();
	tr[x].ad+=k;
	tr[x].ct+=ct;
}
inline void NoP(int x,uint k){tr[x].sm+=k*tr[x].Len(),tr[x].ad+=k;}
inline void PushDown(int x){
	if(tr[x].ad||tr[x].ct||tr[x].ht){
		Push(x<<1,tr[x].ad,tr[x].ct,tr[x].ht);
		Push(x<<1|1,tr[x].ad,tr[x].ct,tr[x].ht);
		tr[x].ad=tr[x].ct=tr[x].ht=0;
	}
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,uint k){
	if(l<=tr[x].l&&tr[x].r<=r) return NoP(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline uint QH(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].hs;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return QH(x<<1,l,r);
	else if(l>mid) return QH(x<<1|1,l,r);
	else return QH(x<<1,l,r)+QH(x<<1|1,l,r);
}

signed main(){
	cin>>n>>c>>q;
	for(int i=1;i<=n;i++) cin>>a[i],ia[a[i]]=i;
	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		qry[ql[i]-1].push_back({i,-1});
		qry[qr[i]].push_back({i,1});
	}

	multiset<int> s;
	for(int i=n;i>=1;i--){
		s.insert(ia[i]);
		vector<int> fr(c+1,0),bk(c+1,n+1);
		fr[0]=bk[0]=ia[i];
		auto it=s.lower_bound(ia[i]);
		for(int j=1;j<=c;j++){
			if(it==s.begin()) break ;
			fr[j]=*(--it);
		}
		it=s.lower_bound(ia[i]);
		for(int j=1;j<=c;j++){
			if(++it==s.end()) break ;
			bk[j]=*it;
		}
		for(int j=0;j<c;j++){
			if(bk[j]+1>bk[j+1]) continue ;
			if(fr[c-j]+1>fr[c-j-1]) continue ;
			mdf[bk[j]].push_back({fr[c-j]+1,fr[c-j-1],i});
			mdf[bk[j+1]].push_back({fr[c-j]+1,fr[c-j-1],-i});
		}
	}

	Build(1,1,n);
	for(int i=1;i<=n;i++){
		for(auto t:mdf[i]) Modify(1,t[0],t[1],t[2]);
		Push(1,0,1,0);
		for(auto t:qry[i]) ans[t[0]]+=QH(1,ql[t[0]],qr[t[0]])*t[1];
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	// int o=1.5e5,e=2e5;
	// cout<<o<<' '<<50<<' '<<e<<endl;
	// vector<int> tmp(o);
	// iota(tmp.begin(),tmp.end(),1);
	// mt19937 rng(4649);
	// shuffle(tmp.begin(),tmp.end(),rng);
	// for(int x:tmp) cout<<x<<' ';cout<<endl;
	// for(int i=1;i<=e;i++){
	// 	int l=rng()%n+1,r=rng()%n+1;
	// 	if(l>r) swap(l,r);
	// 	cout<<l<<' '<<r<<endl;
	// }

	return 0;
}