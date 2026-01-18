#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
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
inline int Inv(int x){return QPow(x,mod-2);}

char s[N];
int f[N][N][4],g[N][N][4],n;
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];

	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<4;k++){
				AddAs(f[i+1][j][k],f[i][j][k]);
				AddAs(g[i+1][j][k],g[i][j][k]);
			}
			if(s[i+1]=='('){
				AddAs(f[i+1][j+1][0],f[i][j][0]);
				AddAs(g[i+1][j+1][0],Add(f[i][j][0],g[i][j][0]));
				AddAs(f[i+1][j+1][2],f[i][j][1]);
				AddAs(g[i+1][j+1][2],Add(f[i][j][1],g[i][j][1]));
				AddAs(f[i+1][j+1][3],f[i][j][2]);
				AddAs(g[i+1][j+1][3],Add(f[i][j][2],g[i][j][2]));
				AddAs(f[i+1][j+1][3],f[i][j][3]);
				AddAs(g[i+1][j+1][3],Add(f[i][j][3],g[i][j][3]));
			}else{
				if(!j) continue ;
				AddAs(f[i+1][j-1][1],f[i][j][0]);
				AddAs(g[i+1][j-1][1],Add(f[i][j][0],g[i][j][0]));
				AddAs(f[i+1][j-1][1],f[i][j][1]);
				AddAs(g[i+1][j-1][1],Add(f[i][j][1],g[i][j][1]));
				AddAs(f[i+1][j-1][2],f[i][j][2]);
				AddAs(g[i+1][j-1][2],Add(f[i][j][2],g[i][j][2]));
				AddAs(f[i+1][j-1][3],f[i][j][3]);
				AddAs(g[i+1][j-1][3],Add(f[i][j][3],g[i][j][3]));
			}
		}
	}
	
	cout<<Sub(g[n][0][3],Mul(2,f[n][0][3]))<<endl;

	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}