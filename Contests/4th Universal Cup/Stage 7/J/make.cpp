#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;
	int n=100,m=100,v=16;
	ofstream inf("make.out");
	inf<<1<<endl;
	inf<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%v<<' ';inf<<endl;
	for(int i=1;i<=m;i++) inf<<rng()%v<<' ';inf<<endl;
	inf.flush();
	inf.close();

	system("copy make.out J.in > temp");
	system("copy make.out bJ.in > temp");
	system("run J > temp");
	system("run bJ > temp");

	return !system("fc J.out bJ.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}