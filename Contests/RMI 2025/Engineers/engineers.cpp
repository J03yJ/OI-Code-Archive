#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int lgN=2e1;

vector<int> e[N];
int fa[N],dep[N],siz[N],hson[N];
inline void GetHSon(int x){
	siz[x]=1,hson[x]=-1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		siz[x]+=siz[y];
		if(!~hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
}
int top[N],dfn[N],dcnt;
inline void GetTop(int x,int t){
	top[x]=t;
	dfn[x]=dcnt++;
	if(~hson[x]) GetTop(hson[x],t);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetTop(y,y);
	}
}

int elr[N<<1],pos[N],sop[N],ecnt;
inline void GetElr(int x){
	elr[ecnt]=x;
	sop[x]=pos[x]=ecnt++;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		GetElr(y);
		elr[sop[x]=ecnt++]=x;
	}
}
int mn[N<<1][lgN],lg[N<<1];
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=0;i<ecnt;i++) mn[i][0]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=0;i+(1<<k)-1<ecnt;i++){
			mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
		}
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=lg[y-x+1];
	return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
}
int lca[N][lgN];
inline void InitR(int n,vector<int> &p){
	for(int i=0;i<n;i++) lca[i][0]=p[i];
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i+(1<<k)-1<n;i++){
			lca[i][k]=LCA(lca[i][k-1],lca[i+(1<<k-1)][k-1]);
		}
	}
}
inline int RLCA(int l,int r){
	int k=lg[r-l+1];
	return LCA(lca[l][k],lca[r-(1<<k)+1][k]);
}

struct Node{
	int l,r,tag;
	array<int,2> dat;
}tr[N<<2];

inline array<int,2> Merge(array<int,2> x,array<int,2> y){
	if(x[0]!=y[0]) return min(x,y);
	else return {x[0],x[1]+y[1]};
}
inline void PushUp(int x){tr[x].dat=Merge(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat[0]+=k,tr[x].tag+=k;}
inline void PushDown(int x){if(tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=0;}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].tag=0;
	if(tr[x].l==tr[x].r) return tr[x].dat={0,1},void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline void ModToR(int x,int k){
	while(~x){
		Modify(1,dfn[top[x]],dfn[x],k);
		x=fa[top[x]];
	}
}

int solve(int n,int d,vector<int> c,vector<int> ep,vector<int> eq){
	vector<int> p(n),ip(n);
	iota(p.begin(),p.end(),0);
	sort(p.begin(),p.end(),[&](int i,int j){return c[i]<c[j];});
	for(int i=0;i<n;i++) ip[p[i]]=i;
	for(int i=0;i<n-1;i++){
		e[ep[i]].push_back(eq[i]);
		e[eq[i]].push_back(ep[i]);
	}
	fa[0]=-1,GetHSon(0),GetTop(0,0);
	GetElr(0),InitLCA(),InitR(n,p);
	
	int ans=n;
	Build(1,0,n-1);
	for(int i=0;i<n;i++) ModToR(fa[i],1);
	for(int i=0,j=0;i<n;i++){
		while(j<n&&c[p[j]]-c[p[i]]<=d){
			Modify(1,dfn[p[j]],dfn[p[j]],1);
			ModToR(fa[p[j]],-1);
			j++;
		}
		int cnt=0,u=-1,v=-1;
		if(i) u=~u?LCA(u,RLCA(0,i-1)):RLCA(0,i-1);
		if(j<n) u=~u?LCA(u,RLCA(j,n-1)):RLCA(j,n-1);
		if(~u&&(ip[u]<i||ip[u]>=j)){
			if(ip[u]<i){
				if(ip[u]) v=~v?LCA(v,RLCA(0,ip[u]-1)):RLCA(0,ip[u]-1);
				if(ip[u]+1<i) v=~v?LCA(v,RLCA(ip[u]+1,i-1)):RLCA(ip[u]+1,i-1);
				if(j<n) v=~v?LCA(v,RLCA(j,n-1)):RLCA(j,n-1);
			}else{
				if(i) v=~v?LCA(v,RLCA(0,i-1)):RLCA(0,i-1);
				if(j<ip[u]) v=~v?LCA(v,RLCA(j,ip[u]-1)):RLCA(j,ip[u]-1);
				if(ip[u]+1<n) v=~v?LCA(v,RLCA(ip[u]+1,n-1)):RLCA(ip[u]+1,n-1);
			}
			if(~v&&pos[u]<pos[v]&&pos[v]<sop[u]) cnt++;
		}
		cnt+=tr[1].dat[0]==0?tr[1].dat[1]:0;
		ans=min(ans,cnt+1>>1);
		Modify(1,dfn[p[i]],dfn[p[i]],-1);
		ModToR(fa[p[i]],1);
	}

	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int n,d;
	cin>>n>>d;
	vector<int> c(n),ep(n-1),eq(n-1);
	for(int &x:c) cin>>x;
	for(int i=0;i<n-1;i++) cin>>ep[i]>>eq[i];

	cout<<solve(n,d,c,ep,eq)<<endl;

	return 0;
}