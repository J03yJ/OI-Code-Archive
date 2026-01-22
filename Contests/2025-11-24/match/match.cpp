#include<bits/stdc++.h>

using namespace std;

ifstream fin("match.in");
ofstream fout("match.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;
const int N=3e5+9;
const int lgN=2e1;
const ull nul=LLONG_MAX;

struct Node{
	int l,r;
	ll am,bm;
	ull a,b,hs,as,bs,ax,ka,kb,kl;
	inline int Len(){return r-l+1;}
}tr[N<<2];

inline void PushA(int x,ull k){tr[x].a=k*tr[x].Len(),tr[x].am=tr[x].as=k;}
inline void PushB(int x,ull k){tr[x].b=k*tr[x].Len(),tr[x].bm=tr[x].bs=k,tr[x].ax=nul;}
inline void PushAtoB(int x,ull k){
	if(tr[x].as!=nul) PushB(x,tr[x].as+k);
	else tr[x].b=tr[x].a+tr[x].Len()*k,tr[x].ax=k,tr[x].bm=tr[x].am+k,tr[x].bs=nul;
}
inline void Stamp(int x){
	if(tr[x].bs!=nul) tr[x].kl+=tr[x].bs;
	else if(tr[x].ax!=nul) tr[x].ka+=1,tr[x].kl+=tr[x].ax;
	else tr[x].kb+=1;
	tr[x].hs+=tr[x].b;
}
inline void PushK(int x,ull ka,ull kb,ull kl){
	if(tr[x].as!=nul) kl+=ka*tr[x].as,ka=0;
	if(tr[x].bs!=nul) kl+=kb*tr[x].bs,kb=0;
	if(tr[x].ax!=nul) ka+=kb,kl+=kb*tr[x].ax,kb=0;
	tr[x].ka+=ka,tr[x].kb+=kb,tr[x].kl+=kl;
	if(tr[x].ax==nul) tr[x].hs+=ka*tr[x].a+kb*tr[x].b+kl*tr[x].Len();
	else tr[x].hs+=ka*(tr[x].b-tr[x].ax*tr[x].Len())+kb*tr[x].b+kl*tr[x].Len();
}
inline void PushDown(int x){
	if(tr[x].ka||tr[x].kb||tr[x].kl){
		PushK(x<<1,tr[x].ka,tr[x].kb,tr[x].kl);
		PushK(x<<1|1,tr[x].ka,tr[x].kb,tr[x].kl);
		tr[x].ka=tr[x].kb=tr[x].kl=0;
	}
	if(tr[x].ax!=nul) PushAtoB(x<<1,tr[x].ax),PushAtoB(x<<1|1,tr[x].ax),tr[x].ax=nul;
	if(tr[x].bs!=nul) PushB(x<<1,tr[x].bs),PushB(x<<1|1,tr[x].bs),tr[x].bs=nul;
	if(tr[x].as!=nul) PushA(x<<1,tr[x].as),PushA(x<<1|1,tr[x].as),tr[x].as=nul;
}
inline void PushUp(int x){
	tr[x].a=tr[x<<1].a+tr[x<<1|1].a;
	tr[x].b=tr[x<<1].b+tr[x<<1|1].b;
	tr[x].hs=tr[x<<1].hs+tr[x<<1|1].hs;
	tr[x].am=min(tr[x<<1].am,tr[x<<1|1].am);
	tr[x].bm=min(tr[x<<1].bm,tr[x<<1|1].bm);
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].as=tr[x].bs=tr[x].ax=LLONG_MAX;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
template<class F> inline void Assign(int x,int l,int r,ull k,F P){
	if(l<=tr[x].l&&tr[x].r<=r) return P(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Assign(x<<1,l,r,k,P);
	if(r>mid) Assign(x<<1|1,l,r,k,P);
	PushUp(x);
}
inline ull Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].hs;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}
inline int Find(int x,ll k){
	if(tr[x].l==tr[x].r) return tr[x].l+(tr[x].bm>=k);
	PushDown(x);
	if(tr[x<<1].bm>=k) return Find(x<<1|1,k);
	else return Find(x<<1,k);
}

ull ans[N];
vector<array<int,4>> qry[N];
int ql[N],qr[N],lg[N],T,n,q;
ll a[N],s[N],mp[N][lgN];
inline int Cmp(int i,int j){return s[i-1]<s[j-1]?i:j;}
inline void InitMp(){
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) mp[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=1;i<=n-(1<<k)+1;i++){
			mp[i][k]=Cmp(mp[i][k-1],mp[i+(1<<k-1)][k-1]);
		}
	}
}
inline int GetMp(int l,int r){
	int k=lg[r-l+1];
	return Cmp(mp[l][k],mp[r-(1<<k)+1][k]);
}

signed main(){
	cin>>T>>n;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		qry[ql[i]-1].push_back({i,ql[i],qr[i],-1});
		qry[qr[i]].push_back({i,ql[i],qr[i],1});
	}

	InitMp();
	Build(1,1,n);
	vector<int> mx,mn;
	for(int i=1;i<=n;i++){
		while(mx.size()&&s[mx.back()]<s[i]) mx.pop_back();
		while(mn.size()&&s[mn.back()-1]>s[i-1]) mn.pop_back();
		int p=mx.size()?mx.back():0;
		if(p){
			int j=GetMp(p+1,i),k=Find(1,s[i]-s[j-1]);
			if(k<=p) Assign(1,k,p,s[i]-s[j-1],PushB);
		}
		int q=mn.size()?mn.back():0;
		Assign(1,q+1,i,-s[i-1],PushA);
		Assign(1,p+1,i,s[i],PushAtoB);
		int k=Find(1,0);
		if(k<=n) Assign(1,k,n,0,PushB);
		Stamp(1);
		mx.push_back(i),mn.push_back(i);
		for(auto t:qry[i]) ans[t[0]]+=Query(1,t[1],t[2])*t[3];
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}