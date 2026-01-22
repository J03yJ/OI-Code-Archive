#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;

int a[N],x[N],n;
inline bool Check(int k){
	ll sum=0;
	for(int i=1;i<=n;i++){
		if(x[i]>k) return 0;
		sum+=k-x[i];
	}
	return sum>=k;
}
inline int T(){
	int l=-1,r=1e9+7;
	while(l+1<r){
		int mid=l+r>>1;
		if(Check(mid)) r=mid;
		else l=mid;
	}
	return r;
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=1e9+7;
	for(x[1]=0;x[1]<=a[1];x[1]++){
		for(int i=2;i<=n;i++) x[i]=a[i-1]-x[i-1];
		ans=min(ans,T());
		for(int i=1;i<=n;i++) cout<<x[i]<<' ';cout<<endl;
		cout<<T()<<endl;
	}

	cout<<ans<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}