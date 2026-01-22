#include<bits/stdc++.h>

using namespace std;

ifstream fin("eri.in");
ofstream fout("eri.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;

inline void AddAs(int &x,int y,int mod){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y,int mod){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y,int mod){x=1ll*x*y%mod;}
inline int Add(int x,int y,int mod){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y,int mod){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y,int mod){return 1ll*x*y%mod;}
inline int QPow(int x,int y,int mod){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x,mod);
		MulAs(x,x,mod);
		y>>=1;
	}
	return res;
}

int s[N][N],c[N][N],p2[N*N],p22[N],f[N],n,mod;

signed main(){
	cin>>n>>mod;

	p2[0]=1;
	for(int i=1;i<=n*n;i++) p2[i]=Add(p2[i-1],p2[i-1],mod);
	for(int i=0;i<=n;i++) p22[i]=QPow(2,QPow(2,i,mod-1),mod);
	for(int i=0;i<=n;i++){
		c[i][0]=1,s[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=Add(c[i-1][j],c[i-1][j-1],mod);
			s[i][j]=Add(Mul(j+1,s[i-1][j],mod),s[i-1][j-1],mod);
		}
	}

	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++) AddAs(f[i],Mul(s[i][j],p2[(n-i)*j],mod),mod);
	}

	int ans=0;
	for(int i=0;i<=n;i++){
		int tmp=Mul(Mul(f[i],p22[n-i],mod),c[n][i],mod);
		if(i&1) SubAs(ans,tmp,mod);
		else AddAs(ans,tmp,mod);
	}

	cout<<ans<<endl;
	
	return 0;
}