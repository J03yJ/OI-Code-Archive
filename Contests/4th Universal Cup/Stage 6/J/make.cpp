#include<bits/stdc++.h>

using namespace std;

int cnt;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;
	int n=2e5,m=rng()%1000000000+1,q=2e5;
	// int n=10,m=rng()%15+1,q=10;
	vector<int> a(n);
	for(int &x:a) x=rng()%m;
	vector<int> l(q),r(q),v(q);
	for(int i=0;i<q;i++){
		l[i]=rng()%n+1,r[i]=rng()%n+1,v[i]=rng()%m;
		if(l[i]>r[i]) swap(l[i],r[i]);
	}

	ofstream fout=ofstream("J.in");
	fout<<n<<' '<<q<<' '<<m<<endl;
	for(int i=0;i<n;i++) fout<<a[i]<<' ';fout<<endl;
	for(int i=0;i<q;i++) fout<<l[i]<<' '<<r[i]<<' '<<v[i]<<endl;
	fout.flush();
	// system("run J > temp");

	// fout=ofstream("brute.in");
	// fout<<n<<' '<<q<<' '<<m<<endl;
	// for(int i=0;i<n;i++) fout<<a[i]<<' ';fout<<endl;
	// for(int i=0;i<q;i++) fout<<l[i]<<' '<<r[i]<<' '<<v[i]<<endl;
	// system("run brute > temp");

	// return !system("fc J.out brute.out > temp");
	return 1;
}

signed main(){
	// while(Test()) ;
	Test();

	return 0;
}