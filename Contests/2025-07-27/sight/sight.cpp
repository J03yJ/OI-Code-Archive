#include<bits/stdc++.h>

using namespace std;

ifstream fin("sight.in");
ofstream fout("sight.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;
const ll inf=1e18;

struct Line{
	ll k,b;
	Line(){}
	Line(ll _k,ll _b){k=_k,b=_b;}
	inline friend bool operator <(Line f,Line g){
		return f.b<g.b||f.b==g.b&&f.k<g.k;
	}
};
inline ll Itsct(Line f,Line g){
	if(f.k<g.k||f.k==g.k&&f.b<g.b) swap(f,g);
	if(f.b>=g.b) return inf;
	else return (g.b-f.b)/(f.k-g.k);
}

struct Data{
	Line f;
	ll lim;
	Data(){}
	Data(Line _f){f=_f,lim=inf;}
	inline friend Data operator +(Data x,Data y){
		Data res;
		res.lim=min(min(x.lim,y.lim),Itsct(x.f,y.f));
		res.f=min(x.f,y.f);
		return res;
	}
};

int a[N],n;
int val[N],tot;
inline int Find(int k){return lower_bound(val,val+tot+1,k)-val;}

struct Node{
	int l,r;
	Data dat;
	ll xtag,ytag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define xtag(x) tr[x].xtag
#define ytag(x) tr[x].ytag

inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
inline void Push(int x,ll xk,ll yk){
	xtag(x)+=xk;
	ytag(x)+=yk;
	dat(x).lim-=xk;
	dat(x).f.b+=xk*dat(x).f.k+yk;
}
inline void PushDown(int x){
	if(!xtag(x)&&!ytag(x)) return ;
	Push(x<<1,xtag(x),ytag(x));
	Push(x<<1|1,xtag(x),ytag(x));
	xtag(x)=ytag(x)=0;
}
inline void Rebuild(int x){
	if(dat(x).lim>0) return ;
	PushDown(x);
	Rebuild(x<<1);
	Rebuild(x<<1|1);
	PushUp(x);
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return dat(x)=Data(Line(0,inf)),void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,Line f){
	if(l(x)==r(x)) return dat(x)=Data(f),void();
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) Set(x<<1,pos,f);
	else Set(x<<1|1,pos,f);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll xk,ll yk){
	if(l<=l(x)&&r(x)<=r) return Push(x,xk,yk),Rebuild(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,xk,yk);
	if(r>mid) Modify(x<<1|1,l,r,xk,yk);
	PushUp(x);
}
inline Line Query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x).f;
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return min(Query(x<<1,l,mid),Query(x<<1|1,mid+1,r));
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++) val[i]=a[i];
	sort(val+1,val+n+1);
	tot=unique(val+1,val+n+1)-val-1;
	for(int i=0;i<=n;i++) a[i]=Find(a[i]);

	Build(1,0,tot);
	Set(1,0,Line(0,0));
	for(int i=1,k=0;i<=n;i++){
		if(a[i]<=k){
			Line f=Query(1,0,a[i]-1);
			Modify(1,a[i],k,1,0);
			Modify(1,0,a[i]-1,0,val[k]);
			Set(1,a[i],Line(val[a[i]],min(Query(1,a[i],a[i]).b,f.b+val[a[i]])));
		}else{
			Line f=Query(1,0,k);
			Modify(1,0,k,0,val[a[i]]);
			Set(1,k,Line(val[k],min(Query(1,k,k).b,f.b+val[a[i]])));
			k=a[i];
		}
	}

	cout<<Query(1,0,tot).b<<endl;

	return 0;
}