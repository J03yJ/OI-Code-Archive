#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+9;
int u[N],v[N],deg[N];
vector<int> G[N];
bool vis[N];

signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i],deg[u[i]]++,deg[v[i]]++;
	for(int i=1;i<=m;i++){
		if(deg[u[i]]<deg[v[i]]||deg[u[i]]==deg[v[i]]&&u[i]<v[i]) G[u[i]].push_back(v[i]);
		else G[v[i]].push_back(u[i]);
	}
	int cnt=0;
	for(int x=1;x<=n;x++){
		for(int y:G[x]) vis[y]=1;
		for(int y:G[x]){
			for(int z:G[y]) if(vis[z]) cnt++;
		}
		for(int y:G[x]) vis[y]=0;
	}
	cout<<cnt<<endl;
}
