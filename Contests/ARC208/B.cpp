#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll n,k;
		cin>>n>>k;
		
		ll tmp=n<=30?(1<<n-1)-1:1e9;
		ll t=(k+tmp-1)/tmp;

		for(int i=1;i<=n;i++){
			ll cur=(t<<i-1)+1,now=t*((1<<i-1)-1);
			if(now>=k){
				ll lst=(t<<i-2)+1,lw=t*((1<<i-2)-1);
				cur=lst+(k-lw);
				for(;i<=n;i++) cout<<cur<<' ';
			}else cout<<cur<<' ';
		}
		cout<<endl;
	}

	return 0;
}