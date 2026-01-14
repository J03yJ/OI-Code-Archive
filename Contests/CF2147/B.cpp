#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=n-1;i>=1;i--) cout<<i<<' ';
		cout<<n<<' ';
		for(int i=1;i<=n-1;i++) cout<<i<<' ';
		cout<<n<<endl;
	}

	return 0;
}