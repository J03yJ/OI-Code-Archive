#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	int n=2e6,m=0,k=2e6;
	cout<<n<<' '<<m<<' '<<k<<endl;
	for(int i=1;i<=n;i++){
		cout<<i<<' '<<rng()%(k/i)+1<<endl;
	}
}