#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int d[N],n;
vector<int> e[N],g[N];

int c[N],fa[N];
inline void DFS(int x){
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		if(c[y]) g[y].push_back(x),d[x]++;
		else g[x].push_back(y),d[y]++;
		c[x]^=c[y];
	}
} 

signed main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		char ch;
		cin>>ch;
		c[i]=(ch=='W');
	}

	DFS(1);
	if(!c[1]){
		cout<<-1<<endl;
		return 0;
	}

	priority_queue<int> q;
	for(int i=1;i<=n;i++) if(!d[i]) q.push(-i);
	while(q.size()){
		int x=-q.top();
		q.pop();
		cout<<x<<' ';
		for(int y:g[x]) if(!--d[y]) q.push(-y);
	}
	cout<<endl;

	return 0;
}