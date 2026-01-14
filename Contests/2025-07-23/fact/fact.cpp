#include<bits/stdc++.h>

using namespace std;

ifstream fin("fact.in");
ofstream fout("fact.out");
#define cin fin
#define cout fout
#define endl '\n'

#define double long double
using ll=long long;
const int mod=1004535809;

// const double k=0.48663000;
const double k=0.5;
inline double F(double x){return ((x+k)*(log(x+k)-1)+1);}

signed main(){
	int T,p,q,b,c,d,e,f,g;
	cin>>T>>p>>q>>b>>c>>d>>e>>f>>g;

	int ans=1;
	while(T--){
		ll l=0,r=1e10;
		while(l+1<r){
			ll mid=l+r>>1;
			if(log((double)(p))*q<=F(mid)) r=mid;
			else l=mid;
		}

		ans=1ll*ans*(r%mod)%mod;

		p=(1ll*b*p+c)%d+1;
		q=(1ll*e*q+f)%g+1;
	}

	cout<<ans<<endl;

	return 0;
}