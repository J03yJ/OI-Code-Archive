#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
const int K=2e1+9;
const int S=(1<<16)+9;
const int inf=1e9+7;

string s[N];
int st[N],n,m,k;

vector<int> p[K];
vector<array<int,2>> e[N+K];
int bel[N],d[K][N+K],c[K][K],v[K][S],sta[N],m1[K][K],m2[K][K];
inline void BFS(int s,int *dis){
	deque<int> q;
	vector<int> vis(n+k+1,0);
	for(int i=1;i<=n+k;i++) dis[i]=inf;
	dis[s]=0;
	q.push_back(s);
	while(q.size()){
		int x=q.front();
		q.pop_front();
		if(vis[x]) continue ;
		vis[x]=1;
		for(auto p:e[x]){
			if(dis[x]+p[1]<dis[p[0]]){
				dis[p[0]]=dis[x]+p[1];
				if(!p[1]) q.push_front(p[0]);
				else q.push_back(p[0]);
			}
		}
	}
}
inline int Dist(int x,int y){
	if(bel[x]==bel[y]) return x!=y;
	if(bel[x]>bel[y]) swap(x,y);
	if(m1[bel[x]][bel[y]]&(sta[x]&sta[y])) return c[bel[x]][bel[y]];
	else if(m1[bel[x]][bel[y]]&(sta[x]|sta[y])) return c[bel[x]][bel[y]]+1;
	else if(m2[bel[x]][bel[y]]&(sta[x]&sta[y])) return c[bel[x]][bel[y]]+1;
	else return c[bel[x]][bel[y]]+2;
}

inline ll Solve(){
	cin>>n>>m>>k;
	st[0]=1;
	for(int i=1;i<=m;i++){
		cin>>s[i];
		st[i]=st[i-1]+s[i-1].size();
		for(int j=0;j<s[i].size();j++){
			if(j){
				e[st[i]+j].push_back({st[i]+j-1,1});
				e[st[i]+j-1].push_back({st[i]+j,1});
			}
			bel[st[i]+j]=s[i][j]-'a'+1;
			e[st[i]+j].push_back({n+bel[st[i]+j],1});
			e[n+bel[st[i]+j]].push_back({st[i]+j,0});
		}
	}
	for(int i=1;i<=k;i++) BFS(n+i,d[i]);
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++) c[i][j]=d[i][n+j]-(i!=j);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			sta[i]|=(d[j][i]==c[j][bel[i]])<<j-1;
		}
		v[bel[i]][sta[i]]++;
		p[bel[i]].push_back(i);
	}

	ll ans=0;
	for(int i=1;i<=k;i++){
		ans+=1ll*p[i].size()*(p[i].size()-1)/2;
		for(int j=0;j<k;j++){
			for(int t=0;t<(1<<k);t++) if(~t>>j&1) v[i][t|(1<<j)]+=v[i][t];
		}
		for(int j=i+1;j<=k;j++){
			for(int t=1;t<=k;t++){
				m1[i][j]|=(c[i][j]==c[i][t]+c[t][j]+1)<<t-1;
				m2[i][j]|=(c[i][j]+1==c[i][t]+c[t][j]+1)<<t-1;
			}
			for(int x:p[j]){
				ll c0=p[i].size()-v[i][(1<<k)-1^m1[i][j]&sta[x]];
				ll c2=v[i][(1<<k)-1^m1[i][j]^m2[i][j]&sta[x]];
				ll c1=p[i].size()-c0-c2;
				ans+=c0*c[i][j]+c1*(c[i][j]+1)+c2*(c[i][j]+2);
			}
		}
	}

	for(int i=1;i<=m;i++){
		for(int j=0;j<s[i].size();j++){
			for(int t=max(0,j-2*k);t<j;t++){
				ans-=Dist(st[i]+t,st[i]+j);
				ans+=min(Dist(st[i]+t,st[i]+j),j-t);
			}
		}
	}

	for(int i=1;i<=k;i++){
		for(int j=1;j<=n+k;j++) d[i][j]=0;
		for(int j=0;j<(1<<k);j++) v[i][j]=0;
		for(int j=1;j<=k;j++) c[i][j]=m1[i][j]=m2[i][j]=0;
		p[i].clear(),p[i].shrink_to_fit();
	}
	for(int i=1;i<=n+k;i++) e[i].clear(),e[i].shrink_to_fit();
	for(int i=1;i<=n;i++) bel[i]=sta[i]=0;
	for(int i=1;i<=m;i++) s[i].clear(),s[i].shrink_to_fit();

	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	for(int o=1;o<=T;o++) cout<<"Case #"<<o<<": "<<Solve()<<endl;

	return 0;
}