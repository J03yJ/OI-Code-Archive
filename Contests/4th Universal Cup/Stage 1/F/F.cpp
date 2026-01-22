#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e5+9;
const int lgN=2e1;

list<int> lp,rp;
int p[N],ip[N],l[N],r[N],fa[N],n,m;
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i],ip[p[i]]=i;
	for(int i=1;i<=m;i++) cin>>l[i]>>r[i];
	ip[n]=1e9;

	iota(fa+1,fa+m+1,1);
	
	vector<int> id(m);
	iota(id.begin(),id.end(),1);
	sort(id.begin(),id.end(),[](int i,int j){return r[i]<r[j];});
	lp=list<int>(id.begin(),id.end());
	sort(id.begin(),id.end(),[](int i,int j){return l[i]<l[j];});
	rp=list<int>(id.begin(),id.end());

	ll ans=0;
	for(int t=0;t<=n;t++){
		vector<int> tmpl;
		while(lp.size()&&r[lp.front()]<ip[t]){
			tmpl.push_back(lp.front());
			lp.pop_front();
		}
		vector<int> tmpr;
		while(rp.size()&&l[rp.back()]>ip[t]){
			tmpr.push_back(rp.back());
			rp.pop_back();
		}
		int x=0;
		if(!x&&tmpl.size()) x=tmpl.front();
		if(!x&&tmpr.size()) x=tmpr.back();
		if(!x) continue ;
		for(int y:tmpl) if(Find(x)!=Find(y)) Merge(x,y),ans+=t;
		for(int y:tmpr) if(Find(x)!=Find(y)) Merge(x,y),ans+=t;
		if(tmpl.size()) lp.push_front(tmpl.front());
		if(tmpr.size()) rp.push_back(tmpr.front());
	}

	cout<<ans<<endl;

	return 0;
}