#include<bits/stdc++.h>

using namespace std;

ifstream fin("word.in");
ofstream fout("word.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;

namespace SgT{
	struct Node{
		int l,r;
		ll dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
	inline void Build(int x,int l,int r){
		tr[x].l=l,tr[x].r=r;
		if(tr[x].l==tr[x].r) return ;
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Set(int x,int pos,ll k){
		if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) Set(x<<1,pos,k);
		else Set(x<<1|1,pos,k);
		PushUp(x);
	}
	inline ll Query(int x,int l,int r){
		if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
		int mid=tr[x].l+tr[x].r>>1;
		ll ans=0;
		if(l<=mid) ans=max(ans,Query(x<<1,l,r));
		if(r>mid) ans=max(ans,Query(x<<1|1,l,r));
		return ans;
	}
}
namespace ACAM{
	struct Node{
		int fail,son[26];
	}tr[N];

	int cnt;
	inline int Allc(){return ++cnt;}
	inline int Insert(string s){
		int x=0;
		for(char c:s){
			if(!tr[x].son[c-'a']) tr[x].son[c-'a']=Allc();
			x=tr[x].son[c-'a'];
		}
		return x;
	}
	inline void InitFail(){
		queue<int> q;
		for(int i=0;i<26;i++){
			if(!tr[0].son[i]) continue ;
			tr[tr[0].son[i]].fail=0;
			q.push(tr[0].son[i]);
		}
		while(q.size()){
			int x=q.front();
			q.pop();
			for(int i=0;i<26;i++){
				if(!tr[x].son[i]) tr[x].son[i]=tr[tr[x].fail].son[i];
				else{
					tr[tr[x].son[i]].fail=tr[tr[x].fail].son[i];
					q.push(tr[x].son[i]);
				}
			}
		}
	}

	vector<int> e[N];
	inline void InitEdge(){
		for(int i=1;i<=cnt;i++) e[tr[i].fail].push_back(i);
	}
	int fa[N],siz[N],hson[N];
	inline void DFS1(int x){
		siz[x]=1;
		for(int y:e[x]){
			fa[y]=x;
			DFS1(y);
			siz[x]+=siz[y];
			if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
		}
	}
	int dfn[N],top[N],dcnt;
	inline void DFS2(int x,int t){
		top[x]=t;
		dfn[x]=++dcnt;
		if(hson[x]) DFS2(hson[x],t);
		for(int y:e[x]){
			if(y==hson[x]) continue ;
			DFS2(y,y);
		}
	}
	inline void InitTree(){
		InitEdge();
		for(int i=1;i<=cnt;i++){
			if(tr[i].fail) continue ;
			DFS1(i),DFS2(i,i);
		}
		SgT::Build(1,1,cnt);
	}

	inline void Set(int x,ll k){SgT::Set(1,dfn[x],k);}
	inline ll FQ(int x){
		ll ans=0;
		while(x){
			ans=max(ans,SgT::Query(1,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		return ans;
	}

	inline ll Query(string s){
		int x=0;ll ans=0;
		for(char c:s){
			x=tr[x].son[c-'a'];
			ans=max(ans,FQ(x));
		}
		return ans;
	}
}

int w[N],pos[N],n;
string s[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i]>>w[i];

	ll ans=0;
	for(int i=1;i<=n;i++) pos[i]=ACAM::Insert(s[i]);
	ACAM::InitFail();
	ACAM::InitTree();
	for(int i=1;i<=n;i++){
		ll res=ACAM::Query(s[i])+w[i];
		ans=max(ans,res);
		ACAM::Set(pos[i],res);
	}

	cout<<ans<<endl;

	return 0;
}