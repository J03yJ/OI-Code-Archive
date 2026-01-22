#include<bits/stdc++.h>

using namespace std;

ifstream fin("escape.in");
ofstream fout("escape.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e2+9;
const int M=2e4+9;
const int Q=3e6+9;
const ll inf=1e18;

ll lst[M],w[M];
int fi[N],to[M],ne[M],adj;
inline void AddEdge(int x,int y,ll z,ll l){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
	lst[adj]=l;
}

ll el[M],ec[M],qt[Q],len;
int eu[M],ev[M],qu[Q],qv[Q],n,m,q;
vector<int> qry[N];

ll fdis[N];
inline void FDij(int s,ll lim,ll t){
	vector<int> vis(n+1,0);
	for(int i=1;i<=n;i++) fdis[i]=inf;
	fdis[s]=t;
	for(int i=1;i<=n;i++){
		int x=0;
		for(int i=1;i<=n;i++) if(!vis[i]&&(!x||fdis[i]<fdis[x])) x=i;
		if(fdis[x]==inf) return ;
		vis[x]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(lst[i]<lim-fdis[x]) continue ;
			if(fdis[x]+w[i]>lim) continue ;
			if(fdis[x]+w[i]<fdis[y]) fdis[y]=fdis[x]+w[i];
		}
	}
}
ll bdis[N];
inline void BDij(int s,ll lim){
	vector<int> vis(n+1,0);
	for(int i=1;i<=n;i++) bdis[i]=inf;
	bdis[s]=0;
	for(int i=1;i<=n;i++){
		int x=0;
		for(int i=1;i<=n;i++) if(!vis[i]&&(!x||bdis[i]<bdis[x])) x=i;
		if(bdis[x]==inf) return ;
		vis[x]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(lst[i]-w[i]<lim+bdis[x]) continue ;
			if(bdis[x]+w[i]<bdis[y]) bdis[y]=bdis[x]+w[i];
		}
	}
}

inline void Dij(int s,ll *dis){
	vector<int> vis(n+1,0);
	for(int i=1;i<=n;i++) dis[i]=inf;
	dis[s]=0;
	for(int i=1;i<=n;i++){
		int x=0;
		for(int i=1;i<=n;i++) if(!vis[i]&&(!x||dis[i]<dis[x])) x=i;
		if(dis[x]==inf) return ;
		vis[x]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			ll cst=dis[x]%len<=lst[i]-w[i]?dis[x]+w[i]:(dis[x]/len+1)*len+w[i];
			if(cst<dis[y]) dis[y]=cst;
		}
	}
}

ll fl[M][N],bl[M][N],d[N][N],res[M][N],lmt[M],val[M],ans[Q];

signed main(){
	cin>>n>>m>>len>>q;
	for(int i=1;i<=m;i++){
		cin>>eu[i]>>ev[i]>>el[i]>>ec[i];
		eu[i]++,ev[i]++;
		AddEdge(eu[i],ev[i],el[i],ec[i]);
		AddEdge(ev[i],eu[i],el[i],ec[i]);
	}
	for(int i=1;i<=q;i++){
		cin>>qu[i]>>qv[i]>>qt[i];
		qu[i]++,qv[i]++;
		qry[qu[i]].push_back(i);
	}

	for(int i=1;i<=m;i++){
		eu[i+m]=ev[i],ev[i+m]=eu[i];
		el[i+m]=el[i],ec[i+m]=ec[i];
	}
	m<<=1;

	
	for(int i=1;i<=m;i++){
		FDij(eu[i],ec[i],el[i]),BDij(ev[i],ec[i]);
		for(int j=1;j<=n;j++) fl[i][j]=fdis[j],bl[i][j]=bdis[j];
	}
	for(int i=1;i<=n;i++) Dij(i,d[i]);

	for(int s=1;s<=n;s++){
		for(int i=1;i<=m;i++) lmt[i]=fl[i][s]==inf?-1:ec[i]-fl[i][s];
		vector<int> p(m);
		iota(p.begin(),p.end(),1);
		sort(p.begin(),p.end(),[](int i,int j){return lmt[i]>lmt[j];});
		for(int i=1;i<=n;i++) res[0][i]=inf;
		res[0][s]=0;
		val[0]=inf;
		for(int i=1;i<=m;i++){
			val[i]=lmt[p[i-1]];
			for(int j=1;j<=n;j++){
				res[i][j]=fl[p[i-1]][s]+bl[p[i-1]][j];
				res[i][j]=min(res[i][j],res[i-1][j]);
			}
		}
		for(int i:qry[s]){
			ans[i]=inf;
			int t=qv[i];
			int j=upper_bound(val+1,val+m+1,qt[i],greater<ll>())-val-1;
			for(int p=1;p<=n;p++){
				if(!d[p][t]) ans[i]=min(ans[i],res[j][p]);
				else if(res[j][p]<inf) ans[i]=min(ans[i],len-qt[i]+d[p][t]);
			}
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}