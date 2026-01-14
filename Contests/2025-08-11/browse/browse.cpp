#include<bits/stdc++.h>

using namespace std;

ifstream fin("browse.in");
ofstream fout("browse.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int p[N],ip[N],t[N],n;
int typ[N],qx[N],qk[N],q;
ll ans[N];
vector<int> qry[N];

struct Node{
	int l,r;
	ll val,sum,hsum,ver;
	ll cov,hcov,sver,tver;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define len(x) (r(x)-l(x)+1)
#define sum(x) tr[x].sum
#define val(x) tr[x].val
#define hsum(x) tr[x].hsum
#define ver(x) tr[x].ver
#define cov(x) tr[x].cov
#define hcov(x) tr[x].hcov
#define sver(x) tr[x].sver
#define tver(x) tr[x].tver

inline void Push(int x,ll c,ll hc,ll sv,ll tv){
	if(!~sver(x)) sver(x)=tver(x)=sv;
	hcov(x)+=cov(x)*(sv-tver(x));
	hcov(x)+=hc;
	cov(x)=c;
	hsum(x)+=sum(x)*(sv-ver(x));
	hsum(x)+=hc*len(x);
	sum(x)=c*len(x);
	val(x)=c;
	ver(x)=tver(x)=tv;
}
inline void PushDown(int x){
	if(!~cov(x)) return ;
	Push(x<<1,cov(x),hcov(x),sver(x),tver(x));
	Push(x<<1|1,cov(x),hcov(x),sver(x),tver(x));
	cov(x)=sver(x)=tver(x)=-1,hcov(x)=0;
}
inline void PushUp(int x){
	sum(x)=sum(x<<1)+sum(x<<1|1);
	hsum(x)=hsum(x<<1)+hsum(x<<1|1);
	val(x)=max(val(x<<1),val(x<<1|1));
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,cov(x)=sver(x)=tver(x)=-1;
	if(l(x)==r(x)){
		val(x)=sum(x)=cov(x)=n+1000-l(x);
		ver(x)=0;
		return ;
	}
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll k,ll t){
	if(l>r) return ;
	if(l<=l(x)&&r(x)<=r) return Push(x,k,0,t,t);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,k,t);
	if(r>mid) Modify(x<<1|1,l,r,k,t);
	PushUp(x);
}
inline ll Sum(int x,int pos){
	if(l(x)==r(x)) return sum(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Sum(x<<1,pos);
	else return Sum(x<<1|1,pos);
}
inline ll HSum(int x,int pos){
	if(l(x)==r(x)) return hsum(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return HSum(x<<1,pos);
	else return HSum(x<<1|1,pos);
}
inline int Find(int x,ll k){
	if(l(x)==r(x)) return l(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(k<=val(x<<1)) return Find(x<<1,k);
	else return Find(x<<1|1,k);
}

int lp[N],rp[N];
inline void Awake(int x,int t){
	lp[x]=rp[x]=x;
	if(lp[x-1]) lp[x]=lp[x-1];
	if(rp[x+1]) rp[x]=rp[x+1];
	if(lp[x-1]) rp[lp[x-1]]=rp[x];
	if(rp[x+1]) lp[rp[x+1]]=lp[x];
	Modify(1,Find(1,lp[x]-1),rp[x]-lp[x]+1,lp[x]-1,t);
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=q;i++){
		cin>>typ[i];
		if(!typ[i]) cin>>qx[i]>>qk[i],qry[qx[i]].push_back(i);
		else cin>>qk[i];
	}

	Build(1,1,n);
	for(int i=1;i<=n;i++) ip[p[i]]=i;
	for(int i=1;i<=n;i++){
		if(i-1) Awake(ip[i-1],i-1);
		for(int j:qry[i]) ans[j]=Sum(1,qk[j])+qk[j];
	}
	Modify(1,1,n,0,n);
	for(int i=1;i<=q;i++) if(typ[i]) ans[i]=HSum(1,qk[i])+1ll*n*qk[i];

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	return 0;
}