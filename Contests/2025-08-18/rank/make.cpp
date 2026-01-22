#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

mt19937 rng(4649);

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	const int n=2e5,q=2e5,v=1e9;
	vector<int> a(n);
	// for(int &x:a) x=rng()%v+v;
	for(int &x:a) x=rng()%v;
	sort(a.begin(),a.end());
	cout<<n<<' '<<q<<endl;
	for(int i:a) cout<<i<<' ';cout<<endl;
	for(int i=1;i<=q;i++){
		cout<<rng()%v<<' '<<1<<endl;
	}

	return 0;
}