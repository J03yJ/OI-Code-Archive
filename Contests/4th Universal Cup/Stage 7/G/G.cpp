#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e3*(1<<10)+9;

int b;
ll a,c;
vector<array<int,2>> e[N];

int inq[N];
ll dis[N];
inline void SPFA(int s){
	for(int i=0;i<(b<<10);i++) dis[i]=1e18;
	queue<int> q;
	dis[s]=0,q.push(s),inq[s]=1;
	while(q.size()){
		int x=q.front();
		q.pop();
		inq[x]=0;
		for(auto p:e[x]){
			if(dis[x]+p[1]<dis[p[0]]){
				dis[p[0]]=dis[x]+p[1];
				if(!inq[p[0]]) q.push(p[0]),inq[p[0]]=1;
			}
		}
	}
}

inline void Solve(){
	cin>>a>>b>>c;
	for(int i=0;i<b;i++){
		for(int j=0;j<1024;j++){
			e[i<<10|j].push_back({i<<10|((j+b)&1023),b});
			e[i<<10|j].push_back({((i+((j^b)-j)%b+b)%b)<<10|(j^b),(j^b)-j});
		}
	}
	SPFA((a%b)<<10|(a&1023));
	if(a+dis[(c%b)<<10|(c&1023)]<=c) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	for(int i=0;i<(b<<10);i++) dis[i]=inq[i]=0,e[i].clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}