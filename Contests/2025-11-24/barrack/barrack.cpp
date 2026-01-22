#include<bits/stdc++.h>

using namespace std;

ifstream fin("barrack.in");
ofstream fout("barrack.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
const int M=1e2+9;
template<class T> inline void ChMin(T &x,T y){if(y<x) x=y;}

vector<array<int,2>> e[N];
ll f[N][M][M][2],g[M][M][2],pf[M][2],sf[M][2];
int fa[N],siz[N],psiz[N],a[N],n,m,k;
inline void DFS(int x,int o){
	siz[x]=1;
	f[x][0][0][0]=f[x][1][0][1]=0;
	for(auto t:e[x]){
		int y=t[0],w=t[1];
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y,w);
		for(int j=0;j<=min(siz[x]+siz[y],m);j++){
			for(int p=0;p<=k;p++){
				for(int q:{0,1}) g[j][p][q]=0x3f3f3f3f3f3f3f3f;
			}
		}
		for(int i=0;i<=min(siz[x],m);i++){
			for(int j=0;j<=min(siz[y],m-i);j++){
				// for(int p=0;p<=k;p++){
				// 	for(int q=0;q<=k;q++){
				// 		ChMin(g[i+j][max(p,q+1)][0],f[x][i][p][0]+f[y][j][q][0]);
				// 		ChMin(g[i+j][min(p,q+1)][1],f[x][i][p][1]+f[y][j][q][1]);
				// 		if(p+q+1<=k){
				// 			ChMin(g[i+j][p][1],f[x][i][p][1]+f[y][j][q][0]);
				// 			ChMin(g[i+j][q+1][1],f[x][i][p][0]+f[y][j][q][1]);
				// 		}else{
				// 			ChMin(g[i+j][q+1][0],f[x][i][p][1]+f[y][j][q][0]);
				// 			ChMin(g[i+j][p][0],f[x][i][p][0]+f[y][j][q][1]);
				// 		}
				// 	}
				// }
				for(int c:{0,1}) pf[k+1][c]=sf[k+1][c]=0x3f3f3f3f3f3f3f3f;
				for(int p=0;p<=k;p++) for(int c:{0,1}) pf[p][c]=sf[p][c]=f[x][i][p][c];
				for(int p=1;p<=k+1;p++) for(int c:{0,1}) ChMin(pf[p][c],pf[p-1][c]);
				for(int p=k;p>=0;p--) for(int c:{0,1}) ChMin(sf[p][c],sf[p+1][c]);
				for(int q=0;q<=k;q++){
					ChMin(g[i+j][q+1][0],pf[q+1][0]+f[y][j][q][0]);
					ChMin(g[i+j][q+1][1],sf[q+1][1]+f[y][j][q][1]);
					ChMin(g[i+j][q+1][1],pf[k-q-1][0]+f[y][j][q][1]);
					ChMin(g[i+j][q+1][0],sf[k-q][1]+f[y][j][q][0]);
				}
				for(int c:{0,1}) pf[0][c]=sf[0][c]=0x3f3f3f3f3f3f3f3f;
				for(int q=0;q<=k;q++) for(int c:{0,1}) pf[q+1][c]=sf[q+1][c]=f[y][j][q][c];
				for(int q=1;q<=k+1;q++) for(int c:{0,1}) ChMin(pf[q][c],pf[q-1][c]);
				for(int q=k;q>=0;q--) for(int c:{0,1}) ChMin(sf[q][c],sf[q+1][c]);
				for(int p=0;p<=k;p++){
					ChMin(g[i+j][p][0],f[x][i][p][0]+pf[p][0]);
					ChMin(g[i+j][p][1],f[x][i][p][1]+sf[p][1]);
					ChMin(g[i+j][p][1],f[x][i][p][1]+pf[k-p][0]);
					ChMin(g[i+j][p][0],f[x][i][p][0]+sf[k-p+1][1]);
				}
			}
		}
		siz[x]+=siz[y];
		psiz[x]+=psiz[y];
		for(int j=0;j<=min(siz[x],m);j++){
			for(int p=0;p<=k;p++){
				for(int q:{0,1}) f[x][j][p][q]=g[j][p][q];
			}
		}
	}
	for(int j=0;j<=min(siz[x],m);j++){
		for(int p=0;p<=k;p++){
			for(int q:{0,1}) f[x][j][p][q]+=1ll*o*abs(j-psiz[x]);
		}
	}
}

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) cin>>a[i],psiz[a[i]]++;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}

	memset(f,0x3f,sizeof f);
	DFS(1,0);

	ll ans=0x3f3f3f3f3f3f3f3f;
	for(int p=0;p<=k;p++) ans=min(ans,f[1][m][p][1]);

	if(ans>=0x3f3f3f3f3f3f3f3f) cout<<-1<<endl;
	else cout<<ans<<endl;

	return 0;
}