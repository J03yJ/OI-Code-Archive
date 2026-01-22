#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int n;
array<ll,2> a[N];

inline bool Check(int k){
	ll l1=-1e9,r1=1e9,l2=-1e9,r2=1e9,t=-1e9;
	for(int i=1;i<=n;i++){
		l1-=k*(a[i][0]-t),r1+=k*(a[i][0]-t);
		l2-=k*(a[i][0]-t),r2+=k*(a[i][0]-t);
		t=a[i][0];
		bool f1=l1<=a[i][1]&&a[i][1]<=r1;
		bool f2=l2<=a[i][1]&&a[i][1]<=r2;
		if(f1&&f2){
			l1=min(l1,l2),r1=max(r1,r2);
			l2=r2=a[i][1];
		}else if(f1) l1=r1=a[i][1];
		else if(f2) l2=r2=a[i][1];
		else return 0;
	}
	return 1;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i][0]>>a[i][1];
		sort(a+1,a+n+1);

		int l=-1,r=1e9+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(Check(mid)) r=mid;
			else l=mid; 
		}
		
		if(r==1e9+1) cout<<-1<<endl;
		else cout<<r<<endl;
	}

	return 0;
}