#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n=20,m=190;
	cout<<n<<' '<<m<<endl;
	mt19937 rng(4649);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++) cout<<i<<' '<<j<<' '<<rng()%10000<<endl;
	}
	
	return 0;
}