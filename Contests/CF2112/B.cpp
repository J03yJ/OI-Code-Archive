#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int a[N],b[N],c[N],d[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i]>>d[i];

		ll ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]>c[i]) ans+=a[i]-c[i];
			if(b[i]>d[i]){
				ans+=b[i]-d[i];
				ans+=min(a[i],c[i]);
			}
		}

		cout<<ans<<endl;
	}

	return 0;
}