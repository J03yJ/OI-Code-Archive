#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int K=1e1+9;
const int lgN=2e1;

int typ[N],n,m,k,q;
vector<array<int,2>> e[N];

int vis[N];
inline void GetTE(int x){
	vis[x]=1;
	for(auto p:e[x]){
		if(!vis[p[0]]){
			typ[p[1]]=1;
			GetTE(p[0]);
		}
	}
}
int mrk[N],siz[N];
inline void GetGrv(int x,int fa,int tot,int &grv){
	bool err=0;
	siz[x]=1;
	for(auto p:e[x]){
		if(p[0]==fa) continue ;
		if(mrk[p[0]]) continue ;
		if(typ[p[1]]!=1) continue ;
		GetGrv(p[0],x,tot,grv);
		siz[x]+=siz[p[0]];
		err|=(siz[p[0]]>tot/2);
	}
	err|=(tot-siz[x]>tot/2);
	if(!err) grv=x;
}
int col[N],cp[N];
inline void Color(int x,int fa,int c,int rt,vector<int> &v){
	col[x]=c,cp[x]=rt;
	v.push_back(x);
	for(auto p:e[x]){
		if(p[0]==fa) continue ;
		if(mrk[p[0]]) continue ;
		if(typ[p[1]]!=1) continue ;
		Color(p[0],x,c,rt,v);
	}
}
int dep[lgN][K][N],mn[N][K];
inline void BFS(int s,int *dep){
	dep[s]=0;
	queue<int> q;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(auto p:e[x]){
			if(mrk[p[0]]) continue ;
			if(!~typ[p[1]]) continue ;
			if(dep[x]+1<dep[p[0]]){
				dep[p[0]]=dep[x]+1;
				q.push(p[0]);
			}
		}
	}
}
int d[N],up[N],ec[N];
inline void Conquer(int x,int tot,int u){
	GetGrv(x,-1,tot,x);
	GetGrv(x,-1,tot,x);
	up[x]=u,d[x]=d[u]+1;

	int ccnt=0;
	vector<int> sv;
	col[x]=0,cp[x]=x;
	for(auto p:e[x]){
		if(mrk[p[0]]) continue ;
		if(typ[p[1]]!=1) continue ;
		Color(p[0],x,++ccnt,x,sv);
	}
	for(int y:sv){
		for(auto p:e[y]){
			if(mrk[p[0]]) continue ;
			if(typ[p[1]]) continue ;
			if(cp[p[0]]!=x) continue ;
			if(col[p[0]]<=col[y]) continue ;
			BFS(y,dep[d[x]][++ec[x]]);
			typ[p[1]]=-1;
		}
	}
	BFS(x,dep[d[x]][++ec[x]]);

	mrk[x]=1;

	for(auto p:e[x]){
		if(mrk[p[0]]) continue ;
		if(typ[p[1]]!=1) continue ;
		Conquer(p[0],siz[p[0]],x);
	}
}

inline void Update(int x){
	for(int y=x;y;y=up[y]){
		for(int i=1;i<=ec[y];i++) mn[y][i]=min(mn[y][i],dep[d[y]][i][x]);
	}
}
inline int Calc(int x){
	int ans=1e9;
	for(int y=x;y;y=up[y]){
		for(int i=1;i<=ec[y];i++) ans=min(ans,mn[y][i]+dep[d[y]][i][x]);
	}
	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m>>k;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back({v,i});
		e[v].push_back({u,i});
	}

	memset(mn,0x3f,sizeof mn);
	memset(dep,0x3f,sizeof dep);
	GetTE(1);
	Conquer(1,n,0);

	cin>>q;
	while(q--){
		int op,x;
		cin>>op>>x;
		if(op==1) Update(x);
		else cout<<Calc(x)<<endl;
	}

	return 0;
}