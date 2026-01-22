#include<bits/stdc++.h>

using namespace std;

ifstream fin("ggd.in");
ifstream fans("ggd.out");

using ll=long long;
const int N=1e3+9;

int a[N],grf[N][N],b[N],n,k;

signed main(){
	fin>>n>>k;
	for(int i=1;i<=n;i++) fin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) fin>>grf[i][j];
	}
	string s;
	fans>>s;
	for(int i=1;i<=n;i++) fans>>b[i];

	if(s=="NO") return 0;
	
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=b[i];
	if(cnt!=k){
		cerr<<"Duck Count Neq K."<<' '<<cnt<<endl;
		return 0;
	}
	
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue ;
			if(grf[i][j]&&grf[j][i]){
				if(b[i]==b[j]){
					cerr<<"Invalid Edges. ("<<i<<", "<<j<<")."<<endl;
					return 0;
				}
				if(b[i]==0) ans+=a[i];
				else ans+=a[j];
			}else if(grf[i][j]){
				if(b[i]!=b[j]){
					ans+=1ll*a[i]*a[i];
					ans+=1ll*a[j]*a[j];
				}else if(b[i]==0){
					ans+=1ll*(a[i]+a[j])*(a[i]+a[j]);
				}else if(b[i]==1){
					ans+=1ll*(a[i]-a[j])*(a[i]-a[j]);
				}
			}
		}
	}
	cout<<ans<<endl;

	return 0;
}