#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

int p[N],n;
vector<int> tmp[N];

vector<int> d[N];
int ntp[N],pri[N],mu[N],phi[N],pcnt;
inline void Init(int lim){
	ntp[1]=1,mu[1]=1,phi[1]=1;
	for(int i=2;i<=lim;i++){
		if(!ntp[i]) pri[++pcnt]=i,phi[i]=i-1,mu[i]=-1;
		for(int j=1;pri[j]*i<=lim&&j<=pcnt;j++){
			ntp[pri[j]*i]=1;
			if(i%pri[j]){
				phi[pri[j]*i]=phi[pri[j]]*phi[i];
				mu[pri[j]*i]=-mu[i];
			}else{
				phi[pri[j]*i]=pri[j]*phi[i];
				mu[pri[j]*i]=0;
				break ;
			}
		}
	}
	for(int i=1;i<=lim;i++) for(int j=i;j<=lim;j+=i) d[j].push_back(i);
}


signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];

	Init(n);
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j:d[i]){
			for(int k:d[p[i]]) tmp[j].push_back(k);
		}
	}
	for(int i=1;i<=n;i++){
		sort(tmp[i].begin(),tmp[i].end());
		int x=0,r=0;
		for(int j:tmp[i]){
			if(j!=x) x=j,r=0;
			ans+=mu[i]*mu[j]*++r;
		}
	}

	ll sum=0;
	for(int i=1;i<=n;i++) sum+=phi[i];
	ans=2*sum-ans;
	ans=1ll*n*(n+1)/2-ans;

	cout<<ans<<endl;

	return 0;
}