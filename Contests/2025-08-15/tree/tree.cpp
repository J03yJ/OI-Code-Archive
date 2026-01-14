#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],dep[N],mxdep[N],hson[N],n,p,q;
inline void GetHSon(int x){
	hson[x]=0;
	mxdep[x]=dep[x];
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		mxdep[x]=max(mxdep[x],mxdep[y]);
		if(!hson[x]||mxdep[y]>mxdep[hson[x]]) hson[x]=y;
	}
}
int top[N];
inline void GetTop(int x,int t){
	top[x]=t;
	if(hson[x]) GetTop(hson[x],t);
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetTop(y,y);
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>p>>q;
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			AddEdge(u,v);
			AddEdge(v,u);
		}

		int root=1;
		fa[root]=0,dep[root]=1,GetHSon(root);
		for(int i=1;i<=n;i++) if(dep[i]>dep[root]) root=i;
		fa[root]=0,dep[root]=1,GetHSon(root);
		GetTop(root,root);

		ll ans=0;
		for(int i=1;i<=n;i++){
			if(i==root) continue ;
			if(top[i]!=i) continue ;
			ans+=min(ll(p)*(mxdep[i]-(dep[i]-1)),ll(q));
		}
		cout<<ans<<endl;

		for(int i=1;i<=n;i++) fi[i]=0;
		adj=0;
	}

	return 0;
}