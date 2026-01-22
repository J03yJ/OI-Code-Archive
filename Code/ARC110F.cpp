#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n;
	cin>>n;
	
	cout<<n*n<<endl;
	for(int i=n;i;i--) for(int j=n;j--;) cout<<i-1<<endl;

	return 0;
}