#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);

	int n=6,t=400;
	for(int o=1;o<=t;o++){
		vector<int> a(n+1,0);
		ofstream fout("I.in");
		fout<<n<<endl;
		for(int i=1;i<=n;i++) fout<<(a[i]=rng()%n+1)<<' ';cout<<endl;
		fout.flush(),fout.close();
		int typ=system("I.exe < I.in > I.out");
		if(typ!=0){
			cerr<<"# "<<o<<" Get Runtime Error."<<endl;
			cerr<<n<<endl;
			for(int i=1;i<=n;i++) cerr<<a[i]<<' ';cout<<endl;
			break ;
		}else cerr<<"# "<<o<<" Run Successfully."<<endl;
	}

	return 0;
}