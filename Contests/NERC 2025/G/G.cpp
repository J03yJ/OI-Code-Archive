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

	if(n&1){
		ll sum=0;
		for(int i=2;i<=n;i++){
			if(~i&1) sum+=a[i];
			else sum-=a[i];
		}
		sum+=a[1];
		x[1]=sum>>1;
		for(int i=2;i<=n;i++) x[i]=a[i]-x[i-1];
	}else{
		ll bp=0,bn=-1e18,l=0,r=1e18,c=0;
		for(int i=2;i<=n;i++){
			if(~i&1) c+=a[i];
			else c-=a[i];
			if(~i&1){
				bn=max(bn,c);
				r=min(r,c);
			}else{
				bp=max(bp,-c);
				l=max(l,c);
			}
		}
		x[1]=min(max(bn-bp>>1,l),r);
		for(int i=2;i<=n;i++) x[i]=a[i]-x[i-1];
	}

	cout<<T()<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}