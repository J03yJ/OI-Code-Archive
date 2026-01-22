#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;

	ofstream inf("sol.in");
	int n=20,q=20;
	inf<<n<<' '<<q<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%(2*n)<<' ';inf<<endl;
	for(int i=1;i<=q;i++){
		int l=rng()%n+1,r=rng()%n+1;
		if(l>r) swap(l,r);
		inf<<l<<' '<<r<<endl;
	}

	inf.flush();
	inf.close();

	system("copy sol.in bf.in > temp");
	system("run sol > temp");
	system("run bf > temp");

	return !system("fc sol.out bf.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}