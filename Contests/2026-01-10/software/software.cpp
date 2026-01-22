#include<bits/stdc++.h>

using namespace std;

ifstream fin("software.in");
ofstream fout("software.out");
#define cin fin
#define cout fout
#define endl '\n'

using bint=__int128;
using ll=long long;

namespace T998{
	const int mod=998244353;
	inline void Solve(){
		string s;
		cin>>s;
		vector<int> a(s.size());
		for(int i=0;i<a.size();i++) a[i]=s[i]-'0';
		reverse(a.begin(),a.end());
		auto Lsh=[&](vector<int> &a){
			for(int i=0;i<a.size();i++){
				if(i&&(a[i]&1)) a[i-1]+=5;
				a[i]>>=1;
			}
		};
		auto Empty=[&](vector<int> &a){
			return !accumulate(a.begin(),a.end(),0ll);
		};
		int ans=1,x=19;
		while(!Empty(a)){
			if(a[0]&1) ans=1ll*x*ans%mod;
			x=1ll*x*x%mod;
			Lsh(a);
		}
		cout<<ans<<endl;
	}
}
namespace T1145{
	const int mod=1145141;
	inline void Solve(){
		string s;
		cin>>s;
		vector<int> a(s.size());
		for(int i=0;i<a.size();i++) a[i]=s[i]-'0';
		reverse(a.begin(),a.end());
		auto Lsh=[&](vector<int> &a){
			for(int i=0;i<a.size();i++){
				if(i&&(a[i]&1)) a[i-1]+=5;
				a[i]>>=1;
			}
		};
		auto Empty=[&](vector<int> &a){
			return !accumulate(a.begin(),a.end(),0ll);
		};
		int ans=1,x=19;
		while(!Empty(a)){
			if(a[0]&1) ans=1ll*ans*x%mod;
			x=1ll*x*x%mod;
			Lsh(a);
		}
		cout<<ans<<endl;
	}
}
namespace Prime{
	int a[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	inline ll QPow(ll x,ll y,ll p){
		ll ans=1;
		while(y){
			if(y&1) ans=bint(ans)*x%p;
			x=bint(x)*x%p;
			y>>=1;
		}
		return ans;
	}
	inline bool Check(ll p){
		if(p<=2||(~p&1)) return p==2;
		ll t=p-1,c=0;
		while(~t&1) t>>=1,c++;
		for(ll x:a){
			if(p==x) continue ;
			ll y=QPow(x,t,p);
			if(y==1||y==p-1) continue ;
			for(int i=0;i<c;i++){
				y=bint(y)*y%p;
				if(y==p-1) break ;
				if(y==1) return 0;
			}
			if(y!=p-1) return 0;
		}
		return 1;
	}
	inline void Solve(){
		ll l,r;
		cin>>l>>r;
		for(ll i=l;i<=r;i++) cout<<(Check(i)?'p':'.');
		cout<<endl;
	}
}

signed main(){
	string Tid;
	cin>>Tid;
	
	int T;
	cin>>T;
	while(T--){
		if(Tid=="1_998244353") T998::Solve();
		else if(Tid=="1?") T1145::Solve();
		else if(Tid=="2p") Prime::Solve();
	}

	return 0;
}