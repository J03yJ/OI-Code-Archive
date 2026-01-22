#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
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

int a[N],n;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	if(n&1){
		int ans=1,cnt=0;
		for(int i=1;i<=n;i++){
			if(a[i]) cnt++;
			else{
				MulAs(ans,Mul(cnt,cnt-1));
				cnt--;
			}
		}
		if(cnt!=1) ans=0;
		cout<<ans<<endl;
	}else{
		int ans=1,cnt=0;
		for(int i=1;i<=n;i++){
			if(a[i]) cnt++;
			else{
				ans=Add(Mul(ans,Mul(cnt,cnt-1)),Mul(ans,cnt));
				cnt--;
			}
		}
		if(cnt!=0) ans=0;
		cout<<ans<<endl;
	}

	return 0;
}