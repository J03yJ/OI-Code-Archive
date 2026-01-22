#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
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

int n;
vector<int> e1[N],e2[N];

int f[N][2];
inline void Work(int x,int fa){
	f[x][0]=1,f[x][1]=0;
	for(int y:e1[x]){
		if(y==fa) continue ;
		Work(y,x);
		f[x][1]=Add(Mul(f[x][0],f[y][0]),Mul(f[x][1],Add(f[y][0],f[y][1])));
		f[x][0]=Mul(f[x][0],Add(f[y][0],f[y][1]));
	}
}

inline void Clear(){
	for(int i=1;i<=n;i++){
		e1[i].clear(),e2[i].clear();
	}
}
inline void Solve(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e1[u].push_back(v);
		e1[v].push_back(u);
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e2[u].push_back(v);
		e2[v].push_back(u);
	}

	Work(1,-1);

	cout<<Add(f[1][0],f[1][1])<<endl;

	Clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}