#include<bits/stdc++.h>

using namespace std;

ifstream fin("festival.in");
ofstream fout("festival.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int fa[N],d[N],cnt[N],n,m;
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

inline void Solve(){
	cin>>n>>m;
	iota(fa+1,fa+n+1,1);
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		if(w) d[u]++,d[v]++;
		else Merge(u,v);
	}

	bool flag=0;
	for(int i=1;i<=n;i++) cnt[Find(i)]+=d[i]&1;
	for(int i=1;i<=n;i++){
		if(fa[i]!=i) continue ;
		flag|=cnt[i]&1;
	}

	if(flag) cout<<"No"<<endl;
	else cout<<"Yes"<<endl;

	for(int i=1;i<=n;i++) fa[i]=d[i]=cnt[i]=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}