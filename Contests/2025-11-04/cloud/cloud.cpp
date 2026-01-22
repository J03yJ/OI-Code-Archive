#include<bits/stdc++.h>

using namespace std;

ifstream fin("cloud.in");
ofstream fout("cloud.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;
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

int f[N][N],n,m;

signed main(){
	cin>>n>>m;

	f[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=m;j++){
			AddAs(f[i+1][j],f[i][j]);
			if(j) AddAs(f[i+1][j-1],Mul(j,f[i][j]));
			if(j<m) AddAs(f[i+1][j+1],Mul(m-j,f[i][j]));
		}
	}

	cout<<f[n][m]<<endl;

	return 0;
}