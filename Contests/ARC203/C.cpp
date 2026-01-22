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

const int INV2=Inv(2);

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

inline int F(int i,int j){
	int ans=C(i-2+j-1,j-1);
	MulAs(ans,j-1);
	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	Init(4e5);

	int T;
	cin>>T;
	while(T--){
		int n,m,k;
		cin>>n>>m>>k;
		k-=n+m-2;
		if(k<0) cout<<0<<endl;
		else if(k==0) cout<<C(n+m-2,n-1)<<endl;
		else if(k==1){
			int tmp=Add(Mul(n,m-1),Mul(m,n-1));
			SubAs(tmp,n+m-2);
			cout<<Mul(C(n+m-2,n-1),tmp)<<endl;
		}else if(k==2){
			int tmp=Add(Mul(n,m-1),Mul(m,n-1));
			SubAs(tmp,n+m-2);
			int ans=Mul(C(n+m-2,n-1),Mul(Mul(tmp,Sub(tmp,1)),INV2));
			SubAs(ans,F(n,m));
			AddAs(ans,Mul(C(n+m-2,n+1),n-1));
			AddAs(ans,Mul(C(n+m-2,m+1),m-1));
			cout<<ans<<endl;
		}
	}
	
	return 0;
}