#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int n,q;
ll v[N],l[N],t[N];

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1;i<=n;i++) cin>>l[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>t[i];

	multiset<pair<ll,int>> sv,sl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}