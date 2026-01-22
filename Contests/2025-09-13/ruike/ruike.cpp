#include<bits/stdc++.h>

using namespace std;

ifstream fin("ruike.in");
ofstream fout("ruike.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int mod=998244353;
const int inf=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

const int INV2=Inv(2);
const int INV6=Inv(6);
inline int C1(int x){return Add(x,0);}
inline int C2(int x){return Mul(Mul(x,x-1),INV2);}
inline int C3(int x){return Mul(Mul(Mul(x,x-1),x-2),INV6);}

int p[N][4],n,xm,ym;
vector<int> xval,yval;
inline int Lx(int i){return xval[i+1]-xval[i];}
inline int Lx(int l,int r){return l<=r?xval[r+1]-xval[l]:0;}
inline int Lx(array<int,2> p){return Lx(p[0],p[1]);}
inline int Ly(int i){return yval[i+1]-yval[i];}
inline int Ly(int l,int r){return l<=r?yval[r+1]-yval[l]:0;}
inline int Ly(array<int,2> p){return Ly(p[0],p[1]);}
inline void Discretize(){
	xval=yval={int(-1e9-1),1,int(1e9+1)};
	for(int i=1;i<=n;i++){
		xval.push_back(p[i][0]);
		yval.push_back(p[i][1]);
		xval.push_back(p[i][2]+1);
		yval.push_back(p[i][3]+1);
	}
	sort(xval.begin(),xval.end());
	sort(yval.begin(),yval.end());
	xval.erase(unique(xval.begin(),xval.end()),xval.end());
	yval.erase(unique(yval.begin(),yval.end()),yval.end());
	for(int i=1;i<=n;i++){
		p[i][0]=lower_bound(xval.begin(),xval.end(),p[i][0])-xval.begin();
		p[i][1]=lower_bound(yval.begin(),yval.end(),p[i][1])-yval.begin();
		p[i][2]=upper_bound(xval.begin(),xval.end(),p[i][2])-xval.begin()-1;
		p[i][3]=upper_bound(yval.begin(),yval.end(),p[i][3])-yval.begin()-1;
	}
	xm=xval.size()-2,ym=yval.size()-2;
}
inline void Flip(){
	swap(xm,ym);
	swap(xval,yval);
	for(int i=1;i<=n;i++) for(int k:{0,2}) swap(p[i][k],p[i][k|1]);
}
inline void ClearVal(){
	xval.clear();
	yval.clear();
}

inline int Work1(){
	int ans=0,lmax=0,rmin=xm+1;
	vector<array<int,2>> f(xm+2,{1,xm}),g(xm+2,{1,xm});
	auto Merge=[](array<int,2> x,array<int,2> y)->array<int,2>{return {max(x[0],y[0]),min(x[1],y[1])};};
	for(int i=1;i<=n;i++){
		f[p[i][2]]=Merge(f[p[i][2]],{p[i][0],p[i][2]});
		g[p[i][0]]=Merge(g[p[i][0]],{p[i][0],p[i][2]});
		lmax=max(lmax,p[i][0]);
		rmin=min(rmin,p[i][2]);
	}
	for(int i=1;i<=xm;i++) f[i]=Merge(f[i],f[i-1]);
	for(int i=xm;i>=1;i--) g[i]=Merge(g[i],g[i+1]);
	for(int i=0;i<=xm+1;i++) f[i]=Merge(f[i],{1,i});
	for(int i=xm+1;i>=0;i--) g[i]=Merge(g[i],{i,xm});
	for(int i=1;i<=xm;i++){
		AddAs(ans,Mul(Mul(C1(Lx(f[i-1])),C1(Lx(g[i+1]))),C1(Lx(i))));
		if(i<=rmin) AddAs(ans,Mul(C1(Lx(g[i+1])),C2(Lx(i))));
		if(i>=lmax) AddAs(ans,Mul(C1(Lx(f[i-1])),C2(Lx(i))));
		if(lmax<=i&&i<=rmin) AddAs(ans,C3(Lx(i)));
	}
	return ans;
}

struct Node{
	int l,r;
	int dat,sum;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define sum(x) tr[x].sum
#define len(x) (Lx(l(x),r(x)))

inline int Calc(int x,int k){
	if(k<=dat(x)) return Mul(len(x),k);
	if(l(x)==r(x)) return sum(x);
	if(k<=dat(x<<1|1)) return Add(Mul(len(x<<1|1),k),Calc(x<<1,k));
	else return Add(Calc(x<<1|1,k),Sub(sum(x),sum(x<<1|1)));
}
inline void PushUp(int x){
	dat(x)=min(dat(x<<1),dat(x<<1|1));
	if(dat(x<<1|1)<=dat(x<<1)) sum(x)=Add(sum(x<<1|1),Mul(len(x<<1),dat(x<<1|1)));
	else sum(x)=Add(sum(x<<1|1),Calc(x<<1,dat(x<<1|1)));
}
inline void Build(int x,int l,int r,int k){
	l(x)=l,r(x)=r,dat(x)=sum(x)=0;
	if(l(x)==r(x)) return dat(x)=k,sum(x)=Mul(len(x),k),void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid,k),Build(x<<1|1,mid+1,r,k);
	PushUp(x);
}
inline void Update(int x,int pos,int k){
	if(l(x)==r(x)) return dat(x)=k,sum(x)=Mul(len(x),k),void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) Update(x<<1,pos,k);
	else Update(x<<1|1,pos,k);
	PushUp(x);
}
inline int FindL(int x,int k){
	if(l(x)==r(x)) return l(x)+(dat(x)<k);
	if(dat(x<<1|1)<k) return FindL(x<<1|1,k);
	else return FindL(x<<1,k);
}
inline array<int,2> Query(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r) return array<int,2>({min(dat(x),k),Calc(x,k)});
	array<int,2> res({k,0});
	int mid=l(x)+r(x)>>1;
	if(r>mid){
		auto tmp=Query(x<<1|1,l,r,res[0]);
		res[0]=min(res[0],tmp[0]);
		AddAs(res[1],tmp[1]);
	}
	if(l<=mid){
		auto tmp=Query(x<<1,l,r,res[0]);
		res[0]=min(res[0],tmp[0]);
		AddAs(res[1],tmp[1]);
	}
	return res;
}
inline int GetSum(int l,int r){
	return Sub(Query(1,l,xm,inf)[1],r<xm?Query(1,r+1,xm,inf)[1]:0);
}
inline void Puts(int x){
	if(l(x)==r(x)) return ;
	Puts(x<<1),Puts(x<<1|1);
}

