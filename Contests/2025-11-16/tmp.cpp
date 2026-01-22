#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int mod=1e9+7;

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
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		int n=s.size();
		s=" "+s;
		vector<int> a(n+1,0),b(n+1,0),cnt(n+1,0);
		cnt[1]=1;
		int ans=1,k=0;
		for(int i=2,j=0;i<=n;i++){
			while(j&&s[j+1]!=s[i]) j=a[j];
			if(s[j+1]==s[i]) j++;
			a[i]=j,cnt[i]=cnt[a[i]]+1;
		}
		for(int i=2,j=0;i<=n;i++){
			while(j&&s[j+1]!=s[i]) j=a[j];
			if(s[j+1]==s[i]) j++;
			if(j>i/2) j=a[j];
			b[i]=j;
			MulAs(ans,cnt[b[i]]+1);
		}

		cout<<ans<<endl;
	}

	return 0;
}