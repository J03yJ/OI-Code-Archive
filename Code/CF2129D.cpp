#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int K=12;
const int N=1e2+9;
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

int f[N][N][K][K],ls[N][N][K],rs[N][N][K],a[N],lim[N],n;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];

		Init(n);
		for(int i=1;i<=n+1;i++) f[i][i-1][0][0]=ls[i][i-1][0]=rs[i][i-1][0]=1;
		for(int len=1;len<=n;len++){
			for(int l=1;l<=n-len+1;l++){
				int r=l+len-1;
				for(int p=l;p<=r;p++){
					int t[2]={0,0};
					if(l==1&&r==n) ;
					else if(l==1) t[1]=1;
					else if(r==n) t[0]=1;
					else t[p>(l+r>>1)]=1;
					if(~a[p]){
						for(int _i=0;_i<min(a[p]+1,K);_i++){
							int _j=a[p]-_i;
							for(int i=0;i<K;i++){
								for(int j=0;j<K;j++){
									AddAs(f[l][r][i+t[0]][j+t[1]],Mul(Mul(f[l][p-1][i][_i],f[p+1][r][_j][j]),C(len-1,p-l)));
								}
							}
						}
					}else{
						for(int i=0;i<K;i++){
							for(int j=0;j<K;j++){
								AddAs(f[l][r][i+t[0]][j+t[1]],Mul(Mul(rs[l][p-1][i],ls[p+1][r][j]),C(len-1,p-l)));
							}
						}
					}
				}
				for(int i=0;i<K;i++){
					for(int j=0;j<K;j++){
						AddAs(ls[l][r][j],f[l][r][i][j]);
						AddAs(rs[l][r][i],f[l][r][i][j]);
					}
				}
			}
		}
		
		cout<<f[1][n][0][0]<<endl;

		for(int l=1;l<=n;l++) for(int r=l-1;r<=n;r++) for(int i=0;i<K;i++) for(int j=0;j<K;j++) f[l][r][i][j]=0;
	}

	return 0;
}