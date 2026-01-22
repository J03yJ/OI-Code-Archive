#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

struct Data{
	int pmin,pmax,sum;
	Data(){}
	Data(int _pmin,int _pmax,int _sum){
		pmin=_pmin;
		pmax=_pmax;
		sum=_sum;
	}
	inline friend Data operator +(Data x,Data y){
		return Data(min(x.pmin,y.pmin+x.sum),max(x.pmax,y.pmax+x.sum),x.sum+y.sum);
	}
};

struct Node{
	int l,r;
	Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return dat(x)=Data(1,1,1),void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,Data k){
	if(l(x)==r(x)) return dat(x)=k,void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline Data Query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x);
	int mid=l(x)+r(x)>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

int a[N],n;
inline bool Check(int k){
	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return a[i]<a[j];});
	p.insert(p.begin(),0);
	Build(1,0,n);
	for(int i=1,j=1;i<=n;i++){
		while(j<=n&&a[p[j]]<a[p[i]]+k) Set(1,p[j++],Data(-1,-1,-1));
		int tmp=Query(1,p[i],n).pmax+Query(1,0,p[i]-1).sum-Query(1,0,p[i]-1).pmin;
		if(tmp>=0) return 1;
	}
	return 0;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		
		int l=-1,r=n+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(Check(mid)) l=mid;
			else r=mid;
		}

		cout<<l<<endl;
	}

	return 0;
}