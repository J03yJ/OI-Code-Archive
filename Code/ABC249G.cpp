#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
using uint=unsigned int;
const int N=2e5+9;
const int B=64,HB=32;

struct Basis{
	ull b[B],z;
	Basis(){memset(b,0,sizeof b),z=0;}
	inline ull& operator [](int i){return b[i];}
	inline void Insert(ull x){
		for(int i=B-1;~i;i--){
			if(~x>>i&1) continue ;
			if(!b[i]){
				b[i]=x;
				return ;
			}else x^=b[i];
		}
		z++;
	}
	inline ull Query(uint hb){
		ull ans=0,cnt=0;
		for(int i=B-1;i>=HB;i--) if(b[i]&&((ans^b[i])>>i&1)==(hb>>i-HB&1)) ans^=b[i],cnt++;
		if((ans>>HB)!=hb) return -1;
		for(int i=HB-1;~i;i--) if(b[i]) ans=max(ans,ans^b[i]),cnt++;
		if(!cnt&&!(hb==0&&z)) return -1;
		return ans^(ull(hb)<<HB);
	}
};

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int n;
	cin>>n;
	uint lim;
	cin>>lim;
	vector<array<uint,2>> a(n);
	for(auto &x:a) cin>>x[0]>>x[1];
	
	vector<ull> b(n);
	for(int i=0;i<n;i++) b[i]=ull(a[i][0])<<32|a[i][1];
	Basis tmp;
	for(auto x:b) tmp.Insert(x);
	auto Get=[&tmp](int len){
		Basis t;
		ull msk=ull(-1)^((ull(1)<<len)-1<<HB);		
		for(int i=0;i<B;i++) if(tmp[i]) t.Insert(tmp[i]&msk);
		t.z+=tmp.z;
		return t;
	};

	ll ans=-1;
	for(int i=HB-1;~i;i--){
		if(~lim>>i&1) continue ;
		uint tmp=(ull(lim)>>i+1)<<i+1;
		Basis bs=Get(i);
		ans=max(ans,ll(bs.Query(tmp)));
	}
	Basis bs=Get(0);
	ans=max(ans,ll(bs.Query(lim)));

	cout<<ans<<endl;

	return 0;
}