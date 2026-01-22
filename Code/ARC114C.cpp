#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
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

const int N=5e3+9;

int pw[N][N],n,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;

	for(int i=0;i<=m;i++) pw[i][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) pw[i][j]=Mul(pw[i][j-1],i);
	}

	int ans=Mul(n,pw[m][n]);
	for(int l=2;l<=n;l++){
		int sum=0;
		for(int j=0;j<m;j++) AddAs(sum,pw[j][l-2]);
		SubAs(ans,Mul(Mul(n-l+1,pw[m][n-l]),sum));
	}

	cout<<ans<<endl;

	return 0;
}