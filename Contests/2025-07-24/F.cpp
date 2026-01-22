#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		int n,k,m,T;
		cin>>n>>k>>m>>T;

		ll ans=0;
		for(int i=1;i<=T;i++){
			int p=n/__gcd(n,i+1);
			ans+=1ll*m*(k-k/p);
		}

		ll t=1ll*T*(n-1);
		cout<<(ans+t-1)/t<<endl;
	}

	return 0;
}