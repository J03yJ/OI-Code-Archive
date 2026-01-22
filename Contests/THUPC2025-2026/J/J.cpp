#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		ll n,m;
		cin>>n>>m;
		if(~n&1) cout<<"NO"<<endl;
		else{
			ll cnt=0,x=m;
			while(true){
				ll y=1ull<<__lg(x)+1;
				y-=x;
				if(x==y) break ;
				cnt++,x=y;
			}
			int k=__lg(x)+1;
			if(~k&1) cout<<"NO"<<endl;
			else if(cnt*2+1>n) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}

	return 0;
}