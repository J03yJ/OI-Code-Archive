#include<bits/stdc++.h>

using namespace std;

ifstream fin("inso.in");
ofstream fout("inso.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
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

int ans[N],p[3],c[3],n;

inline void Solve(){
	for(int i:{0,1,2}) cin>>c[i];
	for(int i:{0,1,2}) cin>>p[i];
	cin>>n;

	Init(n);
	int res=0;
	for(int i=1;i<=n;i++){
		ans[i]=0;
		for(int x=0;x<=i;x++){
			for(int y=0;x+y<=i;y++){
				int z=i-x-y;
				AddAs(ans[i],Mul(Mul(max(max(x+c[0],y+c[1]),z+c[2]),
				Mul(Mul(QPow(p[0],x),QPow(p[1],y)),QPow(p[2],z))),
				Mul(Mul(fac[i],ifac[x]),Mul(ifac[y],ifac[z]))));
			}
		}
		res^=Mul(i,ans[i]);
	}

	cout<<res<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}