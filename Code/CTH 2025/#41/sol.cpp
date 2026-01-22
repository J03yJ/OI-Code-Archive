#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;

ll ans[N];
int ep[N],eq[N],t[N],n,m;

ll cur;
int fa[N],siz[N];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	if(siz[x]<siz[y]) swap(x,y);
	cur-=1ll*siz[x]*(siz[x]-1)/2;
	cur-=1ll*siz[y]*(siz[y]-1)/2;
	fa[y]=x;
	siz[x]+=siz[y];
	cur+=1ll*siz[x]*(siz[x]-1)/2;
}

vector<int> e[N],stk;
int dfn[N],low[N],ins[N],bel[N],dcnt;
inline void Tarjan(int x){
	ins[x]=1,stk.push_back(x);
	dfn[x]=low[x]=++dcnt;
	for(int y:e[x]){
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		while(stk.size()){
			int p=stk.back();
			stk.pop_back();
			ins[p]=0;
			bel[p]=x;
			if(p==x) break ;
		}
	}
}
inline void BinSch(int l,int r,vector<int> &v){
	int mid=l+r>>1;
	vector<int> node;
	for(int i:v){
		if(t[i]>mid) continue ;
		e[Find(ep[i])].push_back(Find(eq[i]));
		node.push_back(Find(ep[i]));
		node.push_back(Find(eq[i]));
	}

	for(int x:node) if(!dfn[x]) Tarjan(x);
	auto Clear=[&](){
		for(int x:node){
			dfn[x]=low[x]=ins[x]=bel[x]=0;
			e[x].clear();
		}
		dcnt=0;
	};

	if(l==r){
		for(int x:node) Merge(x,bel[x]);
		ans[l]=cur;
		Clear();
	}else{
		vector<int> lv,rv;
		for(int i:v){
			if(t[i]>mid) rv.push_back(i);
			else{
				if(bel[Find(ep[i])]==bel[Find(eq[i])]) lv.push_back(i);
				else t[i]=mid+1,rv.push_back(i);
			}
		}
		Clear();
		BinSch(l,mid,lv);
		BinSch(mid+1,r,rv);
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>ep[i]>>eq[i];

	for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++) t[i]=i;
	vector<int> v(m);
	iota(v.begin(),v.end(),1);

	BinSch(1,m,v);

	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

	return 0;
}