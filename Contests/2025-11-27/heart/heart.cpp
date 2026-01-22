#include<bits/stdc++.h>

using namespace std;

ifstream fin("heart.in");
ofstream fout("heart.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
const int mod=998244353;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return y;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return y;}
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

vector<int> e[N];
int fa[N],siz[N],f[N][N],g[N][N];
inline void DFS(int x){
	f[x][1]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);

		siz[x]+=siz[y];
	}
}

signed main(){
	return 0;
}