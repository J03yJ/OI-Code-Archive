#include<bits/stdc++.h>

using namespace std;

using bint=__int128;
using ll=long long;
const int N=1e5+9;

int n;
ll x[N],y[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];

	bint lx=0,tx=0,ty=0;
	for(int i=1;i<n;i++){
		bint _x=x[i]-x[n],_y=y[i]-y[n];
		if(_y<0) _y=-_y,_x=-_x;
		while(ty){
			ll tmp=_y/ty;
			_y-=tmp*ty;
			_x-=tmp*tx;
			swap(_y,ty),swap(_x,tx);
		}
		lx=__gcd(lx,tx>0?tx:-tx);
		swap(_y,ty),swap(_x,tx);
	}

	if(!lx||!ty) cout<<-1<<endl;
	else cout<<ll(lx*ty)<<endl;

	return 0;
}