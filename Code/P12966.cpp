#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;

ll v[N],w[N],lim;
int n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>lim;
	for(int i=1;i<=n;i++) cin>>w[i]>>v[i];

	vector<ll> val({1});
	val.insert(val.end(),v+1,v+n+1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());

	vector<priority_queue<ll>> q(val.size());
	for(int i=1;i<=n;i++){
		int pos=lower_bound(val.begin(),val.end(),v[i])-val.begin();
		q[pos].push(w[i]);
	}
	
	ll ans=0;
	for(int i=0;i+1<val.size();i++){
		while(lim%val[i+1]>=val[i]){
			if(!q[i].size()) break ;
			ans+=q[i].top();
			q[i].pop();
			lim-=val[i];
		}
		while(q[i].size()){
			ll tmp=0;
			for(int j=1;j<=val[i+1]/val[i];j++){
				if(!q[i].size()) break ;
				tmp+=q[i].top();
				q[i].pop();
			}
			q[i+1].push(tmp);
		}
	}
	for(int i=val.size()-1;~i;i--){
		while(q[i].size()&&lim>=val[i]){
			ans+=q[i].top();
			lim-=val[i];
			q[i].pop();
		}
	}

	cout<<ans<<endl;

	return 0;
}