struct DelHeap{
	priority_queue<int> p,q;
	inline void Insert(int x){p.push(x);}
	inline void Erase(int x){q.push(x);}
	inline int Top(){
		while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
		return p.top();
	}
	inline int Size(){return p.size()-q.size();}
	inline void Clear(){
		while(p.size()) p.pop();
		while(q.size()) q.pop();
	}
}q[N],lmx,rmn;
inline void Init(){
	lmx.Insert(1);
	rmn.Insert(-xm);
	Build(1,1,xm,1e9+1);
	for(int i=1;i<=xm;i++) q[i].Insert(-1e9-1);
}
inline void ClearHeap(){
	lmx.Clear();
	rmn.Clear();
	for(int i=1;i<=xm;i++) q[i].Clear();
}
inline void Insert(int x0,int x1){
	lmx.Insert(x0),rmn.Insert(-x1);
	if(!--x0) return ;
	int tmp=-q[x0].Top();
	q[x0].Insert(-xval[x1+1]);
	if(-q[x0].Top()!=tmp) Update(1,x0,-q[x0].Top());
}
inline void Erase(int x0,int x1){
	lmx.Erase(x0),rmn.Erase(-x1);
	if(!--x0) return ;
	int tmp=-q[x0].Top();
	q[x0].Erase(-xval[x1+1]);
	if(-q[x0].Top()!=tmp) Update(1,x0,-q[x0].Top());
}
inline int Work2(){
	int ans=0;
	Init();
	vector<int> dlt(xm+1,0);
	for(int i=1;i<=xm;i++){
		dlt[i]=Sub(C2(Lx(i)),Mul(Lx(i),xval[i+1]));
		AddAs(dlt[i],dlt[i-1]);
	}
	vector<vector<array<int,2>>> ins(ym+2),ers(ym+2);
	for(int i=1;i<=n;i++){
		ins[1].push_back({p[i][0],p[i][2]});
		ers[p[i][1]].push_back({p[i][0],p[i][2]});
		ins[p[i][3]+1].push_back({p[i][0],p[i][2]});
	}
	for(int i=1;i<=ym;i++){
		for(auto p:ins[i]) Insert(p[0],p[1]);
		for(auto p:ers[i]) Erase(p[0],p[1]);
		int l=FindL(1,xval[lmx.Top()]),r=-rmn.Top();
		if(l>r) continue ;
		int tmp=GetSum(l,r);
		if(r<lmx.Top()){
			SubAs(tmp,Mul(Lx(l,r),xval[lmx.Top()]));
		}else{
			int p=lmx.Top();
			SubAs(tmp,Mul(Lx(l,p-1),xval[lmx.Top()]));
			AddAs(tmp,Sub(dlt[r],dlt[p-1]));
		}
		AddAs(ans,Mul(C1(Ly(i)),tmp));
	}
	ClearHeap();
	return ans;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) for(int k:{0,1,2,3}) cin>>p[i][k];

		int ans=0;
		Discretize();
		AddAs(ans,Work1());
		AddAs(ans,Work2());
		Flip();
		AddAs(ans,Work1());
		AddAs(ans,Work2());

		cout<<ans<<endl;

		ClearVal();
	}

	return 0;
}