#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
const int N=6e4+9;
const int B=62;

int w[64],n;
ll a[N],fa[N],f[64][64][64],g[64][64][64],lim;
inline void Init(){
	for(int i=0;i<=B-6;i++){
		for(int s=0;s<64;s++){
			if(!i&&!s) continue ;
			int cnt=0,x=s;
			while(x<64){
				cnt++;
				x+=w[i+__builtin_popcountll(x)];
			}
			f[i][s][0]=x&63;
			g[i][s][0]=cnt;
		}
	}
	for(int k=1;k<=B-6;k++){
		for(int i=0;i<=B-k-6;i++){
			for(int s=0;s<64;s++){
				f[i][s][k]=f[i+1][f[i][s][k-1]][k-1];
				g[i][s][k]=g[i][s][k-1]+g[i+1][f[i][s][k-1]][k-1];
			}
		}
	}
}
inline array<ll,2> F(ll x,ll lim){
	ll i=x>>6,b=x&63,li=lim>>6,trg=li-1,cnt=0;
	for(int k=0;k<=B;k++){
		if(~i>>k&1) continue ;
		if(i+(1ll<<k)>trg) continue ;
		cnt+=g[__builtin_popcountll(i)][b][k];
		b=f[__builtin_popcountll(i)][b][k];
		i+=(1ll<<k);
	}
	for(int k=B;k>=0;k--){
		if(i>>k&1) continue ;
		if(i+(1ll<<k)>trg) continue ;
		cnt+=g[__builtin_popcountll(i)][b][k];
		b=f[__builtin_popcountll(i)][b][k];
		i+=(1ll<<k);
	}
	x=i<<6|b;
	while(x<=lim){
		cnt++;
		x+=w[__builtin_popcountll(x)];
	}
	return {cnt,x};
}
inline ll LCA(ll x,ll y){
	if(x>y) swap(x,y);
	if(F(x,y-1)[1]==y) return y;
	ll sum=0;
	for(int k=B;k>=0;k--){
		if(F(x,sum|(1ll<<k))[1]!=F(y,sum|(1ll<<k))[1]){
			sum|=(1ll<<k);
		}
	}
	x=F(x,sum)[1],y=F(y,sum)[1];
	if(x>y) swap(x,y);
	return x+w[__builtin_popcountll(x)];
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>lim;
	for(int i=1;i<=B;i++) cin>>w[i];
	for(int i=1;i<=n;i++) cin>>a[i];

	Init();
	ll sum=0;
	vector<ll> cur;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		vector<ll> lft;
		for(ll x:cur){
			ll f=LLONG_MAX;
			for(ll y:cur){
				if(y==x) break ;
				if(F(x,a[i]-1)[1]!=F(y,a[i]-1)[1]) continue ;
				f=min(f,LCA(x,y));
			}
			auto tmp=F(x,a[i]-1);
			sum+=tmp[0];
			if(f!=LLONG_MAX){
				auto pmt=F(f,a[i]-1);
				sum-=pmt[0];
			}
			lft.push_back(F(x,a[i]-1)[1]);
		}
		lft.push_back(a[i]);
		sort(lft.begin(),lft.end());
		lft.erase(unique(lft.begin(),lft.end()),lft.end());
		cur=lft;
	}
	for(ll x:cur){
		ll f=LLONG_MAX;
		for(ll y:cur){
			if(y==x) break ;
			if(F(x,lim)[1]!=F(y,lim)[1]) continue ;
			f=min(f,LCA(x,y));
		}
		auto tmp=F(x,lim);
		sum+=tmp[0];
		if(f!=LLONG_MAX){
			auto pmt=F(f,lim);
			sum-=pmt[0];
		}
	}

	cout<<sum<<endl;

	return 0;
}