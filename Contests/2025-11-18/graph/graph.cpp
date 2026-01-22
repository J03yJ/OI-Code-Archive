#include<bits/stdc++.h>

using namespace std;

ifstream fin("graph.in");
ofstream fout("graph.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=3e5+9;
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

int d[N],n,m;

signed main(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		d[u]++,d[v]++;
	}

	int ans=0;
	for(int i=1;i<=n;i++) AddAs(ans,Mul(Sub(d[i]+1,1),Inv(d[i]+1)));
	cout<<ans<<endl;

	return 0;
}