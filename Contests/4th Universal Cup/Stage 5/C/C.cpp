#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll n;
		cin>>n;
		if(n&1) cout<<"No"<<endl;
		else cout<<"Yes"<<endl<<n/2<<' '<<n/2<<endl;
	}

	return 0;
}