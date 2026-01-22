#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;

	ofstream inf("sol.in");
	int n=10,q=10,v=1e9;
	inf<<n<<' '<<q<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%v<<' ';inf<<endl;
	for(int i=1;i<=q;i++){
		int l=rng()%n+1,r=rng()%n+1;
		if(l>r) swap(l,r);
		int k=rng()%(r-l+1)+1;
		inf<<l<<' '<<r<<' '<<k<<endl;
	}

	inf.flush();
	inf.close();

	system("copy sol.in std.in > temp");
	system("run sol > temp");
	system("run std > temp");

	return !system("fc sol.out std.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}