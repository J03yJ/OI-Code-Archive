#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;
const int lgN=2e1;

vector<int> e[N];
int a[N],ql[N],qr[N],qu[N],n,m,q;

vector<int> qry[N<<2];
inline void Insert(int x,int L,int R,int l,int r,int id){
	if(l<=L&&R<=r) return qry[x].push_back(id);
	int mid=L+R>>1;
	if(l<=mid) Insert(x<<1,L,mid,l,r,id);
	if(r>mid) Insert(x<<1|1,mid+1,R,l,r,id);
}

int fa[N],elr[N<<1],pos[N],ecnt;
inline void GetElr(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		GetElr(y);
		elr[++ecnt]=x;
	}
}
int mn[lgN][N<<1],lg[N<<1];
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=ecnt;i++) mn[0][i]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=1;i+(1<<k)-1<=ecnt;i++){
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
		}
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=lg[y-x+1];
	return elr[min(mn[k][x],mn[k][y-(1<<k)+1])];
}

vector<int> ve[N];
inline int GetVir(vector<int> v,vector<int> &node){
	vector<int> stk;
	for(int x:v){
		if(stk.size()){
			int lca=LCA(stk.back(),x);
			if(stk.back()!=lca){
				int lst=0;
				while(stk.size()&&pos[stk.back()]>pos[lca]){
					if(lst) ve[stk.back()].push_back(lst);
					lst=stk.back();
					stk.pop_back();
				}
				if(stk.back()!=lca){
					stk.push_back(lca);
					node.push_back(lca);
				}
				ve[lca].push_back(lst);
			}
		}
		stk.push_back(x);
		node.push_back(x);
	}
	for(int i=0;i+1<stk.size();i++) ve[stk[i]].push_back(stk[i+1]);
	return stk.front();
}

int imp[N],vsiz[N],vson[N],f[N];
inline void GetVSiz(int x){
	vsiz[x]=imp[x];
	for(int y:ve[x]){
		GetVSiz(y);
		vsiz[x]+=vsiz[y];
		vson[x]+=bool(vsiz[y]);
	}
	vson[x]+=imp[x];
}
inline void GetF(int x,int k){
	f[x]=vson[x]?max(x,k):k;
	for(int y:ve[x]) GetF(y,vson[x]-bool(vsiz[y])?max(x,k):k);
}

int ans[N];
inline void Merge(vector<int> &p,vector<int> &q,vector<int> &r){
	int i=0,j=0;
	while(i<p.size()&&j<q.size()){
		if(pos[p[i]]<pos[q[j]]) r.push_back(p[i++]);
		else r.push_back(q[j++]);
	}
	while(i<p.size()) r.push_back(p[i++]);
	while(j<q.size()) r.push_back(q[j++]);
	r.erase(unique(r.begin(),r.end()),r.end());
}
vector<int> v[N<<2];
inline void Solve(int x,int L,int R){
	vector<int> vq,rl,node;
	if(L!=R){
		int mid=L+R>>1;
		Solve(x<<1,L,mid);
		Solve(x<<1|1,mid+1,R);
		Merge(v[x<<1],v[x<<1|1],v[x]);
	}else v[x]={a[L]};
	for(int i=L;i<=R;i++) imp[a[i]]=1;
	for(int i:qry[x]) vq.push_back(qu[i]);
	Merge(v[x],vq,rl);
	int root=GetVir(rl,node);
	GetVSiz(root);
	GetF(root,0);
	for(int i:qry[x]) ans[i]=max(ans[i],f[qu[i]]);
	for(int i:node) imp[i]=vsiz[i]=vson[i]=f[i]=0,ve[i].clear();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>q;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=m;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qu[i];

	GetElr(1),InitLCA();
	vector<int> p(q);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return pos[qu[i]]<pos[qu[j]];});
	for(int i:p) Insert(1,1,m,ql[i],qr[i],i);
	Solve(1,1,m);

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}