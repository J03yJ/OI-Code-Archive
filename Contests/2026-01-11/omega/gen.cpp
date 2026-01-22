#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	int m=3e4,n=1e7,k=10;
	cout<<m<<' '<<n<<' '<<k<<endl;
	for(int i=1;i<=k;i++) cout<<rng()%n+1<<' ';cout<<endl;
	for(int i=1;i<=m;i++) cout<<rng()%n+1<<' ';cout<<endl;

	return 0;
}