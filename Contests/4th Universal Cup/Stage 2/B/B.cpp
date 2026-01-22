#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int T=5e2+9;
const int K=6;
const ll inf=1e18;

ll f[K][T],g[K][T];
int a[N],b[N],n,k;

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

	int lim=k*100;
	for(int i=0;i<=k;i++) for(int j=0;j<=lim;j++) f[i][j]=g[i][j]=-inf;
	f[0][0]=g[0][0]=0;
	for(int i=1;i<=n;i++){
		if(a[i]<=100){
			for(int j=k-1;~j;j--){
				for(int p=0;p+a[i]<=lim;p++){
					f[j+1][p+a[i]]=max(f[j+1][p+a[i]],f[j][p]+b[i]);
				}
			}
		}else{
			for(int j=k-1;~j;j--){
				for(int p=0;p+b[i]<=lim;p++){
					g[j+1][p+b[i]]=max(g[j+1][p+b[i]],g[j][p]+a[i]);
				}
			}
		}
	}

	ll ans=0;
	for(int i=0;i<=k;i++){
		vector<int> s,t;
		for(int p=0;p<=lim;p++) if(f[i][p]>=0) s.push_back(p);
		for(int q=0;q<=lim;q++) if(g[k-i][q]>=0) t.push_back(q);
		for(int p:s){
			for(int q:t){
				ans=max(ans,(f[i][p]+q)*(g[k-i][q]+p));
			}
		}
	}

	cout<<ans<<endl;

	for(int i=0;i<=k;i++) for(int j=0;j<=lim;j++) f[i][j]=g[i][j]=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();
	
	return 0;
}