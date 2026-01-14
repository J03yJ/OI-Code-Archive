#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n=1e5;
	cout<<n<<' '<<1000000<<endl;
	long long mod=1ll<<60;
	mt19937_64 rng(4649);
	for(int i=1;i<=n;i++) cout<<rng()%mod<<' ';cout<<endl;

	return 0;
}