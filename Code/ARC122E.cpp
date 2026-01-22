#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e2+9;

ll a[N];
int vis[N],n;

inline ll GCD(ll x,ll y){return __gcd(x,y);}
inline ll LCM(ll x,ll y){return x/GCD(x,y)*y;}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<ll> ans;
	for(int t=n;t>=1;t--){
		for(int i=1;i<=n;i++){
			if(vis[i]) continue ;
			ll lcm=1;
			for(int j=1;j<=n;j++) if(j!=i&&!vis[j]) lcm=LCM(lcm,GCD(a[i],a[j]));
			if(lcm!=a[i]){
				vis[i]=1;
				ans.push_back(a[i]);
				break ;
			}
		}
	}

	if(ans.size()<n) cout<<"No"<<endl;
	else{
		cout<<"Yes"<<endl;
		reverse(ans.begin(),ans.end());
		for(ll x:ans) cout<<x<<' ';cout<<endl;
	}

	return 0;
}