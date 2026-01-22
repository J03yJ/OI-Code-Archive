#include<bits/stdc++.h>

using namespace std;

ifstream fin("wars.in");
ofstream fout("wars.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

vector<int> e[N];
list<array<int,2>> s[N];
list<array<int,2>>::iterator in[N],out[N];
int a[N],n,root;

inline void DFS1(int x,int fa){
	for(int y:e[x]){
		if(y==fa) continue ;
		DFS1(y,x);
		if(!a[y]){
			s[y].insert(s[y].begin(),{x,y});
			s[y].insert(s[y].end(),{x,y});
			s[x].splice(s[x].end(),s[y]);
		}
	}
}
inline void DFS2(int x,int fa,int ffa){
	if(x!=root&&a[x]){
		auto it=fa==ffa?out[ffa]:in[ffa];
		in[x]=s[root].insert(it,{x,fa});
		s[x].insert(s[x].begin(),{x,fa});
		s[root].splice(it,s[x]);
		out[x]=next(in[x]);
		ffa=x;
	}
	for(int y:e[x]){
		if(y==fa) continue ;
		DFS2(y,x,ffa);
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int x=1;x<=n;x++){
		if(!a[x]) continue ;
		for(int y:e[x]){
			if(a[y]) continue ;
			root=x;
			break ;
		}
		if(root) break ;
	}

	DFS1(root,0);
	in[root]=s[root].begin();
	out[root]=next(in[root]);
	DFS2(root,0,root);

	for(auto p:s[root]) cout<<p[0]<<' '<<p[1]<<endl;

	return 0;
}