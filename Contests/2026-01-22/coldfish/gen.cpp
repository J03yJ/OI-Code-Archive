#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;
	
	ofstream inf("coldfish.in");
	inf<<5<<endl;
	
	for(int T=5;T--;){
		int n=7+rng()%6;
		inf<<n<<endl;
		vector<int> a(n+1,0);
		int x=rng()%n+1,c=rng()&1;
		for(int i=1,r=5;i<=10+rng()%11;i++){
			a[x]++;
			if(rng()%r==0) c^=1;
			if(x==1&&c==0) c=1,x=2;
			else if(x==n&&c==1) c=0,x=n-1;
			else x+=c?1:-1;
		}
		for(int i=1;i<=n;i++) inf<<a[i]<<' ';inf<<endl;
	}

	inf.flush(),inf.close();

	system("copy coldfish.in brute.in > temp");
	system("run coldfish -w > temp");
	system("run brute -w > temp");
	return !system("fc coldfish.out brute.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}