#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e3+9;

int f[N][N],su[N][N],suj[N][N],n,k,mod;
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

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k>>mod;
		
		su[0][0]=f[0][0]=1;
		for(int i=1;i<=k;i++) su[0][i]=Add(su[0][i-1],f[0][i]);
		for(int i=1;i<=n;i++){
			for(int j=0;j<=k;j++){
				f[i][j]=su[i-1][k];
				if(i>1) SubAs(f[i][j],Sub(Mul(Sub(k,j),su[i-2][k-j]),suj[i-2][k-j]));
				su[i][j]=Add(j?su[i][j-1]:0,f[i][j]);
				suj[i][j]=Add(j?suj[i][j-1]:0,Mul(f[i][j],j));
			}
		}
		
		int ans=su[n][k];
		SubAs(ans,Sub(Mul(k,su[n-1][k]),suj[n-1][k]));

		cout<<ans<<endl;
	}
	
	return 0;
}