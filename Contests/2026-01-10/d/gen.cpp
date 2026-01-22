#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;

	int n=100000,q=100000;
	ofstream inf("d.in");
	inf<<n<<' '<<q<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%i<<' ';inf<<endl;
	for(int i=1;i<=q;i++){
		int op=rng()%2+1;
		inf<<op<<' ';
		if(op==1){
			int x=rng()%n+1;
			inf<<x<<' '<<rng()%x<<endl;
		}else inf<<rng()%n+1<<endl;
	}
	inf.flush(),inf.close();

	system("copy d.in b.in > temp");
	system("run d -w > temp");
	system("run b -w > temp");
	return !system("fc d.out b.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}