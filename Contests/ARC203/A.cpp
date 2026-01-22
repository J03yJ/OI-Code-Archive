#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		
		ll res=1ll*n*(m>>1);
		res+=m&1;

		cout<<res<<endl;
	}

	return 0;
}