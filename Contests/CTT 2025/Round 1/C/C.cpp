#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e5+9;

int n,m,o;
vector<array<int,2>> e[N];
ll a[N],d[N];

ll siz[N];
int fa[N];
inline void Init(int lim){for(int i=1;i<=lim;i++) fa[i]=i;}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	fa[y]=x;
}

int vis[N];
vector<int> p[N];
inline bool Check(vector<int> node){
	int cnt=0;
	queue<int> q;
	for(int x:node) if(a[x]>=d[x]) vis[x]=1,q.push(x);
	while(q.size()){
		int x=q.front();
		q.pop();
		cnt++;
		for(auto t:e[x]){
			int y=t[0];
			a[x]-=t[1],a[y]+=t[1];
			if(!vis[y]&&a[y]>=d[y]) vis[y]=1,q.push(y);
		}
	}
	return cnt==node.size();
}

signed main(){
	cin>>o>>n>>m;
	Init(n);
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		if(!w) continue ;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
		d[u]+=w,d[v]+=w;
		Merge(u,v);
		siz[Find(u)]+=w;
	}

	if(o==1){
		int x=0;
		for(int i=1;i<=n;i++){
			if(i!=fa[i]) continue ;
			if(!x||siz[i]<siz[x]) x=i;
		}
		for(int i=1;i<=n;i++){
			if(Find(i)!=x) continue ;
			for(auto t:e[i]){
				if(Find(t[0])!=x) continue ;
				if(i<t[0]) a[i]+=t[1];
			}
		}
		for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
	}else{
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) p[Find(i)].push_back(i);
		for(int i=1;i<=n;i++){
			if(i!=fa[i]) continue ;
			if(Check(p[i])){
				cout<<"YES"<<endl;
				return 0;
			}
		}
		cout<<"NO"<<endl;
	}

	return 0;
}