#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n=1e5,m=1e5,v=1e9;
	mt19937 rng(4649);

	cout<<n<<endl;
	for(int i=2;i<=n;i++){
		cout<<rng()%(i-1)+1<<' '<<i<<' '<<rng()%v<<endl;
	}
	cout<<m<<endl;
	for(int i=1;i<=m;i++) cout<<rng()%v<<endl;

	return 0;
}