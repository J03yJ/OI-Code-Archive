#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int n;
	cin>>n;
	vector<int> a(n);
	for(int &x:a) cin>>x;

	sort(a.begin(),a.end());

	int sum=0,ans=0;
	for(int i=0;i<n;i++){
		AddAs(ans,Mul(Add(a[i],sum),a[i]));
		AddAs(sum,sum);
		AddAs(sum,a[i]);
	}

	cout<<ans<<endl;

	return 0;
}