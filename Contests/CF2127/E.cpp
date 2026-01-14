#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
const int lgN=2e1;

int c[N],w[N],s[N],err[N],n,k;
vector<int> e[N],p[N];

int fa[N],elr[N<<1],pos[N],ecnt;
inline void DFS(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		elr[++ecnt]=x;
	}
}
int mn[N<<1][lgN],lg[N<<1];
inline void Init(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=1;i<=ecnt-(1<<k)+1;i++){
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

inline void Down(int x){
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(!s[y]) s[y]=s[x];
		Down(y);
	}
}

inline void Clear(){
	for(int i=1;i<=n;i++){
		err[i]=w[i]=s[i]=c[i]=fa[i]=pos[i]=0;
		e[i].clear();
	}
	for(int i=1;i<=k;i++) p[i].clear();
	for(int k=0;k<=lg[ecnt];k++){
		for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[i][k]=0;
	}
	for(int i=0;i<=ecnt;i++) elr[i]=lg[i]=0;
	ecnt=0;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>w[i];
		for(int i=1;i<=n;i++) cin>>c[i];
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}

		DFS(1);
		Init();
		for(int i=1;i<=n;i++) if(c[i]) p[c[i]].push_back(i),s[i]=c[i];
		for(int i=1;i<=k;i++){
			sort(p[i].begin(),p[i].end(),[](int u,int v){return pos[u]<pos[v];});
			for(int j=0;j<signed(p[i].size())-1;j++){
				int u=LCA(p[i][j],p[i][j+1]);
				if(!s[u]||s[u]==i) s[u]=i;
				else err[u]|=1;
			}
		}

		ll ans=0;
		for(int i=1;i<=n;i++) if(err[i]) ans+=w[i];
		Down(1);
		cout<<ans<<endl;
		for(int i=1;i<=n;i++){
			if(c[i]) cout<<c[i]<<' ';
			else{
				if(s[i]>0) cout<<s[i]<<' ';
				else cout<<1<<' ';
			}
		}
		cout<<endl;

		Clear();
	}

	return 0;
}