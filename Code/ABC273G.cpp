#include<bits/stdc++.h>

using namespace std;

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
inline int Mod(ll x){return x%mod;}
inline int F(int x){return Mod(1ll*x*(x-1)/2);}

int f[N][N],r[N],c[N],req[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>r[i];
	for(int i=1;i<=n;i++) cin>>c[i];

	int sum=0;
	for(int i=1;i<=n;i++) sum+=c[i];
	for(int i=1;i<=n;i++) req[i]=req[i-1]+r[i];
	if(req[n]!=sum){
		cout<<0<<endl;
		return 0;
	}

	int cnt=0;
	for(int i=1;i<=n;i++) if(c[i]==2) cnt++;
	f[1][cnt]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=cnt;j++){
			int c1=sum-req[i-1]-2*j,c2=j;
			if(r[i]==0) AddAs(f[i+1][j],f[i][j]);
			else if(r[i]==1){
				if(c1>0) AddAs(f[i+1][j],Mul(c1,f[i][j]));
				if(c2>0) AddAs(f[i+1][j-1],Mul(c2,f[i][j]));
			}else if(r[i]==2){
				if(c1>1) AddAs(f[i+1][j],Mul(F(c1),f[i][j]));
				if(c1>0&&c2>0) AddAs(f[i+1][j-1],Mul(Mul(c1,c2),f[i][j]));
				if(c2>1) AddAs(f[i+1][j-2],Mul(F(c2),f[i][j]));
				if(c2>0) AddAs(f[i+1][j-1],Mul(c2,f[i][j]));
			}
		}
	}

	cout<<f[n+1][0]<<endl;

	return 0;
}