#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

int a[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	auto F=[](ll a,ll x){return abs(x)+abs(x-a);};
	ll lpos=-2e13,bs=0,ks=0,dlt=0;
	priority_queue<ll> p;
	for(int i=1;i<=n;i++){
		dlt-=max(a[i]-a[i-1],0);
		ks-=2;
		bs+=F(a[i],lpos-dlt);
		p.push(dlt),p.push(dlt);
		p.push(a[i]+dlt),p.push(a[i]+dlt);
		while(ks+p.size()>0) p.pop();
	}
	vector<ll> tmp;
	while(p.size()) tmp.push_back(p.top()),p.pop();
	reverse(tmp.begin(),tmp.end());
	tmp.insert(tmp.begin(),lpos);
	for(int i=0;i<2*n;i++) bs+=(ks+i)*(tmp[i+1]-tmp[i]);

	cout<<bs<<endl;

	return 0;
}