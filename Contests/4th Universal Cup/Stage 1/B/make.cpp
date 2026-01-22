#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n=1e5;
	cout<<n<<endl;
	mt19937 rng(4649);
	for(int i=2;i<=n;i++){
		cout<<rng()%(i-1)+1<<' '<<i<<endl;
	}
}