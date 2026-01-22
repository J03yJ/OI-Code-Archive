#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int T=3e1+9;

int a[N],m[N],n;
ll f[N][T],g[N][T];
vector<int> val[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++){
		for(int j=max(1-i,-4);j<=min(n-i,4);j++){
			for(int k:{-1,0,1}) val[i].push_back(a[i+j]+k);
		}
		sort(val[i].begin(),val[i].end());
		val[i].erase(unique(val[i].begin(),val[i].end()));
		m[i]=val[i].size();
	}

	ll ans=0x3f3f3f3f3f3f3f3f;
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	for(int j=0;j<m[1];j++) f[1][j]=g[1][j]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m[i];j++){
			f[i][j]+=abs(a[i]-val[i][j]);
			g[i][j]+=abs(a[i]-val[i][j]);
		}
		for(int j=0;j<m[i];j++){
			for(int k=0;k<m[i+1];k++){
				if(val[i][j]<val[i+1][k]) g[i+1][k]=min(g[i+1][k],f[i][j]);
				else if(val[i][j]==val[i+1][k]){
					f[i+1][k]=min(f[i+1][k],f[i][j]);
					g[i+1][k]=min(g[i+1][k],g[i][j]);
				}else f[i+1][k]=min(f[i+1][k],g[i][j]);
			}
		}
	}
	for(int j=0;j<m[n];j++) ans=min(ans,min(f[n][j],g[n][j]));

	cout<<ans<<endl;

	return 0;
}