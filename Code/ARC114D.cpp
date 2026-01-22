#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e3+9;

int a[N],t[N],cnt[N<<1],c[N<<1],n,k;
ll f[N<<2],g[N<<2];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=k;i++) cin>>t[i];

	vector<int> val({int(-1e9-7)});
	val.insert(val.end(),a+1,a+n+1);
	val.insert(val.end(),t+1,t+k+1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	int m=val.size()-1;

	for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
	for(int i=1;i<=k;i++) t[i]=lower_bound(val.begin(),val.end(),t[i])-val.begin();
	for(int i=1;i<=n;i++) cnt[a[i]]++;
	for(int i=1;i<=k;i+=2){
		for(int j=t[i];j<t[i+1];j++) c[j]=1;
	}


	memset(f,0x3f,sizeof f);
	f[N+0]=0;
	for(int i=1;i<m;i++){
		memset(g,0x3f,sizeof g);
		for(int j=-n;j<=n;j++) g[N+j+cnt[i]]=f[N+j];
		for(int j=n;j>=-n;j--) g[N+j]=min(g[N+j],g[N+j+1]);
		for(int j=-n;j<=n;j++){
			if((j^c[i])&1) g[N+j]=0x3f3f3f3f3f3f3f3f;
			else g[N+j]+=1ll*abs(j)*(val[i+1]-val[i]);
		}
		memcpy(f,g,sizeof f);
	}
	for(int j=-n;j<=n;j++) g[N+j+cnt[m]]=f[N+j];
	for(int j=n;j>=-n;j--) g[N+j]=min(g[N+j],g[N+j+1]);

	cout<<(g[N+0]!=0x3f3f3f3f3f3f3f3f?g[N+0]:-1)<<endl;

	return 0;
}