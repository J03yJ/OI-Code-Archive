#include<bits/stdc++.h>

using namespace std;

ifstream fin("set.in");
ofstream fout("set.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
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

vector<int> e[N];
int siz[N],f[N][N][2][2],tmp[N][2][2],h[N][2],su[N][2][2],n;
inline void DFS(int x,int fa){
	h[x][1]=1,h[x][0]=0;
	for(int y:e[x]){
		if(y==fa) continue ;
		DFS(y,x);
		h[x][1]+=h[y][0];
		h[x][0]+=max(h[y][0],h[y][1]);
	}
	siz[x]=1;
	f[x][1][0][0]=f[x][1][1][1]=1;
	for(int y:e[x]){
		if(y==fa) continue ;
		for(int p:{0,1}) for(int q:{0,1}){
			for(int i=1;i<=siz[y];i++) su[i][p][q]=Add(su[i-1][p][q],f[y][i][p][q]);
		}
		for(int k=0;k<=siz[y];k++){
			for(int i=1;i<=siz[x];i++){
				int w=Mul(C(k+i-1,k),C(siz[y]-k+siz[x]-i,siz[y]-k));
				for(int p:{0,1}) for(int q:{0,1}){
					for(int s:{0,1}) for(int t:{0,1}){
						if(p==1&&s==1) continue ;
						if(p==0&&h[y][s]<h[y][!s]) continue ;
						if(t) AddAs(tmp[i+k][p][q|s],Mul(w,Mul(f[x][i][p][q],su[k][s][t])));
						if(p|t) AddAs(tmp[i+k][p][q],Mul(w,Mul(f[x][i][p][q],Sub(su[siz[y]][s][t],su[k][s][t]))));
					}
				}
			}
		}
		siz[x]+=siz[y];
		for(int i=1;i<=siz[x];i++){
			for(int p:{0,1}) for(int q:{0,1}) f[x][i][p][q]=exchange(tmp[i][p][q],0);
		}
		for(int p:{0,1}) for(int q:{0,1}){
			for(int i=1;i<=siz[y];i++) su[i][p][q]=0;
		}
	}
}

signed main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	Init(n);
	DFS(1,-1);

	int res=0;
	for(int p:{0,1}) for(int q:{0,1}){
		if(!q) continue ;
		if(h[1][p]<h[1][!p]) continue ;
		for(int i=1;i<=n;i++) AddAs(res,f[1][i][p][q]);
	}

	cout<<Mul(res,ifac[n])<<endl;

	return 0;
}