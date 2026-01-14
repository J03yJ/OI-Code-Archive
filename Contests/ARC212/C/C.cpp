#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e7+9;
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
inline int Inv(int x){return QPow(x,mod-2);}

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
inline int F(int n,int m){
	if(n<0||m<0) return 0;
	else return C(n+m-1,2*m-1);
}

signed main(){
	Init(2e7);

	int n,m;
	cin>>n>>m;

	int tmp=QPow(2,m),ans=0;
	for(int c=0;c<=n;c++){
		int res=Mul(tmp,Mul(C(c+m-1,m-1),F(n-2*c,m)));
		AddAs(ans,res);
	}

	cout<<ans<<endl;

	return 0;
}