#include<bits/stdc++.h>

using namespace std;

ifstream fin("skyscraper.in");
ofstream fout("skyscraper.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;

signed main(){
	int n;
	cin>>n;
	vector<array<int,2>> a(n);
	for(auto &x:a) cin>>x[0];
	for(auto &x:a) cin>>x[1];

	sort(a.begin(),a.end(),[](auto x,auto y){return x[1]>y[1];});

	ll ans=0,cmx=0;
	for(auto x:a){
		if(x[0]>cmx){
			ans+=1ll*x[1]*(x[0]-cmx);
			cmx=x[0];
		}
	}

	cout<<ans<<endl;

	return 0;
}