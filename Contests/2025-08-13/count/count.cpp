#include<bits/stdc++.h>

using namespace std;

ifstream fin("count.in");
ofstream fout("count.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e2+9;
int f[N][N][N],g[N][N],q,n,m,mod;

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

signed main(){
	cin>>mod>>q;
	memset(f,0,sizeof f);
	n=100;
	Init(n);
	f[1][1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=0;k<j;k++){
				for(int p=max(1,k);p<=j;p++){
					AddAs(f[i+1][j][max(k,p-1)],f[i][j][k]);
				}
				for(int p=max(0,k);p<=j;p++){
					AddAs(f[i+1][j+1][max(k,p)],f[i][j][k]);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=0;k<j;k++){
				AddAs(g[i][j],f[i][j][k]);
			}
		}
	}
	while(q--){
		cin>>n>>m;
		int ans=0,tmp=1;
		for(int i=1;i<=n;i++){
			MulAs(tmp,m+1-i+1);
			AddAs(ans,Mul(Mul(tmp,ifac[i]),g[n][i]));
		}
		cout<<ans<<endl;
	}

	return 0;
}