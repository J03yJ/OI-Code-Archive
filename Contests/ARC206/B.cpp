#include<bits/stdc++.h>

using namespace std;

using ll=long long;

inline int LIS(vector<int> v){
	vector<int> d;
	for(int x:v){
		int p=upper_bound(d.begin(),d.end(),x)-d.begin();
		if(p>=d.size()) d.push_back(x);
		else d[p]=x;
	}
	return d.size();
}

signed main(){
	int n;
	cin>>n;
	vector<int> p(n),c(n);
	for(int &x:p) cin>>x;
	for(int &x:c) cin>>x;

	map<int,vector<int>> mp;
	for(int i=0;i<n;i++) mp[c[i]].push_back(p[i]);

	ll ans=0;
	for(auto &p:mp){
		ans+=1ll*p.first*(p.second.size()-LIS(p.second));
	}

	cout<<ans<<endl;

	return 0;
}