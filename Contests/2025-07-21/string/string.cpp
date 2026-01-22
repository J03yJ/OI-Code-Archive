#include<bits/stdc++.h>

using namespace std;

ifstream fin("string.in");
ofstream fout("string.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e6+9;

inline int MergeC(int x,int y){return x&&y&&x!=y?-1:x|y;}

struct Node{
	int son[2];
	int fail,endp,ban;
}tr[N];
#define son(x,k) tr[x].son[k]
#define fail(x) tr[x].fail
#define endp(x) tr[x].endp
#define ban(x) tr[x].ban

int cnt;
inline int Allc(){return ++cnt;}
inline void Insert(int root,string s,int id){
	int u=root;
	for(char c:s){
		c-='0';
		if(!son(u,c)) son(u,c)=Allc();
		u=son(u,c);
	}
	if(!id) ban(u)=1;
	else endp(u)=MergeC(endp(u),id);
}
inline void Build(int root){
	queue<int> q;
	for(int k:{0,1}){
		if(!son(root,k)) continue ;
		fail(son(root,k))=root;
		q.push(son(root,k));
	}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int k:{0,1}){
			if(son(u,k)){
				fail(son(u,k))=son(fail(u),k);
				q.push(son(u,k));
				ban(son(u,k))|=ban(u);
				ban(son(u,k))|=ban(son(fail(u),k));
				endp(son(u,k))=MergeC(endp(son(u,k)),endp(son(fail(u),k)));
			}else son(u,k)=son(fail(u),k);
		}
	}
}

int dfn[N],low[N],ins[N],bel[N],val[N],dcnt;
vector<int> e[N],stk;
vector<vector<int>> scc;
inline void Tarjan(int x){
	low[x]=dfn[x]=++dcnt;
	stk.push_back(x);
	ins[x]=1;
	for(int y:e[x]){
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		scc.push_back(vector<int>());
		while(stk.size()){
			int p=stk.back();
			stk.pop_back();
			scc.back().push_back(p);
			bel[p]=scc.size()-1;
			ins[p]=0;
			if(p==x) break ;
		}
	}
}

int n,m;
string s[N],t[N];

inline void Clear(){
	for(int i=0;i<=cnt;i++){
		son(i,0)=son(i,1)=fail(i)=ban(i)=endp(i)=0;
		dfn[i]=low[i]=ins[i]=bel[i]=val[i]=0;
		e[i].clear();
	}
	scc.clear();
	dcnt=cnt=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>s[i];
		for(int i=1;i<=m;i++) cin>>t[i];

		for(int i=1;i<=n;i++) Insert(0,s[i],i);
		for(int i=1;i<=m;i++) Insert(0,t[i],0);
		Build(0);

		for(int i=0;i<=cnt;i++){
			if(ban(i)) continue ;
			if(!ban(son(i,0))) e[i].push_back(son(i,0));
			if(!ban(son(i,1))) e[i].push_back(son(i,1));
		}
		for(int i=0;i<=cnt;i++) if(!ban(i)&&!dfn[i]) Tarjan(i);

		bool err=0;
		for(int i=0;i<scc.size();i++){
			int ep=0;
			for(int x:scc[i]) ep=MergeC(ep,endp(x));
			val[i]=ep;
			if(!~ep) err=1;
		}

		for(int i=0;i<scc.size();i++){
			for(int x:scc[i]){
				for(int y:e[x]){
					int j=bel[y];
					err|=val[i]&&val[j]&&(val[i]!=val[j]||!~val[i]);
				}
			}
			for(int x:scc[i]){
				for(int y:e[x]){
					int j=bel[y];
					val[i]=MergeC(val[i],val[j]);
				}
			}
		}

		if(err) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;

		Clear();
	}

	return 0;
}