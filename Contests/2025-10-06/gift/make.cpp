#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	int n=5e3,k=20,v=1e6;
	cout<<n<<' '<<k<<endl;
	for(int i=1;i<=n;i++) cout<<rng()%v<<' ';cout<<endl;
}