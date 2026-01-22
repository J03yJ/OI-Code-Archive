#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ull=unsigned long long;
using bint=__int128;
const int T=4.5e6+9;
const int N=1e6+9;

ull qx[N],qc[N],n;
int op[N],q,tot;

vector<ull> pos;

struct Node{
	ull len,dat,com;
}tr[T<<2];

inline void PushUp(int x){
	tr[x].dat=tr[x<<1].dat^tr[x<<1|1].dat;
	tr[x].com=tr[x<<1].com&tr[x<<1|1].com;
}
inline void Build(int x,int l,int r){
	if(l==r) return tr[x].len=pos[r+1]-pos[l],void();
	int mid=l+r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int L,int R,int l,int r,ull k){
	if((tr[x].com&k)==k) return ;
	if(L==R){
		tr[x].com|=k;
		tr[x].dat=tr[x].len&1?tr[x].com:0;
		return ;
	}
	int mid=L+R>>1;
	if(l<=mid) Modify(x<<1,L,mid,l,r,k);
	if(r>mid) Modify(x<<1|1,mid+1,R,l,r,k);
	PushUp(x);
}
inline ull Query(int x,int L,int R,int l,int r){
	if(l<=L&&R<=r) return tr[x].dat;
	int mid=L+R>>1;
	if(r<=mid) return Query(x<<1,L,mid,l,r);
	else if(l>mid) return Query(x<<1|1,mid+1,R,l,r);
	else return Query(x<<1,L,mid,l,r)^Query(x<<1|1,mid+1,R,l,r);
}

inline bint L(bint l){return l*(l-1)/2+2;}
inline bint R(bint r){return L(r+1)-1;}
inline void Insert(bint l,bint r){
	pos.push_back(l);
	pos.push_back(r+1);
	l=L(l),r=R(r);
	if(l>n) return ;
	r=min(r,bint(n));
	Insert(l,r);
}
inline void Mod(bint l,bint r,ull k){
	int lp=lower_bound(pos.begin(),pos.end(),ull(l))-pos.begin();
	int rp=upper_bound(pos.begin(),pos.end(),ull(r))-pos.begin()-1;
	Modify(1,1,tot,lp,rp,k);
	l=L(l),r=R(r);
	if(l>n) return ;
	r=min(r,bint(n));
	Mod(l,r,k);
}
inline ull Qry(bint l,bint r){
	int lp=lower_bound(pos.begin(),pos.end(),ull(l))-pos.begin();
	int rp=upper_bound(pos.begin(),pos.end(),ull(r))-pos.begin()-1;
	ull res=Query(1,1,tot,lp,rp);
	l=L(l),r=R(r);
	if(l>n) return res;
	r=min(r,bint(n));
	return res^Qry(l,r);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1) cin>>qx[i]>>qc[i];
		else cin>>qx[i];
		Insert(qx[i],qx[i]);
	}
	
	pos.push_back(0),pos.push_back(n+1);
	sort(pos.begin(),pos.end());
	pos.erase(unique(pos.begin(),pos.end()),pos.end());

	tot=pos.size()-1;
	// cerr<<tot<<endl;
	// for(ull x:pos) cout<<x<<endl;
	Build(1,1,tot);

	for(int i=1;i<=q;i++){
		if(op[i]==1) Mod(qx[i],qx[i],qc[i]);
		else cout<<Qry(qx[i],qx[i])<<endl;
	}

	return 0;
}