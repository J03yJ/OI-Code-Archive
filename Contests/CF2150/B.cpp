#include<bits/stdc++.h>

using namespace std;

using ll=long long;
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

const int N=3e5+9;

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

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n+1,0);
		for(int i=1;i<=n;i++) cin>>a[i];
		if(accumulate(a.begin(),a.end(),0ll)!=n){
			cout<<0<<endl;
			continue ;
		}
		bool flag=0;
		for(int i=(n+1)/2+1;i<=n;i++){
			flag|=a[i];
		}
		if(flag){
			cout<<0<<endl;
			continue ;
		}
		Init(n);
		int ans=1,sum=0;
		for(int i=(n+1)/2;i>=1;i--){
			int c=n-2*(i-1)-sum;
			MulAs(ans,C(c,a[i]));
			sum+=a[i];
		}
		cout<<ans<<endl;
	}

	return 0;
}