#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n,k;
		cin>>n>>k;
		vector<array<int,2>> a(n);
		for(auto &t:a) cin>>t[0];
		for(auto &t:a){
			cin>>t[1];
			if(t[0]>t[1]) swap(t[0],t[1]);
		}
		sort(a.begin(),a.end());

		vector<int> p;
		for(int i=0;i<n-1;i++){
			if(a[i][1]<a[i+1][0]){
				p.push_back(2*a[i+1][0]-2*a[i][1]);
			}else p.push_back(0);
		}
		sort(p.begin(),p.end());
		
		ll ans=p.front();
		for(auto &t:a) ans+=t[1]-t[0];
		cout<<ans<<endl;
	}

	return 0;
}