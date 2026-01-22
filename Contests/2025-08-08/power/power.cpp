#include<bits/stdc++.h>

using namespace std;

ifstream fin("power.in");
ofstream fout("power.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;

inline ll LCM(ll x,ll y){return x/__gcd(x,y)*y;}
ll n,m;

signed main(){
	cin>>n>>m;

	ll cnt=n-1,ans=1;
	vector<int> vis(sqrt(n)+3,0);
	for(int i=2;i<=sqrt(n);i++){
		if(vis[i]) continue ;
		int lim=1;ll cur=i;
		while(cur<=n){
			lim++;
			if(cur<=sqrt(n)) vis[cur]=1;
			cur*=i;
		}
		lim--;
		cnt-=lim;
		for(int mn=1;mn<=lim;mn++){
			vector<int> p;
			for(int j=mn+1;j<=lim;j++){
				bool flag=1;
				for(int k=mn+1;k<j;k++) if(j%k==0) flag&=0;
				if(flag) p.push_back(j);
			}
			for(int sta=0;sta<(1<<p.size());sta++){
				ll lcm=mn;
				for(int i=0;i<lim-mn;i++){
					if(~sta>>i&1) continue ;
					lcm=LCM(lcm,p[i]);
				}
				if(__builtin_popcount(sta)&1^1) ans+=1ll*mn*m/lcm;
				else ans-=1ll*mn*m/lcm;
			}
		}
	}
	ans+=cnt*m;

	cout<<ans<<endl;

	return 0;
}