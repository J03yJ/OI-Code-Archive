#include<bits/stdc++.h>

using namespace std;

ifstream fin("update.in");
ofstream fout("update.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=3e5+9;
const ll inf=1e18;

ll ew[N],ec[N];
int eu[N],ev[N],ind[N],outd[N],n,m,q;
vector<int> fg[N],bg[N];
vector<ll> fw[N],bw[N];

ll dis[N],sid[N];
inline void Dij(int s,vector<int> *g,vector<ll> *w,int *outd,ll *dis){
	vector<int> vis(n+1,0);
	for(int i=1;i<=n;i++) dis[i]=inf;
	priority_queue<pair<ll,int>> q;
	q.push({-(dis[s]=0),s});
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(int i=0;i<outd[x];i++){
			int y=g[x][i];
			if(dis[x]+w[x][i]<dis[y]) q.push({-(dis[y]=dis[x]+w[x][i]),y});
		}
	}
}

inline void Clear(){
	for(int i=1;i<=n;i++){
		fg[i].clear(),fw[i].clear();
		bg[i].clear(),bw[i].clear();
		ind[i]=outd[i]=0;
	}
}

struct Line{
	ll k,b;
	Line(){}
	Line(ll _k,ll _b){k=_k,b=_b;}
	inline ll operator ()(ll x){return k*x+b;}
};
inline bool Cov(Line f,Line g,ll p){return f.k<=g.k&&f(p)<=g(p);}
inline ll Itsct(Line f,Line g){return ((f.b-g.b)+(g.k-f.k)-1)/(g.k-f.k);}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>eu[i]>>ev[i]>>ew[i]>>ec[i];
			fg[eu[i]].push_back(ev[i]);
			fw[eu[i]].push_back(ew[i]);
			bg[ev[i]].push_back(eu[i]);
			bw[ev[i]].push_back(ew[i]);
			outd[eu[i]]++;
			ind[ev[i]]++;
		}

		Dij(1,fg,fw,outd,dis);
		Dij(n,bg,bw,ind,sid);
		
		vector<Line> l(m);
		for(int i=1;i<=m;i++) l[i-1]=Line(-ec[i],dis[eu[i]]+sid[ev[i]]+ew[i]);
		sort(l.begin(),l.end(),[](Line f,Line g){return f.k^g.k?f.k>g.k:f.b>g.b;});
		vector<Line> s;
		vector<ll> p;
		for(Line f:l){
			while(s.size()&&Cov(f,s.back(),p.back())){
				s.pop_back();
				p.pop_back();
			}
			if(!s.size()) p.push_back(0);
			else p.push_back(Itsct(s.back(),f));
			s.push_back(f);
		}

		cin>>q;
		while(q--){
			ll k;
			cin>>k;
			int pos=upper_bound(p.begin(),p.end(),k)-p.begin()-1;
			cout<<s[pos](k)<<endl;
		}

		Clear();
	}

	return 0;
}