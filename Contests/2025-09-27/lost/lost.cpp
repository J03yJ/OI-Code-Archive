#include<bits/stdc++.h>

using namespace std;

ifstream fin("lost.in");
ofstream fout("lost.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int K=2e2+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

struct Matrix{
	vector<bitset<K>> r,c;
	Matrix(int n,bool I=0){
		c=r=vector<bitset<K>>(n,bitset<K>());
		for(int i=0;i<n;i++) r[i].reset(),c[i].reset();
		if(I) for(int i=0;i<n;i++) r[i][i]=c[i][i]=1;
	}
	inline bitset<K>& operator [](int x){return r[x];}
	inline void T(){
		int n=r.size();
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++) c[i][j]=r[j][i];
		}
	}
	inline friend Matrix operator *(Matrix f,Matrix g){
		int n=f.r.size();
		Matrix res(n);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				res[i][j]=(f.r[i]&g.c[j]).any();
			}
		}
		res.T();
		return res;
	}
	inline friend bool operator ==(Matrix f,Matrix g){
		for(int i=0;i<f.r.size();i++) if((f[i]^g[i]).any()) return 0;
		return 1;
	}
};

inline Matrix QPow(int n,Matrix x,int y){
	Matrix res(n,1);
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}

int n,m,t;
vector<int> e[N],re[N];

int dfn[N],low[N],ins[N],bel[N],dep[N],dcnt,scnt;
vector<vector<int>> scc;
vector<int> r[N],stk;
inline void Tarjan(int x){
	dfn[x]=low[x]=++dcnt;
	stk.push_back(x);
	ins[x]=1;
	for(int y:e[x]){
		if(!dfn[y]){
			dep[y]=dep[x]+1;
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(ins[y]){
			low[x]=min(low[x],dfn[y]);
			if(dfn[x]>dfn[y]) r[y].push_back(dep[x]-dep[y]+1);
		}
	}
	if(low[x]==dfn[x]){
		scnt++;
		scc.push_back(vector<int>());
		while(stk.size()){
			int p=stk.back();
			scc.back().push_back(p);
			stk.pop_back();
			bel[p]=scnt-1;
			ins[p]=0;
			if(p==x) break ;
		}
	}
}

int vis[N],c[N];
inline bool Try(int s,int k){
	auto Clear=[&](){
		for(int x:scc[bel[s]]) vis[x]=c[x]=0;
	};
	queue<int> q;
	q.push(s);
	vis[s]=1,c[s]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int y:e[x]){
			if(bel[y]!=bel[x]) continue ;
			int t=(c[x]+1)%k;
			if(!vis[y]){
				c[y]=t;
				vis[y]=1;
				q.push(y);
			}else{
				if(c[y]!=t){
					Clear();
					return 0;
				}
			}
		}
	}
	Clear();
	return 1;
}

signed main(){
	cin>>n>>m>>t;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		re[v].push_back(u);
	}

	vector<int> tmp,rem;
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=0;i<scnt;i++){
		int s=scc[i].back();
		if(scc[i].size()==1) continue ;
		int k=r[s].back();
		for(int j=k;j>=1;j--){
			if(k%j) continue ;
			if(Try(s,j)){
				tmp.push_back(j);
				break ;
			}
		}
	}

	map<int,int> mp;
	for(int x:tmp){
		for(int i=2;i<=x*x;i++){
			if(x%i) continue ;
			int cnt=0;
			while(x%i==0) x/=i,cnt++;
			mp[i]=max(mp[i],cnt);
		}
		if(x!=1) mp[x]=max(mp[x],1);
	}

	int ans=1;
	for(auto p:mp) MulAs(ans,QPow(p.first,p.second));

	if(t==1){
		Matrix f(n);
		for(int i=1;i<=n;i++){
			for(int j:e[i]) f[i-1][j-1]=1;
		}
		f.T();
		Matrix sft=f;
		for(auto p:mp){
			int t=p.first,c=p.second;
			sft=QPow(n,sft,QPow(t,c));
		}
		Matrix g(n,1);
		int l=0,r=n*n;
		while(l+1<r){
			int mid=l+r>>1;
			Matrix g=QPow(n,f,mid);			
			if(g==(g*sft)) r=mid;
			else l=mid;
		}
		cout<<r<<' ';
	}

	cout<<ans<<endl;

	return 0;
}