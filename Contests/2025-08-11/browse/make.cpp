#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

signed main(){
	int n=1e6,q=1e6;
	vector<int> a(n);
	cout<<n<<' '<<q<<endl;
	iota(a.begin(),a.end(),1);
	mt19937 rng(4649);
	shuffle(a.begin(),a.end(),rng);
	for(int i:a) cout<<i<<' ';cout<<endl;
	for(int i=1;i<=q;i++) cout<<1<<' '<<i<<' '<<i<<endl;

	return 0;
}