#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=6e3+9;
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

vector<int> e[N];
int fa[N],siz[N],f[N][N][2][2],g[N][2][2];
inline void DFS(int x){
	siz[x]=1;
	f[x][1][1][0]=f[x][0][0][0]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		for(int i=0;i<=siz[x];i++){
			for(int j=0;j<=siz[y];j++){
				for(int p:{0,1}){
					for(int q:{0,1}){
						AddAs(g[i+j][p][1],Mul(f[x][i][p][1],f[y][j][q][1]));
						AddAs(g[i+j][p][0],Mul(f[x][i][p][0],f[y][j][q][1]));
						if(q) AddAs(g[i+j][p][1],Mul(f[x][i][p][1],f[y][j][q][0]));
						if(p^q) AddAs(g[i+j][p][1],Mul(f[x][i][p][0],f[y][j][q][0]));
						else if(p|q) AddAs(g[i+j][p][0],Mul(f[x][i][p][0],f[y][j][q][0]));
					}
				}
			}
		}
		siz[x]+=siz[y];
		for(int i=0;i<=siz[x];i++){
			for(int p:{0,1}){
				for(int q:{0,1}){
					f[x][i][p][q]=g[i][p][q];
					g[i][p][q]=0;
				}
			}
		}
	}
}

vector<int> solve(int n,vector<int> u,vector<int> v){
	for(int i=0;i<n-1;i++){
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}

	DFS(0);
	vector<int> ans(n+1,0);
	for(int i=0;i<=n;i++){
		for(int p:{0,1}) for(int q:{0,1}) if(p|q) AddAs(ans[i],f[0][i][p][q]);
	}

	return ans;
}

signed main(){
	int n;
	cin>>n;
	vector<int> u(n-1,0),v(n-1,0);
	for(int i=0;i<n-1;i++) cin>>u[i]>>v[i];

	vector<int> ans=solve(n,u,v);

	for(int x:ans) cout<<x<<' ';cout<<endl;

	return 0;
}