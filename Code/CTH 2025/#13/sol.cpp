#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;
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
inline int Inv(int x){return QPow(x,mod-2);}

int n;
ll a[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<int> stk;
	for(int i=1;i<=n;i++){
		while(stk.size()>1){
			int j=stk.end()[-1],k=stk.end()[-2];
			if((a[i]-a[j])*(j-k)>=(a[j]-a[k])*(i-j)) stk.pop_back();
			else break ;
		}
		stk.push_back(i);
	}

	int ans=0;
	for(int i=0;i+1<stk.size();i++) AddAs(ans,Mul((a[stk[i]]+a[stk[i+1]])%mod,stk[i+1]-stk[i]));
	AddAs(ans,(a[stk.front()]+a[stk.back()])%mod);
	MulAs(ans,Inv(Mul(2,n)));
	
	cout<<ans<<endl;

	return 0;
}