#include<bits/stdc++.h>

using namespace std;

ifstream fin("walk.in");
ofstream fout("walk.out");
#define cin fin
#define cout fout

const int N=2e5+9;

vector<int> e[N],g[N];
int dis[N],fa[N],vis[N],on[N],n,m,k;
inline void DFS(int x){
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dis[y]=dis[x]+1;
		DFS(y);
	}
}
inline void Get(int x,vector<int> &ans){
	ans.push_back(x);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(on[y]&&vis[y]==1){
			Get(y,ans);
			ans.push_back(x);
		}
	}
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(on[y]&&vis[y]==-1) Get(y,ans);
	}
}

inline void Solve(){
	cin>>n>>m>>k;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	fa[1]=0,dis[1]=1,DFS(1);
	int p=max_element(dis+1,dis+n+1)-dis;
	fa[p]=0,dis[p]=1,DFS(p);
	int q=max_element(dis+1,dis+n+1)-dis;
	
	int len=dis[q];
	int res=min(len,k)+2*max(k-len,0);

	if(m<res) cout<<"No"<<endl;
	else{
		cout<<"Yes"<<endl;
		if(k<=len){
			vector<int> node;
			for(int i=1,x=q;i<=k;i++,x=fa[x]) node.push_back(x);
			
			vector<int> ans;
			for(int i=0,typ=1;ans.size()<m;i+=typ){
				ans.push_back(node[i]);
				if(i+typ<0||i+typ>=node.size()) typ*=-1;
			}

			for(int x:ans) cout<<x<<' ';cout<<endl;
		}else{
			vector<int> node;
			for(int i=1,x=q;i<=len;i++,x=fa[x]) node.push_back(x);
			
			int cnt=0;
			queue<int> q;
			for(int x:node) q.push(x),vis[x]=-1;
			while(q.size()){
				int x=q.front();
				q.pop();
				if(cnt<k){
					on[x]=1;
					if(++cnt==k) break ;
				}
				for(int y:e[x]){
					if(vis[y]) continue ;
					q.push(y);
					vis[y]=1;
				}
			}

			vector<int> ans;
			Get(p,ans);
			for(int i=1,typ=1;ans.size()<m;i+=typ){
				ans.push_back(node[i]);
				if(i+typ<0||i+typ>=node.size()) typ*=-1;
			}

			for(int x:ans) cout<<x<<' ';cout<<endl;
		}
	}

	for(int i=1;i<=n;i++) fa[i]=dis[i]=vis[i]=on[i]=0,e[i].clear(),g[i].clear();
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}