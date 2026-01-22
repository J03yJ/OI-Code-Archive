#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e6+9;

int a[N],b[N],lp[N],l[N],r[N],ans[N],n,k,q;

struct Node{
	int l,r,siz;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define siz(x) tr[x].siz

inline void PushUp(int x){siz(x)=siz(x<<1)+siz(x<<1|1);}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,siz(x)=0;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline int FindPos(int x,int k){
	if(l(x)==r(x)) return l(x);
	if(k<=siz(x<<1)) return FindPos(x<<1,k);
	else return FindPos(x<<1|1,k-siz(x<<1));
}
inline int Sum(int x,int l,int r){
	if(l>r) return 0;
	if(l<=l(x)&&r(x)<=r) return siz(x);
	int mid=l(x)+r(x)>>1;
	if(r<=mid) return Sum(x<<1,l,r);
	else if(l>mid) return Sum(x<<1|1,l,r);
	else return Sum(x<<1,l,r)+Sum(x<<1|1,l,r);
}
inline void Insert(int x,int pos){
	if(l(x)==r(x)) return siz(x)++,void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) Insert(x<<1,pos);
	else Insert(x<<1|1,pos);
	PushUp(x);
}

int t[N<<2];
inline void Add(int x,int k){while(x<=n) t[x]+=k,x+=x&-x;}
inline int Ask(int x){int sum=0;while(x) sum+=t[x],x&=x-1;return sum;}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}
inline void Clear(){for(int i=1;i<=n;i++) t[i]=0;}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>k>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>l[i]>>r[i];

	for(int i=1;i<=n;i++){
		if(a[i]>1) b[i]=Ask(1,a[i]-1);
		Add(a[i],1);
	}
	Clear();
	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return a[i]<a[j];});
	Build(1,1,n);
	for(int i:p){
		if(b[i]<k) lp[i]=0;
		else lp[i]=FindPos(1,b[i]-k+1);
		Insert(1,i);
	}

	Build(1,1,n);
	vector<array<int,3>> op;
	for(int i=1;i<=n;i++) op.push_back({0,i,lp[i]});
	for(int i=1;i<=q;i++) op.push_back({1,r[i],i});
	sort(op.begin(),op.end(),[](auto x,auto y){return x[1]^y[1]?x[1]<y[1]:x[0]<y[0];});
	for(auto t:op){
		if(t[0]==0){if(t[2]) Add(t[2],1);}
		else{
			ans[t[2]]=(r[t[2]]-l[t[2]]+1)-Ask(l[t[2]],r[t[2]]);
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}