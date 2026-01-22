#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;

	ofstream inf("tickets.in");
	int n=10,m=10,k=rng()%m+1,v=100;
	inf<<n<<' '<<m<<' '<<k<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			inf<<rng()%v+1<<' ';
		}
		inf<<endl;
	}
	inf.flush();
	inf.close();

	system("run tickets > temp");

	return !system("run judge > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}