#include<bits/stdc++.h>

using namespace std;

ifstream fin("rebuild.in");
ofstream fout("rebuild.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

int afa[N],bfa[N],n,k;
vector<int> at[N],bt[N];
inline void DFS(int x,int *fa,vector<int> *t){
	for(int y:t[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y,fa,t);
	}
}

int f[N][2];
inline void Work(int x){
	vector<int> son;
	for(int y:at[x]){
		if(y==afa[x]) continue ;
		Work(y);
		if(bfa[y]==x) for(int k:{0,1}) f[x][k]+=f[y][0];
		else son.push_back(y);
	}
	if(!son.size()) f[x][1]++;
	else{
		sort(son.begin(),son.end(),[](int i,int j){
			return f[i][1]-f[i][0]>f[j][1]-f[j][0];
		});
		int m=son.size();
		son.insert(son.begin(),0);
		vector<int> pre(m+2,0),suf(m+2,0);
		for(int i=1;i<=m;i++) pre[i]=pre[i-1]+f[son[i]][0];
		for(int i=m;i>=1;i--) suf[i]=suf[i+1]+f[son[i]][1];
		int g[2]={suf[1],suf[1]+1};
		for(int i=1;i<=m;i++){
			int p=min(i*k,m);
			g[0]=min(g[0],i+pre[p]+suf[p+1]);
			int q=min(i*k-1,m);
			g[1]=min(g[1],i+pre[q]+suf[q+1]);
		}
		for(int k:{0,1}) f[x][k]+=g[k];
	}
	f[x][0]=min(f[x][0],f[x][1]);
}

signed main(){
	cin>>n>>k;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		at[u].push_back(v);
		at[v].push_back(u);
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		bt[u].push_back(v);
		bt[v].push_back(u);
	}

	DFS(1,afa,at);
	DFS(1,bfa,bt);
	Work(1);

	cout<<f[1][0]<<endl;

	return 0;
}