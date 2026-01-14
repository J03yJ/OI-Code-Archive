#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=2e5+9;

int x[N],y[N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];

		vector<int> p(n);
		iota(p.begin(),p.end(),1);
		
		vector<int> v(n+1,0);
		sort(p.begin(),p.end(),[](int i,int j){return x[i]<x[j];});
		for(int i=0;i<n/2;i++) v[p[i]]|=1;
		sort(p.begin(),p.end(),[](int i,int j){return y[i]<y[j];});
		for(int i=0;i<n/2;i++) v[p[i]]|=2;

		vector<int> r[4];
		for(int i=1;i<=n;i++) r[v[i]].push_back(i);
		for(int i=0;i<r[0].size();i++) cout<<r[0][i]<<' '<<r[3][i]<<endl;
		for(int i=0;i<r[1].size();i++) cout<<r[1][i]<<' '<<r[2][i]<<endl;

		// vector<pii> ans;
		// for(int i=0;i<r[0].size();i++) ans.push_back({r[0][i],r[3][i]});
		// for(int i=0;i<r[1].size();i++) ans.push_back({r[1][i],r[2][i]});
		// int sum=0;
		// for(pii p:ans) sum+=abs(x[fir(p)]-x[sec(p)])+abs(y[fir(p)]-y[sec(p)]);
		// cout<<sum<<endl;
	}
	
	return 0;
}