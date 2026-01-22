#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	int n=1e4,k=1e9;
	cout<<1<<endl;
	cout<<k<<' '<<n<<endl;
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		int x=rng()%k;
		while(mp[x]) x=rng()%k;
		mp[x]=1;
		cout<<x<<' ';
	}
	cout<<endl;

	return 0;
}