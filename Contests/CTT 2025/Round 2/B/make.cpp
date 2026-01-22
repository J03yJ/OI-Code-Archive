#include<bits/stdc++.h>

using namespace std;

signed main(){
	mt19937 rng(4649);
	int n=300;
	
	int T=100;
	while(T--){
		int k=rng()%(5)+1;
		ofstream fout("make.out");
		fout<<n/2<<' '<<k<<endl;
		vector<int> a(n);
		iota(a.begin(),a.end(),1);
		shuffle(a.begin(),a.end(),rng);
		for(int i=0;i<n;i+=2){
			if(a[i]>a[i+1]) swap(a[i],a[i+1]);
			fout<<a[i]<<' '<<a[i+1]<<' '<<1<<endl;
		}
		fout.close();

		system("B < make.out > B.out");
		system("brute < make.out > brute.out");
		cout<<"Left Cases : "<<T<<endl;
		if(system("fc B.out brute.out > tmp")){
			cout<<"???"<<endl;
			system("pause");
		}
	}

	return 0;
}