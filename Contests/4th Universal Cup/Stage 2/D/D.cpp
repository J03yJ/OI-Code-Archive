#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

inline int Digit(ll k){
	int sum=0;
	while(k) sum+=k%10,k/=10;
	return sum;
}

inline void ExGCD(ll a,ll b,ll &x,ll &y){
	if(!b) return x=1,y=0,void();
	ExGCD(b,a%b,x,y);
	ll z=x;
	x=y;
	y=z-(a/b)*y;
}

inline void Solve(){
	ll k;
	cin>>k;

	map<int,ll> mp;
	for(int i=1;i<=2*k;i++){
		ll tmp=k*i,c=Digit(tmp);
		if(!mp[c]) mp[c]=tmp;
	}

	for(auto p:mp){
		for(auto q:mp){
			ll a=p.first,b=q.first,x=0,y=0,g=__gcd(a,b);
			if(k%g) continue ;
			ExGCD(a,b,x,y);
			x*=k/g,y*=k/g;
			ll ta=b/g,tb=a/g;
			if(x<0){
				ll c=(abs(x)+ta-1)/ta;
				x+=ta*c,y-=tb*c;
			}
			if(x>0){
				ll c=x/ta;
				x-=ta*c,y+=tb*c;
			}
			if(y<0) continue ;
			ll s=p.second,t=q.second;
			for(int i=1;i<=x;i++) cout<<s;
			for(int i=1;i<=y;i++) cout<<t;
			cout<<endl;
			return ;
		}
	}

	assert(0);
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}