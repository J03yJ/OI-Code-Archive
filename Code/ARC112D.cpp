#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e3+9;

int a[N][N],fa[N*N],vis[N*N],n,m;
inline int Id(int i,int j){return (i-1)*m+j;}
inline void Init(){iota(fa+1,fa+n*m+1,1);}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			a[i][j]=(c=='#');
		}
	}

	Init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!a[i][j]) continue ;
			for(int k=i-1;k;k--){
				if(!a[k][j]) continue ;
				Merge(Id(k,j),Id(i,j));
				break ;
			}
			for(int k=j-1;k;k--){
				if(!a[i][k]) continue ;
				Merge(Id(i,k),Id(i,j));
				break ;
			}
		}
	}

	int rcnt=0;
	for(int i=1;i<=max(n,m);i++){
		if(a[1][i]) vis[Find(Id(1,i))]=1;
		if(a[n][i]) vis[Find(Id(n,i))]=1;
		if(a[i][1]) vis[Find(Id(i,1))]=1;
		if(a[i][m]) vis[Find(Id(i,m))]=1;
	}
	for(int i=2;i<n;i++){
		int flag=0;
		for(int j=1;j<=m;j++) if(a[i][j]) flag|=vis[Find(Id(i,j))];
		if(flag) continue ;
		rcnt++;
		for(int j=1;j<=m;j++) if(a[i][j]) vis[Find(Id(i,j))]=1;
	}
	for(int i=1;i<=n*m;i++) vis[i]=0;
	int ccnt=0;
	for(int i=1;i<=max(n,m);i++){
		if(a[1][i]) vis[Find(Id(1,i))]=1;
		if(a[n][i]) vis[Find(Id(n,i))]=1;
		if(a[i][1]) vis[Find(Id(i,1))]=1;
		if(a[i][m]) vis[Find(Id(i,m))]=1;
	}
	for(int j=2;j<m;j++){
		int flag=0;
		for(int i=1;i<=n;i++) if(a[i][j]) flag|=vis[Find(Id(i,j))];
		if(flag) continue ;
		ccnt++;
		for(int i=1;i<=n;i++) if(a[i][j]) vis[Find(Id(i,j))]=1;
	}

	cout<<min(rcnt,ccnt)<<endl;

	return 0;
}