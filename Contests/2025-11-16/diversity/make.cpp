#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n=2.5e3,m=5e3,c=5e2,v=1e9;
	cout<<n<<' '<<m<<' '<<c<<endl;
	mt19937 rng(4649);
	for(int i=1;i<=n;i++) cout<<rng()%v+1<<' '<<rng()%5+1<<' '<<rng()%c+1<<endl;
	for(int i=1;i<=c;i++) cout<<rng()%v+1<<endl;
	
	return 0;
}