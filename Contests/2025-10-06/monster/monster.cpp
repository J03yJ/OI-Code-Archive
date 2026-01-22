#include<bits/stdc++.h>

using namespace std;

ifstream fin("monster.in");
ofstream fout("monster.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int mod=1e9+7;
const int inv2=mod+1>>1;

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

int fac[N],ifac[N],p2[N],p3[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
	p2[0]=1;
	for(int i=1;i<=lim;i++) p2[i]=Mul(p2[i-1],2);
	p3[0]=1;
	for(int i=1;i<=lim;i++) p3[i]=Mul(p3[i-1],3);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

int a[N],n;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		
		Init(n);
		int ans=0;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			AddAs(ans,Mul(a[i],p2[n-i]));
			AddAs(ans,Mul(a[i],Mul(p2[n-i],Mul(inv2,Sub(p3[i-1],1)))));
		}

		cout<<ans<<endl;
	}

	return 0;
}