#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,k,res=0,ans=0;
		cin>>k>>m>>n;
		vector<int> tmp(k),imp(n+1,0);
		for(int &x:tmp) cin>>x,imp[x]=1;
		vector<int> u(m),v(m),nw(n+1,0),slf(n+1,0);
		vector<map<int,int>> mp(n+1);
		for(int i=0;i<m;i++){
			cin>>u[i]>>v[i];
			if(imp[u[i]]&&imp[v[i]]) res++;
			else if(imp[u[i]]&&!imp[v[i]]) nw[v[i]]++;
			else if(imp[v[i]]&&!imp[u[i]]) nw[u[i]]++;
			else{
				if(u[i]==v[i]) nw[u[i]]++,slf[u[i]]++;
				else{
					mp[u[i]][v[i]]++;
					mp[v[i]][u[i]]++;
				}
			}
		}

		multiset<int> s;
		for(int i=1;i<=n;i++) if(!imp[i]) s.insert(nw[i]);
		ans=res;
		for(int i=1;i<=n;i++){
			if(imp[i]) continue ;
			ans=max(ans,res+nw[i]);
			s.erase(s.lower_bound(nw[i]));
			for(auto p:mp[i]){
				int j=p.first,k=p.second;
				s.erase(s.lower_bound(nw[j]));
				s.insert(nw[j]+k);
			}
			if(s.size()) ans=max(ans,res+nw[i]+*s.rbegin());
			s.insert(nw[i]);
			for(auto p:mp[i]){
				int j=p.first,k=p.second;
				s.erase(s.lower_bound(nw[j]+k));
				s.insert(nw[j]);
			}
		}

		cout<<ans<<endl;
	}

	return 0;
}