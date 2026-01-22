#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int n,x0,x1,y0,y1;
	cin>>n>>x0>>y0>>x1>>y1;
	vector<array<int,4>> a(n);
	for(auto &t:a) for(int k:{0,1,2,3}) cin>>t[k];

	double sum=0,lst=y0;
	sort(a.begin(),a.end(),[](auto x,auto y){return x[3]>y[3];});
	while(a.size()&&a.back()[3]<y1) a.pop_back();
	for(auto t:a){
		if(t[3]<lst) sum+=lst-t[3];
		lst=min(lst,(double)t[1]);
	}
	sum+=max(double(0),lst-y1);

	cout<<fixed<<setprecision(1)<<sum<<endl;

	return 0;
}