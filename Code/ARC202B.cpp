#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int mod=998244353;
const int N=2e5+9;

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

int fac[N<<1],ifac[N<<1];
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

int n,m;

signed main(){
	cin>>n>>m;

	Init(n<<1);
	if(~n&1) cout<<0<<endl;
	else if(m&1){
		int ans=0;
		for(int i=-n;i<=n;i++){
			if(n-i&1) continue ;
			if(__gcd(abs(i),m)>1) continue ;
			AddAs(ans,C(n,(n-i)/2));
		}
		cout<<ans<<endl;
	}else{
		int ans=0;
		for(int i=-2*n;i<=2*n;i++){
			if(2*n-i&1) continue ;
			if(__gcd(abs(i/2),m/2)>1) continue ;
			AddAs(ans,C(2*n,(2*n-i)/2));
		}
		cout<<ans<<endl;
	}

	return 0;
}