#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e3+9;

int a[N],b[N],c[N][N],n,m;
inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];

	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) c[i][j]=a[i]^b[j];
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(c[i][j+1]!=c[i][j]+1) continue ;
			if(c[i+1][j]!=c[i][j]+2) continue ;
			if(c[i+1][j+1]!=c[i][j]+3) continue ;
			ans++;
		}
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