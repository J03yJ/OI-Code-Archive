#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int fi[N],d[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	d[x]++;
}

int a[N],n;
int fa[N],siz[N];
inline void GetGrv(int x,int &grv){
	siz[x]=1;
	bool flag=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		GetGrv(y,grv);
		siz[x]+=siz[y];
		if(siz[y]>n/2) flag=0;
	}
	if(n-siz[x]>n/2) flag=0;
	if(flag) grv=x;
}

inline void Clear(){
	for(int i=1;i<=n;i++) fi[i]=d[i]=fa[i]=0;
	adj=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T,Tid;
	cin>>T>>Tid;
	while(T--){
		cin>>n;
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			AddEdge(u,v);
			AddEdge(v,u);
		}
		for(int i=1;i<=n;i++){
			char c;
			cin>>c;
			a[i]=c-'0';
		}

		bool err=(a[2]==1);
		for(int i=1;i<=n;i++) if((i&1)&&!a[i]) err=1;

		int u=0;
		fa[1]=0,GetGrv(1,u);
		fa[u]=0,GetGrv(u,u);

		int pos=0;
		for(int i=2;i<=n;i+=2) if(!a[i]) pos=i;

		int smx=0;
		for(int i=fi[u];i;i=ne[i]){
			int v=to[i];
			smx=max(smx,siz[v]);
		}
		for(int i=smx*2+1;i<=n;i++) if((~i&1)&&!a[i]) err=1;

		int mx=0;
		for(int i=1;i<=n;i++){
			if(d[i]<3) continue ;
			mx=max(mx,i!=u?siz[i]:n-smx);
		}
		for(int i=(mx-1)*2;i<=n;i++) if((~i&1)&&a[i]) err=1;

		if(err) cout<<"NO"<<endl;
		else{
			cout<<T<<" YES"<<endl;
			for(int i=1;i<=n;i++) cout<<i<<' ';cout<<endl;
		}

		Clear();
	}

	return 0;
}