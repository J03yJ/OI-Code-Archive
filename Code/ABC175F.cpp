#include<bits/stdc++.h>
 
using namespace std;
 
using ll=long long;
const int N=5e1+9;
const int M=2e3+9;
const ll inf=1e18;
 
int c[N],n,tot,st,ed;
string s[N];
vector<array<int,2>> e[M];
 
inline bool Palin(string s){
	for(int i=0;i<s.size();i++) if(s[i]!=s[s.size()-i-1]) return 0;
	return 1;
}
inline string Merge(string s,string t){
	reverse(t.begin(),t.end());
	while(s.size()&&t.size()&&s.back()==t.back()){
		s.pop_back();
		t.pop_back();
	}
	reverse(t.begin(),t.end());
	return s+t;
}
 
ll dis[M];
int vis[M];
inline void Dij(){
	for(int i=1;i<=tot;i++) dis[i]=inf;
	priority_queue<array<ll,2>> q;
	q.push({-(dis[st]=0),st});
	while(q.size()){
		int x=q.top()[1];
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(auto t:e[x]){
			if(dis[x]+t[1]<dis[t[0]]){
				q.push({-(dis[t[0]]=dis[x]+t[1]),t[0]});
			}
		}
	}
}
 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i]>>c[i];
 
	map<string,int> id;
	st=id[""]=++tot,ed=id["?"]=++tot;
	for(int i=1;i<=n;i++){
		for(int j=0;j<s[i].size();j++){
			string t="?"+s[i].substr(0,j+1);
			if(!id[t]) id[t]=++tot;
		}
		for(int j=0;j<s[i].size();j++){
			string t=s[i].substr(j)+"?";
			if(!id[t]) id[t]=++tot;
		}
	}
	for(int i=1;i<=n;i++){
		if(Palin(s[i])) e[st].push_back({ed,c[i]});
		for(int j=0;j<s[i].size();j++){
			string t="?"+s[i].substr(0,j+1);
			if(Palin(s[i].substr(j+1))) e[st].push_back({id[t],c[i]});
			for(int k=1;k<=n;k++){
				string r=s[k].size()>=t.size()?Merge(t.substr(1),s[k])+"?":Merge(t,s[k]);
				if(r.size()>abs(int(t.size()-1)-int(s[k].size()))+1) continue ;
				if(!id[r]) continue ;
				e[id[t]].push_back({id[r],c[k]});
			}
		}
		for(int j=0;j<s[i].size();j++){
			string t=s[i].substr(j)+"?";
			if(Palin(s[i].substr(0,j))) e[st].push_back({id[t],c[i]});
			for(int k=1;k<=n;k++){
				string r=s[k].size()>=t.size()?"?"+Merge(s[k],t.substr(0,t.size()-1)):Merge(s[k],t);
				if(r.size()>abs(int(t.size()-1)-int(s[k].size()))+1) continue ;
				if(!id[r]) continue ;
				e[id[t]].push_back({id[r],c[k]});
			}
		}
	}
 
	Dij();
 
	cout<<(dis[ed]!=inf?dis[ed]:-1)<<endl;
 
	return 0;
}