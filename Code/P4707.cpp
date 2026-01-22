#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e3+9;
const int M=1e4+9;
const int K=1e1+9;
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

int p[N],f[K][M],n,k,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k>>m;
	for(int i=1;i<=n;i++) cin>>p[i];

	k=n-k+1;
	for(int l=1;l<=k;l++) f[l][0]=mod-1;
	for(int i=1;i<=n;i++){
		for(int l=k;l>=1;l--){
			for(int j=m;j>=p[i];j--){
				SubAs(f[l][j],f[l][j-p[i]]);
				AddAs(f[l][j],f[l-1][j-p[i]]);
			}
		}
	}

	int ans=0;
	for(int j=1;j<=m;j++) AddAs(ans,Mul(Mul(m,Inv(j)),f[k][j]));

	cout<<ans<<endl;

	return 0;
}