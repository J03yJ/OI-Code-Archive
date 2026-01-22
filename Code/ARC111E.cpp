#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

#define Sum0(x) ((x)+1)
#define Sum1(x) ((x)*((x)+1)/2)
inline ll FloorSum(ll a,ll b,ll c,ll n){
	if(!a) return Sum0(n)*(b/c);
	if(a>=c||b>=c) return Sum1(n)*(a/c)+Sum0(n)*(b/c)+FloorSum(a%c,b%c,c,n);
	ll m=(a*n+b)/c;
	return n*m-FloorSum(c,c-b-1,a,m-1);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		ll lim=(d-1)/(c-b);
		ll s0=FloorSum(b,a-1,d,lim);
		ll s1=FloorSum(c,a,d,lim);
		cout<<lim-(s1-s0)<<endl;
	}

	return 0;
}