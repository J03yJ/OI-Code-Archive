#include<bits/stdc++.h>

using namespace std;

ifstream fin("kedavra.in");
ofstream fout("kedavra.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e2+9;

inline void Solve(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(auto &x:a) cin>>x;

	cout<<fixed<<setprecision(10);
	if(n==1) cout<<1.0<<endl;
	else{
		int x=-1,y=-1;
		for(int z:a){
			if(z>x) y=x,x=z;
			else if(z>y) y=z;
		}
		if(x==y) cout<<0.0<<endl;
		else cout<<1.0<<endl;
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}