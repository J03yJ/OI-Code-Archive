#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n;
	cin>>n;

	int fac=1;
	for(int i=1;i<=n;i++) fac*=i;
	cout<<fac<<endl;

	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	do{
		cout<<n<<endl;
		for(int i:p) cout<<i<<' ';
		cout<<endl;
	}while(next_permutation(p.begin(),p.end()));

	return 0;
}