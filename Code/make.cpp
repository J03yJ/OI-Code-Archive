#include<bits/stdc++.h>

using namespace std;

int cnt=0;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case : "<<++cnt<<endl;
	int n=3e5,p=3,d=5,lim=243,v=1e9;
	ofstream inf("QOJ15509.in");
	inf<<n<<' '<<d<<' '<<p<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%lim<<' ';inf<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%v+1<<' ';inf<<endl;
	for(int i=0;i<lim;i++) inf<<rng()%v+1<<' ';inf<<endl;
	int q=3e5;
	inf<<q<<endl;
	for(int i=1;i<=q;i++){
		inf<<rng()%v<<' '<<rng()%v<<' '<<rng()%v<<' ';
		int l1=rng()%lim,r1=rng()%lim,l2=rng()%n+1,r2=rng()%n+1;
		if(l1>r1) swap(l1,r1);
		if(l2>r2) swap(l2,r2);
		inf<<l1<<' '<<r1<<' '<<l2<<' '<<r2<<endl;
	}

	// system("copy QOJ15509.in brute.in > temp");
	// cerr<<"S1!"<<endl;
	// system("run QOJ15509 > temp");
	// cerr<<"S2!"<<endl;
	// system("run brute > temp");
	// cerr<<"S3!"<<endl;

	return !system("fc QOJ15509.out brute.out > temp");
}

signed main(){
	while(Test()) ;

	return 0;
}