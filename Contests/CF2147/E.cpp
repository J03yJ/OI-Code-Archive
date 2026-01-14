#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int B=32;
using ll=long long;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		int n,q;
		cin>>n>>q;
		vector<ll> a(n);
		for(ll &x:a) cin>>x;

		vector<array<ll,2>> ans;
		for(int i=B;~i;i--){
			ll res=0,t=i+1,tmp=0;
			priority_queue<ll> q;
			for(int j=0;j<n;j++) q.push(a[j]&(1<<i)-1),tmp|=a[j];
			for(int j=i+1;j<B;j++) t+=(tmp>>j&1);
			for(int j=i;~j;j--){
				int cnt=0;
				while(q.top()>=(1ll<<j)){
					ll tmp=q.top();
					q.pop();
					q.push(tmp&(1ll<<j)-1);
					cnt++;
				}
				if(!cnt){
					res+=(1ll<<j)-q.top();
					q.pop();
					q.push(0);
				}
			}
			ans.push_back({res,t});
		}
		ll t=0,tmp=0;
		for(int j=0;j<n;j++) tmp|=a[j];
		for(int j=0;j<B;j++) t+=(tmp>>j&1);
		ans.push_back({ll(-1e18),t});
		sort(ans.begin(),ans.end());
		
		while(q--){
			ll c;
			cin>>c;
			int p=upper_bound(ans.begin(),ans.end(),array<ll,2>({c,114514ll}))-ans.begin()-1;
			cout<<ans[p][1]<<endl;
		}
	}

	return 0;
}