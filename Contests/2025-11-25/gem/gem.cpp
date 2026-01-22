#include<bits/stdc++.h>

using namespace std;

ifstream fin("gem.in");
ofstream fout("gem.out");
#define cin fin
#define cout fout
#define endl '\n'

#define double long double
const int N=2e3+9;
const int M=2e4+9;
const double eps=1e-7;

int fi[N],ne[M<<1],to[M<<1],a[M<<1],b[M<<1],v[N],adj,n,m,o,id;
inline void AddEdge(int x,int y,int _a,int _b){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y,a[adj]=_a,b[adj]=_b;
}

int vis[N];
double ans[N],dis[N];
inline void Dij(int s,double k){
	for(int i=1;i<=n;i++) dis[i]=1e18,vis[i]=0;
	priority_queue<pair<double,int>> q;
	q.push({dis[s]=0,s});
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			double w=a[i]*k+b[i]+dis[x];
			if(w<dis[y]) q.push({-(dis[y]=w),y});
		}
	}
}
inline bool Check(int s,double k){
	Dij(s,k);
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=(dis[i]<=v[i]);
	if(cnt>=o) return 1;
	else return 0;
}

signed main(){
	cout<<fixed<<setprecision(8);

	cin>>n>>m>>o>>id;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1,u,v,x,y;i<=m;i++){
		cin>>u>>v>>x>>y;
		AddEdge(u,v,x,y);
	}

	if(o==1){
		cout<<1000000000<<endl;
		return 0;
	}

	mt19937 rng(4649);
	double cur=-eps;
	vector<int> id(n);
	iota(id.begin(),id.end(),1);
	shuffle(id.begin(),id.end(),rng);
	for(int s:id){
		if(!Check(s,cur+eps)) continue ;
		double l=cur,r=1e9+eps;
		while((r-l)/max(l,(double)1.0)>=eps){
			double mid=(l+r)/2;
			if(Check(s,mid)) l=mid;
			else r=mid;
		}
		cur=l;
	}
	
	if(cur<0) cout<<-1<<endl;
	else cout<<cur<<endl;

	return 0;
}