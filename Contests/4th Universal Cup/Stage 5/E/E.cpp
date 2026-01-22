#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
const int inf=1e9;

struct Data{
	int f,g;
	Data(int _f=0,int _g=0){f=_f,g=_g;}
	inline friend Data operator +(Data x,Data y){return Data(max(x.f,y.f),max(x.g,y.g));};
};
struct Node{
	int lc,rc;
	Data dat;
}tr[N<<6];

int cnt;
inline int Allc(){return tr[++cnt].dat=Data(-inf,-inf),cnt;}
inline void Clear(){for(int x=1;x<=cnt;x++) tr[x].lc=tr[x].rc=0,tr[x].dat=Data(0,0);cnt=0;}
inline void PushUp(int x){
	tr[x].dat=Data(-inf,-inf);
	if(tr[x].lc) tr[x].dat=tr[x].dat+tr[tr[x].lc].dat;
	if(tr[x].rc) tr[x].dat=tr[x].dat+tr[tr[x].rc].dat;
}
inline void Insert(int &x,int L,int R,int pos,Data k){
	if(!x) x=Allc();
	if(L==R) return tr[x].dat=tr[x].dat+k,void();
	int mid=L+R>>1;
	if(pos<=mid) Insert(tr[x].lc,L,mid,pos,k);
	else Insert(tr[x].rc,mid+1,R,pos,k);
	PushUp(x);
}
inline void Merge(int &x,int y,int L,int R){
	if(!x||!y) return x|=y,void();
	if(L==R){
		tr[x].dat=tr[x].dat+tr[y].dat;
		return ;
	}
	int mid=L+R>>1;
	Merge(tr[x].lc,tr[y].lc,L,mid);
	Merge(tr[x].rc,tr[y].rc,mid+1,R);
	PushUp(x);
}
inline Data Query(int x,int L,int R,int l,int r){
	if(!x||l>r) return Data(-inf,-inf);
	if(l<=L&&R<=r) return tr[x].dat;
	int mid=L+R>>1;
	if(r<=mid) return Query(tr[x].lc,L,mid,l,r);
	else if(l>mid) return Query(tr[x].rc,mid+1,R,l,r);
	else return Query(tr[x].lc,L,mid,l,r)+Query(tr[x].rc,mid+1,R,l,r);
}

char typ[N];
int fa[N],csu[N],wsu[N],root[N],ans[N],siz[N],n;
vector<int> e[N],node[N];
inline void DFS(int x){
	siz[x]=1;
	csu[x]=csu[fa[x]],wsu[x]=wsu[fa[x]];
	if(typ[x]=='0') csu[x]++;
	else wsu[x]++;
	Insert(root[x],-n,n,csu[x]-wsu[x],Data(3*wsu[x]-csu[x],3*csu[x]-wsu[x]));
	node[x].push_back(x);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		if(siz[x]<siz[y]){
			swap(root[x],root[y]);
			swap(node[x],node[y]);
			swap(siz[x],siz[y]);
		}
		for(int u:node[y]){
			int C=csu[u]-csu[x]-csu[fa[x]];
			int W=wsu[u]-wsu[x]-wsu[fa[x]];
			Data s1=Query(root[x],-n,n,W-C,n);
			ans[x]=max(ans[x],s1.f+3*W-C);
			Data s2=Query(root[x],-n,n,-n,W-C-1);
			ans[x]=max(ans[x],s2.g+3*C-W);
		}
		Merge(root[x],root[y],-n,n);
		node[x].insert(node[x].end(),node[y].begin(),node[y].end());
		node[y].clear();
		node[y].shrink_to_fit();
		siz[x]+=siz[y];
	}
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>typ[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	fill(ans+1,ans+n+1,-1);
	DFS(1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

	for(int i=1;i<=n;i++){
		typ[i]=csu[i]=wsu[i]=root[i]=ans[i]=siz[i]=fa[i]=0;
		e[i].clear(),e[i].shrink_to_fit();
		node[i].clear(),node[i].shrink_to_fit();
	}
	Clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}