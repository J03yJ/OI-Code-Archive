#include<bits/stdc++.h>

using namespace std;

using ll=long long;

const int N=2e5+9;

int a[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<ll> cur({0});
	for(int i=1;i<=n;i++){
		vector<ll> now;
		for(ll x:cur){
			now.push_back(x);
			now.push_back(x+a[i]);
		}

		sort(now.begin(),now.end());

		vector<ll> v;
		for(int j=0;j+1<now.size();j++){
			if(now[j]*1.01<=now[j+1]) v.push_back(now[j]);
		}
		v.push_back(now.back());
		cur=v;
	}

	for(int x:cur) cout<<x<<endl;

	return 0;
}