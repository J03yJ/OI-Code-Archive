#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;

int n,m;
ll a[N],b[N],sum[N];
inline void Solve(){
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];

	for(int i=0;i<=n+9;i++){
		sum[i]=a[i];
		if(i) sum[i]+=sum[i-1]/10;
	}
	for(int i=n+9;~i;i--){
		ll k=sum[i]/m;
		b[i]=k;
		a[i]-=k*m;
		if(a[i]<0){
			a[i-1]+=a[i]*10;
			sum[i-1]+=a[i]*10;
		}
	}
	bool flag=0;
	for(int i=n+9;~i;i--){
		if(b[i]) flag=1;
		if(flag) cout<<b[i];
		a[i]=b[i]=0;
	}
	if(!flag) cout<<0;
	cout<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}