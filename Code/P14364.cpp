#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e2+9;
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

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

int f[N][N][N],c[N],cnt[N],sum[N],n,m;
char s[N];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) cin>>c[i];

	for(int i=1;i<=n;i++) cnt[c[i]]++;
	for(int i=0;i<=n;i++){
		sum[i]=cnt[i];
		if(i) sum[i]+=sum[i-1];
	}

	Init(n);
	f[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=i;k++){
				if(!f[i][j][k]) continue ;
				int p=sum[j]-(i-k);
				if(s[i+1]=='0'){
					// AddAs(f[i+1][j+1][k],Mul(p,f[i][j][k]));
					for(int t=0;t<=min(cnt[j+1],k);t++){
						AddAs(f[i+1][j+1][k-t],Mul(Mul(p,f[i][j][k]),Mul(fac[t],Mul(C(cnt[j+1],t),C(k,t)))));
					}
					// AddAs(f[i+1][j+1][k+1],f[i][j][k]);
					for(int t=0;t<=min(cnt[j+1],k+1);t++){
						AddAs(f[i+1][j+1][k+1-t],Mul(f[i][j][k],Mul(fac[t],Mul(C(cnt[j+1],t),C(k+1,t)))));
					}
				}else{
					// AddAs(f[i+1][j+1][k],Mul(p,f[i][j][k]));
					for(int t=0;t<=min(cnt[j+1],k);t++){
						AddAs(f[i+1][j+1][k-t],Mul(Mul(p,f[i][j][k]),Mul(fac[t],Mul(C(cnt[j+1],t),C(k,t)))));
					}
					AddAs(f[i+1][j][k+1],f[i][j][k]);
				}
			}
		}
	}

	int ans=0;
	for(int j=0;j<=n-m;j++){
		int k=sum[n]-sum[j];
		AddAs(ans,Mul(f[n][j][k],fac[k]));
	}

	cout<<ans<<endl;

	return 0;
}