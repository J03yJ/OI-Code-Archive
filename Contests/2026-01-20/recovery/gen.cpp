#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n=1e6;
	cout<<0<<' '<<1<<endl;
	cout<<n<<endl;
	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	shuffle(p.begin(),p.end(),mt19937(4649));
	for(int x:p) cout<<x<<' ';cout<<endl;

	return 0;
}