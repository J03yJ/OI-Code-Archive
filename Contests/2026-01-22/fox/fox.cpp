#include<bits/stdc++.h>

using namespace std;

bool bg;

ifstream fin("fox.in");
ofstream fout("fox.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int L=5e6+9;
const int Z=26;
const int lgN=20;
const int N=6e5+9;

namespace ACAM{
	struct Node{
		int son[Z],fail,cnt,vld;
	}tr[L];

	int cnt;
	inline int Allc(){return ++cnt;}
	inline int Insert(string &s){
		int x=0;
		for(char c:s){
			c-='a';
			if(!tr[x].son[c]) tr[x].son[c]=Allc();
			x=tr[x].son[c];
		}
		tr[x].cnt++;
		return x;
	}
	inline void Build(){
		queue<int> q;
		for(int i=0;i<Z;i++){
			if(!tr[0].son[i]) continue ;
			tr[tr[0].son[i]].fail=0;
			q.push(tr[0].son[i]);
		}
		while(q.size()){
			int x=q.front();
			q.pop();
			tr[x].vld=tr[tr[x].fail].vld;
			if(tr[x].cnt) tr[x].vld=x;
			for(int i=0;i<Z;i++){
				if(tr[x].son[i]){
					tr[tr[x].son[i]].fail=tr[tr[x].fail].son[i];
					q.push(tr[x].son[i]);
				}else tr[x].son[i]=tr[tr[x].fail].son[i];
			}
		}
	}
	inline void Get(string &s,vector<int> &v){
		int x=0;
		v.push_back(x);
		for(char c:s){
			c-='a';
			if(!tr[x].son[c]) tr[x].son[c]=Allc();
			x=tr[x].son[c];
			v.push_back(x);
		}
	}
}

string s[N];
vector<int> e[N],imp;
int fa[N],dep[N],elr[N<<1],pos[N],n,m,q,Tid,ecnt;
inline void DFS(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	for(int y:e[x]){
		fa[y]=x;
		dep[y]=dep[x]+ACAM::tr[imp[y]].cnt;
		DFS(y);
		elr[++ecnt]=x;
	}
}
int mn[lgN][N];
inline void InitLCA(){
	for(int i=1;i<=ecnt;i++) mn[0][i]=pos[elr[i]];
	for(int k=1;k<=__lg(ecnt);k++){
		for(int i=1;i+(1<<k)-1<=ecnt;i++){
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
		}
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=__lg(y-x+1);
	return elr[min(mn[k][x],mn[k][y-(1<<k)+1])];
}

ll ans[L];
vector<int> ve[N],node;
inline void GetVir(vector<int> &v){
	node=v;
	sort(v.begin(),v.end(),[](int x,int y){return pos[x]<pos[y];});
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=0;i+1<v.size();i++) node.push_back(LCA(v[i],v[i+1]));
	sort(node.begin(),node.end(),[](int x,int y){return pos[x]<pos[y];});
	node.erase(unique(node.begin(),node.end()),node.end());
	for(int i=0;i+1<node.size();i++) ve[LCA(node[i],node[i+1])].push_back(node[i+1]);
}
int cnt[N];
inline void Calc(int x,int fa){
	for(int y:ve[x]){
		Calc(y,x);
		cnt[x]+=cnt[y];
	}
	ans[cnt[x]]+=dep[x]-dep[fa];
}
inline void VirClear(){
	for(int x:node) cnt[x]=0,ve[x].clear();
}

bool ed;

signed main(){

	cin>>Tid>>n;
	for(int i=1;i<=n;i++) cin>>s[i],m=max(m,(signed)s[i].size());

	for(int i=1;i<=n;i++) imp.push_back(ACAM::Insert(s[i]));
	ACAM::Build();

	imp.push_back(0);
	sort(imp.begin(),imp.end());
	imp.erase(unique(imp.begin(),imp.end()),imp.end());

	for(int i=1;i<imp.size();i++){
		int u=ACAM::tr[ACAM::tr[imp[i]].fail].vld;
		u=lower_bound(imp.begin(),imp.end(),u)-imp.begin();
		e[u].push_back(i);
	}

	DFS(0),InitLCA();

	for(int i=1;i<=n;i++){
		vector<int> v;
		ACAM::Get(s[i],v);
		for(int &x:v){
			x=ACAM::tr[x].vld;
			x=lower_bound(imp.begin(),imp.end(),x)-imp.begin();
			cnt[x]++;
		}
		GetVir(v);
		Calc(0,0);
		VirClear();
	}

	ans[0]=1ll*n*n;
	for(int i=1;i<=m;i++) ans[0]-=ans[i];
	for(int i=1;i<=m;i++) ans[i]+=ans[i-1];

	cin>>q;
	while(q--){
		ll k;
		cin>>k;
		k=1ll*n*n-k+1;
		int p=lower_bound(ans,ans+m+1,k)-ans;
		cout<<p<<endl;
	}

	return 0;
}