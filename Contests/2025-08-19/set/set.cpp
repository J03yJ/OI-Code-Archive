#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e2+9;
const int S=(1<<19)+9;
const int B=19;
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

int a[N],b[N],co[N][N],n,m,l,q;
inline void CalcPolyCoef(){
	for(int k=0;k<=n;k++){
		co[k][0]=1;
		for(int i=0;i<=k;i++) ;
		for(int i=1;i<=n;i++){
			for(int j=n;j>=1;j--){
				AddAs(co[k][j+1],co[k][j]);
				if(i>k) co[k][j]=Sub(mod,co[k][j]);
			}
		}
	}
}
int t[S],f[N][S][2];
inline void CalcCount(){
	for(int sta=0;sta<(1<<B);sta++){
		for(int i=1;i<=n;i++) if(__builtin_popcount(sta&a[i])&1^1) t[sta]++;
	}
	for(int k=0;k<=n;k++){
		for(int sta=0;sta<(1<<B);sta++){
			if(t[sta]==k) f[k][sta][0]++;
		}
		for(int i=0;i<B;i++){
			for(int sta=0;sta<(1<<B);sta++){
				if(sta>>i&1) continue ;
				int g[2][2]={{f[k][sta][0],f[k][sta][1]},{f[k][sta|(1<<i)][0],f[k][sta|(1<<i)][1]}};
				f[k][sta][0]=Add(g[0][0],g[1][0]);
				f[k][sta][1]=Add(g[0][1],g[1][1]);
				f[k][sta|(1<<i)][0]=Add(g[0][0],g[1][1]);
				f[k][sta|(1<<i)][0]=Add(g[0][1],g[1][0]);
			}
		}
	}
}
int g[N][N];
inline void GetPermNum(int lim){
	g[0][n]=1;
	for(int l=1;l<=lim;l++){
		for(int i=0;i<=n;i++){
			if(i<n) AddAs(g[l][i],Mul(i+1,g[l-1][i+1]));
			if(i>0) AddAs(g[l][i],Mul(n-i+1,g[l-1][i-1]));
		}
	}
}

signed main(){
	int Tid,T;
	cin>>Tid>>T;
	while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++) cin>>a[i];
		
		while(q--){
			cin>>m>>l;
			for(int i=1;i<=m;i++) cin>>b[i];
		}
	}

	return 0;
}