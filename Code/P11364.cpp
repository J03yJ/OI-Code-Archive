#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;
const int lgN=2e1;

vector<int> e[N];
int ql[N],qr[N],qk[N],ans[N],n,q;

int a[N<<1],bl[N<<1],br[N<<1],fa[N],dep[N],pos[N],elr[N<<1],ecnt;
inline void DFS(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		DFS(y);
		elr[++ecnt]=x;
	}
}
int lg[N<<1],mn[N<<1][lgN];
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=1;i<=ecnt-(1<<k)+1;i++){
			mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
		}
	}
}
inline int LCA(int u,int v){
	u=pos[u],v=pos[v];
	if(u>v) swap(u,v);
	int k=lg[v-u+1];
	return elr[min(mn[u][k],mn[v-(1<<k)+1][k])];
}

struct Node{
	int l,r,dat;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].dat=0;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].dat=max(tr[x].dat,k),void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline int Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
}

vector<int> kq[N],km[N],lq[N],lm[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	cin>>q;
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qk[i];

	dep[1]=1,DFS(1),InitLCA();
	for(int i=1;i<n;i++) a[i]=LCA(i,i+1);

	vector<int> stk;
	for(int i=1;i<n;i++){
		while(stk.size()&&dep[a[stk.back()]]>=dep[a[i]]) stk.pop_back();
		bl[i]=stk.size()?stk.back()+1:1;
		stk.push_back(i);
	}
	stk.clear();
	for(int i=n-1;i>=1;i--){
		while(stk.size()&&dep[a[stk.back()]]>=dep[a[i]]) stk.pop_back();
		br[i]=stk.size()?stk.back():n;
		stk.push_back(i);
	}

	for(int i=1;i<=q;i++) kq[qk[i]].push_back(i),lq[ql[i]].push_back(i);
	for(int i=1;i<n;i++) km[br[i]-bl[i]+1].push_back(i),lm[bl[i]].push_back(i);
	for(int i=1;i<=n;i++) bl[n+i]=br[n+i]=i,a[n+i]=i,km[1].push_back(n+i);

	Build(1,1,n);
	for(int i=1;i<=n;i++){
		for(int j:lm[i]) Set(1,br[j],dep[a[j]]);
		for(int j:lq[i]) ans[j]=max(ans[j],Query(1,qr[j],n));
	}
	Build(1,1,n);
	for(int i=n;i>=1;i--){
		for(int j:km[i]) Set(1,br[j],dep[a[j]]);
		for(int j:kq[i]) ans[j]=max(ans[j],Query(1,ql[j]+qk[j]-1,qr[j]));
	}
	Build(1,1,n);
	for(int i=n;i>=1;i--){
		for(int j:km[i]) Set(1,bl[j],dep[a[j]]);
		for(int j:kq[i]) ans[j]=max(ans[j],Query(1,ql[j],qr[j]-qk[j]+1));
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}