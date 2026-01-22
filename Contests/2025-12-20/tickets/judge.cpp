#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	ifstream inf("tickets.in");
	ifstream ouf("tickets.out");

	ll ans;
	int n,m,k;
	inf>>n>>m>>k;
	ouf>>ans;

	vector<vector<int>> a(n),b(n);
	for(int i=0;i<n;i++){
		a[i].resize(m);
		for(int j=0;j<m;j++) inf>>a[i][j];
		b[i].resize(m);
		for(int j=0;j<m;j++) ouf>>b[i][j];
	}

	vector<vector<int>> v(k);
	for(int i=0;i<n;i++){
		map<int,int> mp;
		for(int j=0;j<m;j++){
			if(!~b[i][j]) continue ;
			if(mp[b[i][j]]){
				cerr<<"Not Perm On Row #"<<i<<" / "<<b[i][j]<<' '<<i<<' '<<j<<endl;
				return 1;
			}
			mp[b[i][j]]=1;
			v[b[i][j]].push_back(a[i][j]);
		}
	}

	ll res=0;
	for(int i=0;i<k;i++){
		if(v[i].size()!=n){
			cerr<<"Size of Color #"<<i<<" Neq n / "<<v[i].size()<<endl;
			return 2;
		}
		sort(v[i].begin(),v[i].end());
		for(int j=0;j<n;j++) res+=abs(v[i][j]-v[i][n/2]);
	}

	if(res!=ans){
		cerr<<"Result Not Matched / "<<ans<<" / "<<res<<endl;
		return 3;
	}

	cerr<<"Accepted"<<endl;

	return 0;
}