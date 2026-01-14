#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(int &x:a) cin>>x;

	ll ans=1,cnt=0,lst=-1;
	map<int,int> mp;
	for(int i=n-1;~i;i--){
		if(a[i]!=lst) ans+=cnt-mp[a[i]];
		lst=a[i];
		mp[a[i]]++;
		cnt++;
	}

	cout<<ans<<endl;

	return 0;
}