#include<bits/stdc++.h>

using namespace std;

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

int a[N],b[N],asum[N],bsum[N],f[N][N],g[N][N],n,vl,vr;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>vl>>vr;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	reverse(a+1,a+n+1);
	reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++) asum[i]=asum[i-1]+a[i];
	for(int i=1;i<=n;i++) bsum[i]=bsum[i-1]+b[i];

	f[1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j<=n;j++){
			int cur=vr-bsum[j]+asum[i-1];
			if(j<=n&&cur-b[j+1]>=0) AddAs(f[i][j+1],f[i][j]);
			if(i<=j) AddAs(f[i+1][j],f[i][j]);
		}
	}

	vl--;
	g[1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j<=n;j++){
			int cur=vl-bsum[j]+asum[i-1];
			if(j<=n&&cur-b[j+1]>=0) AddAs(g[i][j+1],g[i][j]);
			if(i<=j) AddAs(g[i+1][j],g[i][j]);
		}
	}

	cout<<Sub(f[n+1][n],g[n+1][n])<<endl;

	return 0;
}