#include<bits/stdc++.h>

using namespace std;

ifstream fin("west.in");
ofstream fout("west.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
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

int f[N][N],a[N],b[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	f[n][n]=1;
	Init(n<<1);
	for(int i=n;i>=1;i--){
		for(int j=n;j>=1;j--){
			AddAs(f[i][j],Add(f[i+1][j],f[i][j+1]));
			if(a[i]!=b[j]) continue ;
			for(int d=1,c=0;max(i,j)+d<=n;d++){
				if(a[i+d]!=b[j+d]) continue ;
				SubAs(f[i][j],Mul(c?QPow(2,c-1):1,f[i+d][j+d]));
				c++;
			}
		}
	}

	cout<<f[1][1]<<endl;

	return 0;
}