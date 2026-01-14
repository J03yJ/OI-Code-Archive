#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
const int lgN=2e1;
const int mod=998244353;

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

int fi[N],ne[N<<1],to[N<<1],adj,n;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int bel[N<<2];
inline void Init(){iota(bel,bel+(n+1)*2+1,0);};
inline int Find(int x){return bel[x]==x?x:bel[x]=Find(bel[x]);}
inline void Merge(int x,int y){x=Find(x),y=Find(y),bel[max(x,y)]=min(x,y);}
inline void SameC(int x,int y){Merge(x,y),Merge(x+n+1,y+n+1);}
inline void DiffC(int x,int y){Merge(x,y+n+1),Merge(x+n+1,y);}

int a[N],fa[N][lgN],dep[N],dfn[N],atag[N],btag[N],m,v,dcnt;
inline int LCA(int x,int y){
	if(dep[x]>=dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
	if(x==y) return x;
	for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
	return fa[x][0];
}
inline void DFS1(int x){
	if(!fa[x][0]) dep[x]=1;
	for(int i=1;i<lgN;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	dfn[x]=++dcnt;
	vector<int> tmp;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(!dfn[y]){
			fa[y][0]=x;
			dep[y]=dep[x]+1;
			DFS1(y);
		}else if(dfn[y]>dfn[x]){
			if(dep[y]-dep[x]&1){
				atag[y]=max(atag[x],dep[y]-dep[x]-1);
				if(~(dep[y]-dep[x]+1)&2) SameC(x,y);
			}else{
				btag[y]=max(btag[x],dep[y]-dep[x]);
				SameC(0,x);
			}
			tmp.push_back(y);
		}
	}
	sort(tmp.begin(),tmp.end(),[](int i,int j){return dfn[i]<dfn[j];});
	for(int i=0;i+1<tmp.size();i++){
		int u=tmp[i],v=tmp[i+1],lca=LCA(u,v);
		if(lca==x) continue ;
		int t=dep[u]+dep[v]-2*dep[lca]+2;
		if(~t&2) SameC(x,u);
	}
}
inline void DFS2(int x,int dig){
	if(~a[x]){
		if(a[x]>>dig&1) DiffC(0,x);
		else SameC(0,x);
	}
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(fa[y][0]!=x) continue ;
		DFS2(y,dig);
		atag[x]=max(atag[x],atag[y]-1);
		btag[x]=max(btag[x],btag[y]-1);
	}
	if(atag[x]) SameC(x,fa[x][1]);
	if(btag[x]) SameC(x,fa[x][0]);
}
inline int Calc(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(Find(i)==Find(i+n+1)) return -1;
		if(Find(i)==Find(0)||Find(i)==Find(n+1)) continue ;
		cnt+=(Find(i)==i);
	}
	return cnt;
}
inline void ClearDFN(){for(int i=1;i<=n;i++) dfn[i]=fa[i][0]=atag[i]=btag[i]=0;dcnt=0;}
inline void ClearEdge(){for(int i=1;i<=n;i++) fi[i]=0;adj=0;}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>v;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			AddEdge(u,v);
			AddEdge(v,u);
		}

		int x=n;
		for(int i=0;i<=__lg(v-1);i++){
			Init(),DFS1(1),DFS2(1,i);
			x=min(x,Calc());
			ClearDFN();
		}
		if(!~x) cout<<0<<endl;
		else cout<<QPow(v,x)<<endl;

		ClearEdge();
	}

	return 0;
}