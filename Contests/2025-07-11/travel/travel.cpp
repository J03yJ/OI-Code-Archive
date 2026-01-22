#include<bits/stdc++.h>

using namespace std;

ifstream fin("travel.in");
ofstream fout("travel.out");
#define cin fin
#define cout fout

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const ll inf=1e18;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],siz[N],dep[N],hson[N];
inline void DFS1(int x){
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		DFS1(y);
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>=siz[hson[x]]) hson[x]=y;
	}
}
int dfn[N],idfn[N],top[N],dcnt;
inline void DFS2(int x,int t){
	top[x]=t;
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
	if(hson[x]) DFS2(hson[x],t);
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		DFS2(y,y);
	}
}

int pre[N][lgN],suf[N][lgN],lg[N],n,q;
ll cst[N],mn[N][lgN],pcst[N][lgN],scst[N][lgN];
inline void Init(){
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int x=idfn[i];
		while(stk.size()&&cst[stk.back()]>=cst[x]) stk.pop_back();
		pre[i][0]=stk.size()?dfn[stk.back()]:0;
		stk.push_back(x);
	}
	stk.clear();
	for(int i=n;i>=1;i--){
		int x=idfn[i];
		while(stk.size()&&cst[stk.back()]>=cst[x]) stk.pop_back();
		suf[i][0]=stk.size()?dfn[stk.back()]:n+1;
		stk.push_back(x);
	}
	for(int i=1;i<=n;i++) mn[i][0]=cst[idfn[i]];
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int k=1;k<=lg[n];k++){
		for(int i=1;i<=n-(1<<k)+1;i++){
			mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
		}
	}
	for(int i=1;i<=n;i++){
		pcst[i][0]=1ll*cst[idfn[i]]*(i-pre[i][0]);
		scst[i][0]=1ll*cst[idfn[i]]*(suf[i][0]-i);
	}
	suf[n+1][0]=n+1;
	for(int k=1;k<=lg[n];k++){
		for(int i=1;i<=n+1;i++){
			pre[i][k]=pre[pre[i][k-1]][k-1];
			suf[i][k]=suf[suf[i][k-1]][k-1];
			pcst[i][k]=pcst[i][k-1]+pcst[pre[i][k-1]][k-1];
			scst[i][k]=scst[i][k-1]+scst[suf[i][k-1]][k-1];
		}
	}
}
inline ll Min(int l,int r){
	int k=lg[r-l+1];
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}
inline vector<pii> GetPath(int u,int v){
	vector<pii> p,q;
	while(top[u]!=top[v]){
		if(dep[top[u]]>=dep[top[v]]){
			p.push_back({dfn[u],dfn[top[u]]});
			u=fa[top[u]];
		}else{
			q.push_back({dfn[top[v]],dfn[v]});
			v=fa[top[v]];
		}
	}
	p.push_back({dfn[u],dfn[v]});
	p.insert(p.end(),q.rbegin(),q.rend());
	return p;
}
inline ll Cost(int u,int v){
	vector<pii> p=GetPath(u,v);
	ll ans=0,cur=inf;
	for(pii t:p){
		int i=fir(t),j=sec(t);
		if(i<=j){
			int l=i-1,r=j+1;
			while(l+1<r){
				int mid=l+r>>1;
				if(Min(i,mid)<cur) r=mid;
				else l=mid;
			}
			ans+=cur*(r-i);
			if(r<=j){
				i=r;
				for(int k=lg[n];~k;k--){
					if(suf[i][k]<=j){
						ans+=scst[i][k];
						i=suf[i][k];
					}
				}
				cur=cst[idfn[i]];
				ans+=cst[idfn[i]]*(j-i+1);
			}
		}else{
			int l=j-1,r=i+1;
			while(l+1<r){
				int mid=l+r>>1;
				if(Min(mid,i)<cur) l=mid;
				else r=mid;
			}
			ans+=cur*(i-l);
			if(l>=j){
				i=l;
				for(int k=lg[n];~k;k--){
					if(pre[i][k]>=j){
						ans+=pcst[i][k];
						i=pre[i][k];
					}
				}
				cur=cst[idfn[i]];
				ans+=cst[idfn[i]]*(i-j+1);
			}
		}
	}
	return ans-cur;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>cst[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}

	DFS1(1);
	DFS2(1,1);
	Init();

	cin>>q;
	while(q--){
		int u,v;
		cin>>u>>v;
		cout<<Cost(u,v)<<endl;
	}

	return 0;
}