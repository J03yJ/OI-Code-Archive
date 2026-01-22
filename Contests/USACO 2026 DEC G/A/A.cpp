#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

vector<int> e[N],mdf[N];
int fa[N],t[N],u[N],vis[N],now[N],n,m;
char op[N];

struct DSU{
	int fa[N],siz[N];
	inline void Init(){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;}
	inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
	inline void Merge(int x,int y){
		x=Find(x),y=Find(y);
		if(x==y) return ;
		fa[y]=x;
		siz[x]+=siz[y];
	}
}T;
inline void DFS(int x,int top){
	if(t[x]<=m) top=x;
	T.Merge(top,x);
	for(int y:e[x]) DFS(y,top);
}

int cnt[4],ans[N][4];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>fa[i];
	cin>>m;
	for(int i=1;i<=n;i++) t[i]=m+1;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>op[i];
		t[u[i]]=min(t[u[i]],i);
		mdf[u[i]].push_back(i);
		op[i]=1+int(op[i]>'C')+int(op[i]>'O');
		now[u[i]]=op[i];
	}

	for(int i=1;i<=n;i++){
		int x=i;
		while(!vis[x]){
			vis[x]=i;
			x=fa[x];
		}
		if(vis[x]!=i) continue ;
		vector<int> node;
		int y=x;
		do{
			node.push_back(y);
			y=fa[y];
		}while(y!=x);
		fa[*min_element(node.begin(),node.end(),[](int i,int j){return t[i]<t[j];})]=0;
	}
	for(int i=1;i<=n;i++) if(fa[i]) e[fa[i]].push_back(i);

	T.Init();
	for(int i=1;i<=n;i++) if(!fa[i]) DFS(i,0);
	for(int i=1;i<=n;i++) if(T.fa[i]==i) cnt[now[i]]+=T.siz[i];
	for(int i=m;i>=1;i--){
		for(int j:{1,2,3}) ans[i][j]=cnt[j];
		mdf[u[i]].pop_back();
		cnt[op[i]]-=T.siz[u[i]];
		if(mdf[u[i]].size()){
			int j=mdf[u[i]].back();
			cnt[op[j]]+=T.siz[u[i]];
			now[u[i]]=op[j];
		}else{
			cnt[now[T.Find(fa[u[i]])]]+=T.siz[u[i]];
			T.Merge(fa[u[i]],u[i]);
		}
	}

	for(int i=1;i<=m;i++){
		cout<<ans[i][1]<<' '<<ans[i][2]<<' '<<ans[i][3]<<endl;
	}

	return 0;
}