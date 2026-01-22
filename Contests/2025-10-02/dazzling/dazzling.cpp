#include<bits/stdc++.h>

using namespace std;

ifstream fin("dazzling.in");
ofstream fout("dazzling.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int S=5e2+9;
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

int f[N][S*3],g[S][N<<1],n,w,B,T;

signed main(){
	cin>>n>>w;

	sizeof f;
	
	B=sqrt(n)*1.5,T=sqrt(n)*4;
	for(int i=1;i<=B;i++) f[i][i]=1;
	for(int i=0;i<=n;i++){
		for(int j=1;j<T;j++){
			if(i+j+1<=n) AddAs(f[i+j+1][j+1],Mul(w,f[i][j]));
			if(i+j-1<=n) AddAs(f[i+j-1][j-1],f[i][j]);
		}
	}
	g[1][N+0]=1;
	for(int i=1;i<T;i++){
		for(int j=-n;j<=n;j++){
			if(j+i<=n) AddAs(g[i+1][N+j+i],Mul(w,g[i][N+j]));
			if(j-i>=-n) AddAs(g[i+1][N+j-i],g[i][N+j]);
		}
	}
	
	int ans=0;
	for(int i=1;i<=T;i++) AddAs(ans,f[n][i]);
	for(int i=1;i<T;i++){
		for(int j=-n;j<=n;j++){
			if((n-j)%i) continue ;
			int p=(n-j)/i;
			if(p<=B) continue ;
			if(p>B) AddAs(ans,g[i][N+j]);
		}
	}

	cout<<ans<<endl;

	return 0;
}