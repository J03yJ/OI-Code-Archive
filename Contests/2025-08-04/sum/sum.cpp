#include<bits/stdc++.h>

using namespace std;

ifstream fin("sum.in");
ofstream fout("sum.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
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

int p[N],h[N],f[N][N],n;

signed main(){
	cin>>n;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		p[i]=Mul(x,Inv(y));
	}
	for(int i=0;i<=n;i++) cin>>h[i];
	
	for(int i=0;i<=n;i++) f[0][i]=h[i];
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			AddAs(f[i][j],Mul(p[i],f[i-1][j+1]));
			AddAs(f[i][j],Mul(Sub(1,p[i]),f[i-1][max(j-1,0)]));
		}
	}

	for(int i=1;i<=n;i++) cout<<f[i][0]<<' ';cout<<endl;

	return 0;
}