#include<bits/stdc++.h>

using namespace std;

ifstream fin("dtree.in");
ofstream fout("dtree.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
int n,mod;

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
	cin>>n>>mod;

	Init(n);

	vector<int> c(n+1,0);
	c[n]=1;
	int sum=Mul(c[n],fac[n-1]);
	for(int i=n-1;i;i--){
		c[i]=Mul(2,Mul(sum,ifac[i]));
		AddAs(sum,Mul(c[i],fac[i-1]));
	}

	int ans=0;
	for(int i=3;i<=n;i++){
		int t=Mul(fac[i-1],1ll*(i+1)*(i-2)/2%mod);
		AddAs(ans,Mul(t,c[i]));
	}

	cout<<ans<<endl;

	return 0;
}