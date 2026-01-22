#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
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
inline int Inv(int x){return QPow(x,mod-2);}

vector<int> e[N],stk;
int dfn[N],low[N],ins[N],bel[N],len[N],f[N][2],g[N],n,m,k,dcnt,scnt;
inline void Tarjan(int x,int fa){
	ins[x]=1;
	stk.push_back(x);
	dfn[x]=low[x]=++dcnt;
	for(int y:e[x]){
		if(y==fa) continue ;
		if(!dfn[y]){
			Tarjan(y,x);
			low[x]=min(low[x],low[y]);
		}else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		scnt++;
		while(stk.size()){
			int p=stk.back();
			stk.pop_back();
			bel[p]=scnt;
			len[scnt]++;
			ins[p]=0;
			if(p==x) break ;
		}
	}
}
inline void Solve(){
	cin>>n>>m>>k;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	Tarjan(1,0);

	f[1][0]=0,f[1][1]=1;
	for(int i=2;i<=n;i++){
		f[i][0]=Add(Mul(f[i-1][0],k-2),Mul(f[i-1][1],k-1));
		f[i][1]=f[i-1][0];
	}
	for(int i=1;i<=n;i++) g[i]=f[i][i==1];

	int ans=1;
	for(int i=1;i<=scnt;i++) MulAs(ans,Mul(k-1,g[len[i]]));
	MulAs(ans,Mul(k,Inv(k-1)));

	cout<<ans<<endl;

	dcnt=scnt=0;
	for(int i=1;i<=n;i++){
		e[i].clear();
		dfn[i]=low[i]=ins[i]=bel[i]=len[i]=0;
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}