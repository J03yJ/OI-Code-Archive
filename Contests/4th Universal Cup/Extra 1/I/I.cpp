#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int a[N][N],n;
vector<int> e[N];

int vis[N];
inline void DFS(int x){
	vis[x]=1;
	for(int y:e[x]){
		if(vis[y]) continue ;
		cout<<x<<' '<<y<<endl;
		DFS(y);
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++) cin>>a[i][j];
	}

	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i][j]==(a[i][i]^a[j][j])){
				e[i].push_back(j);
				e[j].push_back(i);
			}
		}
	}

	DFS(1);

	return 0;
}