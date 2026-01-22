#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	ll n,x,y;
	cin>>n>>x>>y;

	if(~n&1){
		cout<<0<<endl;
		return 0;
	}

	ll ans=0;
	for(ll s=y;s;s=y&(s-1)){
		ll res=0;
		for(int i=0;i<=__lg(s);i++){
			if(~s>>i&1) continue ;
			ll p=x-(1ll<<i),q=n*s-(1ll<<i);
			if(p<0||q<0) continue ;
			if((p|q)==q) res|=1ll<<i;
		}
		ans^=res;
	}

	cout<<ans<<endl;

	return 0;
}