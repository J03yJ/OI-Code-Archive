#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		if(n>m) swap(n,m);
		if(n>=2&&m>=3) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}

	return 0;
}