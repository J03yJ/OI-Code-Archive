#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;
	ofstream inf("dameow.in");
	int n=200,m=200;
	inf<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			inf<<rng()%20000<<' ';
		}
		inf<<endl;
	}
	inf.flush(),inf.close();

	system("copy dameow.in b.in > temp");
	system("run dameow -w > temp");
	system("run b -w > temp");
	return !system("fc dameow.out b.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}