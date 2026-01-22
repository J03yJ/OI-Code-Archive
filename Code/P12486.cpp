#include<bits/stdc++.h>

using namespace std;

#define popc __builtin_popcount
using ll=long long;
const int N=5e1+9;
const int Q=1e1+9;
const int S=(1<<10)+9;
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

ll cst[Q];
int x[Q],y[Q],w[Q],iys[N],msk[Q],use[Q][N],f[N][N][S],g[S],n,m,q;

signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++) cin>>x[i]>>y[i]>>w[i];

	vector<int> ys(y+1,y+q+1);
	sort(ys.begin(),ys.end());
	ys.erase(unique(ys.begin(),ys.end()),ys.end());
	int yl=ys.size();

	vector<int> xs(x+1,x+q+1);
	sort(xs.begin(),xs.end());
	xs.erase(unique(xs.begin(),xs.end()),xs.end());
	int xl=xs.size();

	map<array<int,2>,int> mp;
	for(int i=1;i<=q;i++){
		int xp=lower_bound(xs.begin(),xs.end(),x[i])-xs.begin();
		int yp=lower_bound(ys.begin(),ys.end(),y[i])-ys.begin();
		cst[xp]|=1ll<<w[i];
		if(mp[{xp,w[i]}]&&mp[{xp,w[i]}]!=yp){
			cout<<0<<endl;
			return 0;
		}
		mp[{xp,w[i]}]=yp;
		msk[xp]|=1<<yp;
		use[xp][w[i]]|=1<<yp;
	}
	for(int i=0;i<xl;i++) for(int j=1;j<=n;j++) use[i][j]|=use[i][j-1];

	Init(n);
	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n-yl;j++){
			for(int sta=0;sta<(1<<yl);sta++){
				MulAs(f[i][j][sta],QPow(j+popc(sta)-(i-1),m-xl));
				for(int k=0;k<xl;k++){
					if(cst[k]>>i&1) MulAs(f[i][j][sta],sta>>mp[{k,i}]&1);
					else MulAs(f[i][j][sta],j+popc(sta^(sta&msk[k]))-(i-1-popc(sta&msk[k]&use[k][i-1])));
				}
				g[sta]=f[i][j][sta];
			}
			for(int k=0;k<yl;k++){
				for(int sta=0;sta<(1<<yl);sta++){
					if(~sta>>k&1) AddAs(g[sta|1<<k],g[sta]);
				}
			}
			for(int k=0;j+k<=n-yl;k++){
				for(int sta=0;sta<(1<<yl);sta++){
					AddAs(f[i+1][j+k][sta],Mul(C(n-yl-j,k),g[sta]));
				}
			}
		}
	}

	cout<<f[n][n-yl][(1<<yl)-1]<<endl;

	return 0;
}