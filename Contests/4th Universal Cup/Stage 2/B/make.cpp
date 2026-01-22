#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);

	int n=1e5;
	cout<<1<<endl;
	cout<<n<<endl;
	for(int i=1;i<=n;i++){
		if(rng()&1) cout<<rng()%100<<' '<<rng()%1000000000<<endl;
		else cout<<rng()%1000000000<<' '<<rng()%100<<endl;
	}

	return 0;
}