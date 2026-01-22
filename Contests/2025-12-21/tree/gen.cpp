#include<bits/stdc++.h>

using namespace std;

mt19937 rng(4649);

signed main(){
	int n=1e5,q=1e5,v=1e9,c=1e4;
	cout<<n<<' '<<q<<' '<<rng()%c+1<<endl;
	for(int i=1;i<=n;i++) cout<<rng()%c+1<<' ';cout<<endl;
	for(int i=1;i<=q;i++){
		int op=rng()%3+1,l=rng()%n+1,r=rng()%n+1;
		if(l>r) swap(l,r);
		cout<<op<<' '<<l<<' '<<r<<' ';
		if(op==2){
			int x=rng()%c+1;
			x=-x;
			cout<<x<<' ';
		}
		cout<<endl;
	}

	return 0;
}