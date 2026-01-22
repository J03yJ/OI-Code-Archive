#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	
	int T=100;
	while(T--){
		ofstream fout("ruike.in");
		int n=2,v=5;
		fout<<1<<endl;
		fout<<n<<endl;
		for(int i=0;i<n;i++){
			array<int,4> t;
			for(int k=0;k<4;k++) t[k]=rng()%v+1;
			for(int k=0;k<2;k++) if(t[k]>t[k|2]) swap(t[k],t[k|2]);
			for(int k=0;k<4;k++) fout<<t[k]+(k>>1)<<' ';fout<<endl;
		}

		cerr<<"LEFT Tasks : "<<T+1<<endl;
		system("run ruike -w");
		system("run brute -w");
		if(system("fc ruike.out brute.out")){
			cerr<<"???"<<endl;
			break ;
		}
	}

	return 0;
}