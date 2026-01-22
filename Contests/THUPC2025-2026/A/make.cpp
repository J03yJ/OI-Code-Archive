#include<bits/stdc++.h>

using namespace std;

signed main(){
	const int n=5e5,m=5e5,q=5e5;

	cout<<n<<' '<<m<<' '<<q<<endl;
	for(int i=1;i<n;i++) cout<<i<<' '<<i+1<<endl;
	for(int i=1;i<=n;i++) cout<<n<<' ';cout<<endl;
	for(int i=1;i<=q;i++){
		cout<<i<<' '<<i<<' '<<n<<endl;
	}

	return 0;
}