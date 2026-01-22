#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e3+9;
const ll inf=1e18;

ll f[N],g[N],w[N][N];
int a[N],c[N],n,k,p;

inline void Work(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=l+r>>1,p=-1;
	g[mid]=-inf;
	for(int i=max(0,L);i<=min(R,mid-2);i++){
		if(f[i]+w[i][mid]>g[mid]){
			g[mid]=f[i]+w[i][mid];
			p=i;
		}
	}
	Work(l,mid-1,L,p);
	Work(mid+1,r,p,R);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k>>p;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>c[i];

	for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n;j++) w[i][j+1]=w[i][j]+1ll*c[j-i]*a[j];
	}

	ll ans=-inf;
	for(int i=1;i<=n+1;i++) f[i]=-inf;
	for(int i=0;i<=n+1;i++) g[i]=-inf;
	for(int o=1;o<=n+1;o++){
		Work(o+1,n+1,0,n);
		for(int i=o;i<=n+1;i++) g[i]=max(g[i]+p,f[i-1]);
		if(n+1-o<=k) ans=max(ans,g[n+1]);
		for(int i=0;i<=n+1;i++) f[i]=exchange(g[i],-inf);
	}

	cout<<ans<<endl;

	return 0;
}