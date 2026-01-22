#include<bits/stdc++.h>

using namespace std;

ifstream fin("permutation.in");
ofstream fout("permutation.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=4e3+9;
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

int f[N],g[N],n,m;

signed main(){
	cin>>n>>m;
	
	f[0]=1;
	Init(2*n);
	for(int t=1;t<=(2*n)%m;t++){
		for(int k=1;k<=((2*n)/m+1)/2;k++){
			int w=Mul(C((2*n)/m+1,2*k),fac[2*k]);
			for(int i=n;i>=k;i--){
				AddAs(g[i],Mul(C(i,k),Mul(w,f[i-k])));
			}
		}
		for(int i=0;i<=n;i++) AddAs(f[i],g[i]),g[i]=0; 
	}
	for(int t=1;t<=m-(2*n)%m;t++){
		for(int k=1;k<=((2*n)/m)/2;k++){
			int w=Mul(C((2*n)/m,2*k),fac[2*k]);
			for(int i=n;i>=k;i--){
				AddAs(g[i],Mul(C(i,k),Mul(w,f[i-k])));
			}
		}
		for(int i=0;i<=n;i++) AddAs(f[i],g[i]),g[i]=0; 
	}

	int ans=0;
	for(int i=0;i<=n;i++){
		if(~i&1) AddAs(ans,Mul(C(n,i),Mul(fac[2*n-2*i],f[i])));
		else SubAs(ans,Mul(C(n,i),Mul(fac[2*n-2*i],f[i])));
	}

	cout<<ans<<endl;

	return 0;
}