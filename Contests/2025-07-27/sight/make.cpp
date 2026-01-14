#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	const int n=5e5,v=1e9;

	cout<<n<<endl;
	for(int i=1;i<=n;i++){
		cout<<rng()%v+1<<' ';
	}
	cout<<endl;

	return 0;
}