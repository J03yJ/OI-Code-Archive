#include<bits/stdc++.h>

using namespace std;

ifstream fin("factory.in");
ofstream fout("factory.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int a[N],b[N],c[N],n,m,k,r;

signed main(){
	cin>>n>>m>>k>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=k;i++) cin>>c[i];

	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	sort(c+1,c+k+1);

	ll ans=0;
	for(int i=1;i<=n;i++) b[i]-=r;
	for(int i=1;i<=n;i++){
		ll L=a[i]+c[1],R=a[i]+c[k];
		ll tmp=-(L+R+1>>1),res=1e18;
		int p=lower_bound(b+1,b+m+1,tmp)-b;
		if(p<=m) res=min(res,max(abs(L+b[p]),abs(R+b[p])));
		if(p-1>=1) res=min(res,max(abs(L+b[p-1]),abs(R+b[p-1])));
		ans=max(ans,res);
	}
	cout<<ans<<endl;

	return 0;
}