#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=6e3+9;
const int M=1e4+9;

vector<int> e[N],sc[N],ans[M];
int u[M],v[M],c[M],id[N],fa[N],dep[N],vis[N],f[N][10],n,m;
inline void CalcF(int x){
	int p=8;
	vis[x]=1;
	f[x][8]=1;
	for(int i:e[x]){
		int y=x^u[i]^v[i];
		if(vis[y]) continue ;
		fa[y]=x;
		id[y]=i;
		dep[y]=dep[x]+1;
		CalcF(y);
		for(int j=1;j<8;j++){
			f[x][j]+=f[y][j+1];
			if(f[y][j]) p=min(p,j);
		}
	}
	for(int i=1;i<8;i++) f[x][i]=f[x][i]>=i;
	for(int i=p;i<8;i++) f[x][i]=1;
}
int tot;
inline void SetC(int x,int k,int o,vector<int> r){
	sc[x]=r;
	int p=-1;
	for(int i:e[x]){
		int y=x^u[i]^v[i];
		if(fa[y]!=x) continue ;
		if(!f[y][k+1]){
			c[i]=++tot;
			r.push_back(c[i]);
			SetC(y,k+1,c[i],r);
			r.pop_back();
		}else{
			p++;
			if(r[p]==o) p++;
			c[i]=r[p];
			SetC(y,k,c[i],r);
		}
	}
}

int to[N];
inline void Init(){iota(to+1,to+n+1,1);}
inline int Find(int x){return to[x]==x?x:to[x]=Find(to[x]);}
inline void Merge(int x,int y){to[Find(y)]=Find(x);}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		e[u[i]].push_back(i);
		e[v[i]].push_back(i);
	}

	Init();
	CalcF(1);
	SetC(1,0,0,{});
	for(int i=1;i<=m;i++){
		if(c[i]) continue ;
		c[i]=++tot;
		vector<int> tmp;
		int x=dep[u[i]]<dep[v[i]]?u[i]:v[i],y=x^u[i]^v[i];
		tmp=sc[y];
		tmp.push_back(c[i]);
		sort(tmp.begin(),tmp.end());
		tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
		ans[i]=tmp;
		while(Find(y)!=Find(x)){
			int p=Find(y);
			ans[id[p]]=tmp;
			Merge(fa[p],p);
		}
	}

	for(int i=1;i<=m;i++) cout<<c[i]<<' ';cout<<endl;
	for(int i=1;i<=m;i++){
		cout<<ans[i].size()<<' ';
		for(int x:ans[i]) cout<<x<<' ';cout<<endl;
	}

	return 0;
}