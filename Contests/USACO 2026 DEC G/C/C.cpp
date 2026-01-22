#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e6+9;
const int mod=1e9+7;

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

int p[N],op[N],f[N],F[N],g[N],G[N],h[N],cnt[N],n,d;

signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>p[i]>>op[i],cnt[i]=cnt[i-1]+!op[i];

	f[0]=F[0]=g[0]=G[0]=1;
	for(int i=1;i<=n;i++){
		if(op[i]){
			int lp=lower_bound(p+1,p+n+1,p[i]-d)-p;
			AddAs(h[i],F[lp-1]);
			AddAs(h[i],Mul(Sub(G[i-1],G[lp-1]),QPow(2,cnt[i])));
			int rp=upper_bound(p+1,p+n+1,p[i]+d)-p-1;
			f[i]=Mul(h[i],QPow(2,cnt[rp]-cnt[i]));
			g[i]=Mul(h[i],QPow(2,mod-cnt[i]-1));
		}
		F[i]=Add(F[i-1],f[i]);
		G[i]=Add(G[i-1],g[i]);
	}

	cout<<Sub(F[n],1)<<endl;

	return 0;
}