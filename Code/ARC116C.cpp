#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=4e5+9;
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

int a[N],n,m;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=0;
	Init(4e5);
	for(int i=1;i<=m;i++){
		vector<array<int,2>> ps;
		int tmp=i;
		for(int j=2;j*j<=tmp;j++){
			int cnt=0;
			while(tmp%j==0) cnt++,tmp/=j;
			if(cnt) ps.push_back({j,cnt});
		}
		if(tmp!=1) ps.push_back({tmp,1});
		int res=1;
		for(auto t:ps) MulAs(res,C(n+t[1]-1,t[1]));
		AddAs(ans,res);
	}

	cout<<ans<<endl;

	return 0;
}