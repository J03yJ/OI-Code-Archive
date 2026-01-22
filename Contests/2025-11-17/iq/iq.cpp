#include<bits/stdc++.h>

using namespace std;

ifstream fin("iq.in");
ofstream fout("iq.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

int a[N],n,k,p;
inline void Solve(){
	cin>>n>>k>>p;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=0;
	sort(a+1,a+n+1);
	for(int i=1,o=-1;i<=n;i++){
		if(a[i]<p) continue ;
		if(!~o) o=i-1;
		int t=max(0,a[i]-p-k);
		if(n-i<t) continue ;	
		int l=0,r=o+1;
		while(l+1<r){
			int mid=l+r>>1;
			int x=t+max(0,p-a[mid]);
			if(x<=mid-1) r=mid;
			else l=mid;
		}
		ans=max(ans,i-l);
	}
	for(int i=n,o=-1;i>=1;i--){
		if(a[i]>p+k) continue ;
		if(!~o) o=i+1;
		int t=max(0,p-a[i]);
		if(i-1<t) continue ;
		int l=o-1,r=n+1;
		while(l+1<r){
			int mid=l+r>>1;
			int x=t+max(0,a[mid]-p-k);
			if(x<=n-mid) l=mid;
			else r=mid;
		}
		ans=max(ans,r-i);
	}

	cout<<ans<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}