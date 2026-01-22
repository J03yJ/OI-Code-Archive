#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;

	ofstream inf("sol.in");
	int n=3,m=500,v=1000000000;
	inf<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			inf<<rng()%v+1<<' ';
		}
		inf<<endl;
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