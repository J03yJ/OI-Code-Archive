#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n);
		for(int &x:a) cin>>x;

		map<int,int> mp;
		for(int x:a) mp[x]++;

		int cur=0;
		array<ll,2> ans({0,0});
		vector<array<int,2>> tmp;
		for(auto p:mp) tmp.push_back({p.first,p.second});
		sort(tmp.begin(),tmp.end(),[](auto x,auto y){return x[1]>y[1];});
		for(auto t:tmp){
			ans[cur]+=1ll*t[1]*((t[0]>>1)+(t[0]&1));
			ans[cur^1]+=1ll*t[1]*(t[0]>>1);
			cur^=(t[0]&1);
		}

		cout<<ans[0]<<' '<<ans[1]<<endl;
	}

	return 0;
}