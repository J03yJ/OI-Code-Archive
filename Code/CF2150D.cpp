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

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n+1,0);
		for(int i=1;i<=n;i++) cin>>a[i];
		
		Init(n);
		vector<int> sum(n+1,0),ssum(n+1,0);
		for(int i=1;i<=n;i++) sum[i]=Add(sum[i-1],a[i]);
		for(int i=1;i<=n;i++) ssum[i]=Add(ssum[i-1],sum[i]);

		int ans=Mul(n,sum[n]);
		for(int len=2;len<=n;len++){
			for(int lx:{0,1}){
				for(int rx:{0,1}){
					int s=n-len-lx-rx;
					if(s<0) continue ;
					if(s&1) continue ;
					s>>=1;
					AddAs(ans,Mul(Sub(ssum[n],Add(ssum[n-len],ssum[len-1])),Mul(C(s+len-1,len-1),Mul(2*s,Inv(len))+1)));
					AddAs(ans,Mul(sum[n-len+1],Mul(lx,C(s+len-1,len-1))));
					AddAs(ans,Mul(Sub(sum[n],sum[len-1]),Mul(rx,C(s+len-1,len-1))));
				}
			}
		}

		cout<<ans<<endl;
	}

	return 0;
}