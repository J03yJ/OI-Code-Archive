#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll n,m,k;
		cin>>n>>k>>m;
		m=min(m,n-1);

		ll lft=n-n/k;
		if(m<=lft) cout<<m+1+((n/k-1)/2)<<endl;
		else cout<<m+1+((n-m-1)/2)<<endl;
	}

	return 0;
}