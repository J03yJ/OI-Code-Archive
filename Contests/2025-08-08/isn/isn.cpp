#include<bits/stdc++.h>

using namespace std;

ifstream fin("isn.in");
ofstream fout("isn.out");
#define cin fin
#define cout fout
#define endl '\n'


using ll=long long;
const int N=2e3+9;
const int mod=1e9+7;

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

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

int f[N][N],g[N],a[N],n,tot;
struct Fenwick{
	int tr[N];
	inline void Add(int x,int k){
		while(x<=tot){
			AddAs(tr[x],k);
			x+=x&-x;
		}
	}
	inline int Ask(int x){
		int sum=0;
		while(x){
			AddAs(sum,tr[x]);
			x&=x-1;
		}
		return sum;
	}
}tf[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<int> val(a,a+n+1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	val.insert(val.begin(),-1);
	tot=val.size()-1;

	Init(n);
	tf[0].Add(1,1);
	for(int i=1;i<=n;i++){
		int pos=lower_bound(val.begin(),val.end(),a[i])-val.begin();
		for(int j=i;j>=1;j--){
			f[i][j]=tf[j-1].Ask(pos);
			tf[j].Add(pos,f[i][j]);
		}
	}
	for(int i=1;i<=n;i++) g[i]=Mul(fac[n-i],tf[i].Ask(tot));
	for(int i=1;i<n;i++) SubAs(g[i],Mul(g[i+1],i+1));

	int ans=0;
	for(int i=1;i<=n;i++) AddAs(ans,g[i]);
	cout<<ans<<endl;

	return 0;
}