#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e2+9;
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
#define Inv(x) QPow(x,mod-2)

int f[N][N][N],l[N],r[N],c[N],n,m;
vector<int> q[N];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>l[i]>>r[i]>>c[i],q[r[i]].push_back(i);

	int ans=0;
	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<max(i,1);j++){
			for(int k=0;k<max(j,1);k++){
				bool err=0;
				for(int p:q[i]){
					int x=int(i>=l[p])+int(j>=l[p])+int(k>=l[p]);
					err|=x!=c[p];
				}
				if(err){
					f[i][j][k]=0;
					continue ;
				}
				AddAs(f[i+1][i][j],f[i][j][k]);
				AddAs(f[i+1][j][k],f[i][j][k]);
				AddAs(f[i+1][i][k],f[i][j][k]);
				if(i==n) AddAs(ans,f[i][j][k]);
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}