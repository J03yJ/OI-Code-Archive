#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e2+9;

ll sf[N*N],sg[N*N];
int p[N][N],cnt[N*N],n,m,a,b;

inline void Solve(){
	cin>>n>>m>>a>>b;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>p[i][j],cnt[p[i][j]]++;
	}

	sort(cnt+1,cnt+n*m+1,greater<int>());
	for(int i=1;i<=n*m;i++) sf[i]=sf[i-1]+1ll*cnt[i]*(i-1)*b,sg[i]=sg[i-1]+1ll*cnt[i]*a;
	ll ans=LLONG_MAX;
	for(int k=0;k<=n*m;k++){
		ll res=1ll*cnt[0]*k*b+sf[k]+sg[n*m]-sg[k];
		ans=min(ans,res);
	}

	cout<<ans<<endl;

	for(int i=0;i<=n*m;i++) cnt[i]=sf[i]=sg[i]=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}