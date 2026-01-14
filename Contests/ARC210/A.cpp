#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

int n,q;
ll a[N],d[N];

signed main(){
	cin>>n>>q;
	fill(d+1,d+n+1,1);
	while(q--){
		int i,x;
		cin>>i>>x;
		a[i]+=x;
		d[i+1]=max(d[i+1],a[i]-a[i+1]+1);
	}

	for(int i=1;i<=n;i++) d[i]+=d[i-1];

	ll sum=0;
	for(int i=1;i<=n;i++) sum+=d[i];

	cout<<sum<<endl;

	return 0;
}