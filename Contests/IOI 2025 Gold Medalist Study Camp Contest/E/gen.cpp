#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case "<<++cnt<<endl;
	ofstream inf("E.in");
	int n=8,q=5;
	inf<<n<<' '<<q<<endl;
	vector<int> p(n);
	iota(p.begin(),p.end(),1);
	shuffle(p.begin(),p.end(),rng);
	for(int x:p) inf<<x<<' ';inf<<endl;
	for(int i=1;i<=q;i++){
		int l=rng()%n+1,r=rng()%n+1;
		if(l>r) swap(l,r);
		inf<<l<<' '<<r<<endl;
	}
	inf.flush(),inf.close();

	system("copy E.in b.in > temp");
	system("run E > temp");
	system("run b > temp");
	return !system("fc E.out b.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}