#include<bits/stdc++.h>

using namespace std;

ifstream fin("flame.in");
ofstream fout("flame.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;
const int mod=998244353;

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

struct Fenw{
	int tr[N],lim;
	inline void Init(int _lim){lim=_lim;}
	inline void Add(int x,int k){while(x<=lim) AddAs(tr[x],k),x+=x&-x;}
	inline int Ask(int x){int sum=0;while(x) AddAs(sum,tr[x]),x&=x-1;return sum;}
	inline int Ask(int l,int r){return Sub(Ask(r),Ask(l-1));}
}t[3];

int a[N],x[N],y[N],w[N],ql[N],qr[N],id[N],d[N],n,m;
vector<array<int,2>> val;
vector<int> o[N];
inline void Discr(){
	val.push_back({-1,-1});
	for(int i=1;i<=m;i++) val.push_back({y[i],i});
	sort(val.begin(),val.end());
	for(int i=1;i<=m;i++){
		id[i]=lower_bound(val.begin(),val.end(),array<int,2>({y[i],i}))-val.begin();
		d[id[i]]=i;
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>x[i]>>y[i]>>w[i],o[x[i]].push_back(i);

	Discr();
	vector<int> stk,v;
	for(int i=1;i<=n;i++){
		while(stk.size()&&a[i]>=a[stk.back()]) stk.pop_back(),v.pop_back();
		stk.push_back(i),v.push_back(a[i]);
		for(int j:o[i]){
			int pos=upper_bound(v.begin(),v.end(),y[j],greater<int>())-v.begin()-1;
			if(pos<0) ql[j]=1;
			else ql[j]=stk[pos]+1;
		}
	}
	stk.clear(),v.clear();
	for(int i=n;i>=1;i--){
		while(stk.size()&&a[i]>=a[stk.back()]) stk.pop_back(),v.pop_back();
		stk.push_back(i),v.push_back(a[i]);
		for(int j:o[i]){
			int pos=upper_bound(v.begin(),v.end(),y[j],greater<int>())-v.begin()-1;
			if(pos<0) qr[j]=n;
			else qr[j]=stk[pos]-1;
		}
	}


	int ans=0;
	for(int k:{0,1,2}) t[k].Init(n);
	for(int i=1;i<=m;i++){
		int j=d[i];
		AddAs(ans,Mul(QPow(w[j],0),t[2].Ask(ql[j],qr[j])));
		SubAs(ans,Mul(2,Mul(QPow(w[j],1),t[1].Ask(ql[j],qr[j]))));
		AddAs(ans,Mul(QPow(w[j],2),t[0].Ask(ql[j],qr[j])));
		for(int k:{0,1,2}) t[k].Add(x[j],QPow(w[j],k));
	}

	cout<<ans<<endl;

	return 0;
}