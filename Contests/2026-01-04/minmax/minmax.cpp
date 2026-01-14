#include<bits/stdc++.h>

using namespace std;

ifstream fin("minmax.in");
ofstream fout("minmax.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;

vector<int> e[N];
int eu[N],ev[N],ew[N],fa[N],dep[N],up[N],n,k;
inline void DFS(int x){
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		DFS(y);
	}
}
int anc[lgN][N],minw[lgN][N],maxw[lgN][N];
inline void Init(){
	for(int i=2;i<=n;i++) anc[0][i]=fa[i],minw[0][i]=maxw[0][i]=up[i];
	minw[0][1]=n+1,maxw[0][1]=0;
	for(int k=1;k<lgN;k++){
		for(int i=1;i<=n;i++){
			anc[k][i]=anc[k-1][anc[k-1][i]];
			minw[k][i]=min(minw[k-1][i],minw[k-1][anc[k-1][i]]);
			maxw[k][i]=max(maxw[k-1][i],maxw[k-1][anc[k-1][i]]);
		}
	}
}
inline int Min(int x,int y){
	int ans=n;
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--){
		if(dep[anc[k][x]]>=dep[y]){
			ans=min(ans,minw[k][x]);
			x=anc[k][x];
		}
	}
	if(x==y) return ans;
	for(int k=lgN-1;~k;k--){
		if(anc[k][x]!=anc[k][y]){
			ans=min(ans,minw[k][x]);
			ans=min(ans,minw[k][y]);
			x=anc[k][x];
			y=anc[k][y];
		}
	}
	ans=min(ans,minw[0][x]);
	ans=min(ans,minw[0][y]);
	return ans;
}
inline int Max(int x,int y){
	int ans=1;
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--){
		if(dep[anc[k][x]]>=dep[y]){
			ans=max(ans,maxw[k][x]);
			x=anc[k][x];
		}
	}
	if(x==y) return ans;
	for(int k=lgN-1;~k;k--){
		if(anc[k][x]!=anc[k][y]){
			ans=max(ans,maxw[k][x]);
			ans=max(ans,maxw[k][y]);
			x=anc[k][x];
			y=anc[k][y];
		}
	}
	ans=max(ans,maxw[0][x]);
	ans=max(ans,maxw[0][y]);
	return ans;
}

ll tr[N],ans;
inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}

int mn[N],mx[N],siz[N],vis[N];
inline void GetGrv(int x,int fa,int tot,int &grv){
	bool flag=1;
	siz[x]=1;
	for(int y:e[x]){
		if(y==fa) continue ;
		if(vis[y]) continue ;
		GetGrv(y,x,tot,grv);
		siz[x]+=siz[y];
		flag&=(siz[y]<=tot/2);
	}
	flag&=(tot-siz[x]<=tot/2);
	if(flag) grv=x;
}
inline void GetNode(int x,int fa,vector<int> &v){
	v.push_back(x);
	for(int y:e[x]){
		if(y==fa) continue ;
		if(vis[y]) continue ;
		GetNode(y,x,v);
	}
}
vector<int> v[N];
inline void Conquer(int x,int tot){
	GetGrv(x,-1,tot,x);
	GetGrv(x,-1,tot,x);
	vis[x]=1;

	v[x]={x};
	for(int y:e[x]){
		if(vis[y]) continue ;
		v[y].clear();
		GetNode(y,x,v[y]);
		v[x].insert(v[x].end(),v[y].begin(),v[y].end());
	}
	
	for(int u:v[x]) mn[u]=Min(u,x),mx[u]=Max(u,x);
	auto Calc=[&](vector<int> &node,ll w){
		ll res=0;
		sort(node.begin(),node.end(),[](int u,int v){return mn[u]>mn[v];});
		for(int i:node){
			if(mn[i]+k<=n){
				if(mx[i]==mn[i]+k) res+=Ask(1,mn[i]+k);
				else if(mx[i]<mn[i]+k) res+=Ask(mn[i]+k,mn[i]+k);
			}
			Add(mx[i],1);
		}
		for(int i:node) Add(mx[i],-1);
		ans+=res*w;
	};
	Calc(v[x],1);
	for(int y:e[x]) if(!vis[y]) Calc(v[y],-1);

	for(int y:e[x]){
		if(vis[y]) continue ;
		Conquer(y,siz[y]);
	}
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		cin>>eu[i]>>ev[i]>>ew[i];
		e[eu[i]].push_back(ev[i]);
		e[ev[i]].push_back(eu[i]);
	}

	dep[1]=1,DFS(1);
	for(int i=1;i<n;i++) up[dep[eu[i]]>dep[ev[i]]?eu[i]:ev[i]]=ew[i];
	Init();

	Conquer(1,n);

	cout<<ans<<endl;

	return 0;
}