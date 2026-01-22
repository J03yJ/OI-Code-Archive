#include<bits/stdc++.h>

using namespace std;

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

const int N=1e2+9;

int a[N],cnt[N],su[N],f[N][N*N],g[N][N*N],n,m;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]++;
	
	int t=n*n;
	m+=n*(n+1)/2;
	
	int sum=0;
	for(int i=1;i<=n;i++) sum+=a[i],cnt[min(a[i],n)]++;
	for(int i=1;i<=n;i++) su[i]=su[i-1]+cnt[i];

	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int p=0;p<cnt[i];p++){
			for(int j=0;j<=su[i-1]+p;j++){
				int lft=(i-1)-(su[i-1]+p-j);
				for(int k=0;k<=t;k++){
					AddAs(g[j][k],Mul(lft,f[j][k]));
					AddAs(g[j+1][k],f[j][k]);
				}
			}
			memcpy(f,g,sizeof g);
			memset(g,0,sizeof g);
		}
		for(int j=0;j<=su[i];j++){
			for(int k=0;k<=t;k++){
				if(j) AddAs(g[j-1][k],Mul(j,f[j][k]));
				AddAs(g[j][k],f[j][k]);
			}
		}
		memcpy(f,g,sizeof g);
		memset(g,0,sizeof g);
		for(int j=0;j<=su[i];j++){
			for(int k=j;k<=t;k++){
				AddAs(g[j][k],f[j][k-j]);
			}
		}
		memcpy(f,g,sizeof g);
		memset(g,0,sizeof g);
	}

	int ans=0;
	for(int i=0;i<=t;i++) if(i+sum<=m) AddAs(ans,f[0][i]);

	cout<<ans<<endl;

	return 0;
}