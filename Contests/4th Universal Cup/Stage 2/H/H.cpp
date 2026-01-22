#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int n,d;
ll a[N],b[N],tmp[N];

inline ll Get(){
	ll dist=0;
	
	vector<ll> t1,t2;
	for(int i=1;i<=n;i++){
		tmp[i]=b[i];
		if(b[i]>0) t1.push_back(i);
		if(b[i]<0) t2.push_back(i);
	}

	while(t1.size()&&t2.size()){
		dist=max(dist,abs(t1.back()-t2.back()));
		ll t=tmp[t1.back()]+tmp[t2.back()];
		if(t>0){
			t2.pop_back();
			tmp[t1.back()]=t;
		}else if(t<0){
			t1.pop_back();
			tmp[t2.back()]=t;
		}else t1.pop_back(),t2.pop_back();
	}

	assert(t1.empty()&&t2.empty());
	
	return (dist+d-1)/d;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>d;
		for(int i=1;i<=n;i++) cin>>a[i];

		ll sum=0;
		for(int i=1;i<=n;i++) sum+=a[i];
		sum/=n;
		for(int i=1;i<=n;i++) b[i]=a[i]-sum;

		cout<<Get()<<endl;
	}

	return 0;
}