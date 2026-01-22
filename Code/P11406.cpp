#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
const int lgN=9e0;

int a[N],f[N][lgN],n,q;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<ll> b(a,a+n+1);
	partial_sum(b.begin(),b.end(),b.begin());
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	ll tmp=0;
	for(int i=0;i<=n;tmp+=a[++i]) a[i]=lower_bound(b.begin(),b.end(),tmp)-b.begin()+1;
	b.clear();
	b.shrink_to_fit();
	b.resize(n+1,n+1);
	for(int i=n;i>=0;i--) f[i][0]=b[a[i]],b[a[i]]=i;

	for(int k=0;k<lgN;k++) f[n+1][k]=n+1;
	for(int i=n;i>=0;i--) f[i][0]=min(f[i+1][0],f[i][0]);
	for(int k=1;k<lgN;k++){
		for(int i=0;i<=n;i++) f[i][k]=f[f[f[f[i][k-1]][k-1]][k-1]][k-1];
	}

	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		
		l--;
		int ans=0;
		for(int k=lgN-1;~k;k--){
			while(f[l][k]<=r) l=f[l][k],ans+=1<<(k<<1);
		}

		cout<<ans<<endl;
	}

	return 0;
}