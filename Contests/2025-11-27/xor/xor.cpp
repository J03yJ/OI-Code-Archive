#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using Itv=array<ll,2>;

vector<Itv> B(ll l,ll r){
	r++;
	vector<Itv> res;
	for(int k=0;k<60;k++){
		if(~l>>k&1) continue ;
		if(l+(1ll<<k)>r) continue ;
		res.push_back({l,k});
		l+=(1ll<<k);
	}
	for(int k=60;~k;k--){
		if(l+(1ll<<k)>r) continue ;
		res.push_back({l,k});
		l+=(1ll<<k);
	}
	return res;
}
inline Itv X(Itv x,Itv y){
	Itv res;
	res[1]=max(x[1],y[1]);
	res[0]=((x[0]>>res[1])^(y[0]>>res[1]))<<res[1];
	return res;
}
inline vector<Itv> U(vector<Itv> v){
	sort(v.begin(),v.end(),[](Itv a,Itv b){
		return a[0]^b[0]?a[0]<b[0]:a[1]>b[1];
	});
	vector<Itv> r;
	for(auto p:v){
		if(r.size()&&r.back()[0]+(1ll<<r.back()[1])>=p[0]+(1ll<<p[1])) continue ;
		r.push_back(p);
	}
	return r;
}
inline vector<Itv> X(vector<Itv> u,vector<Itv> v){
	vector<Itv> res;
	for(auto p:u) for(auto q:v) res.push_back(X(p,q));
	return U(res);
}
inline vector<Itv> M(vector<Itv> u,vector<Itv> v){
	u.insert(u.end(),v.begin(),v.end());
	return u;
}
inline ll S(ll x){
	if((x&3)==0) return x;
	else if((x&3)==1) return 1;
	else if((x&3)==2) return x+1;
	else return 0;
}
inline ll L(vector<Itv> v){
	ll res=0;
	for(auto p:v) res+=1ll<<p[1];
	return res;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll l,r;
		cin>>l>>r;
		l--;

		if(r-l+1<=12){
			set<ll> s;
			for(ll i=l;i<=r;i++){
				for(ll j=i+1;j<=r;j++) s.insert(S(i)^S(j));
			}
			cout<<s.size()<<endl;
			continue ;
		}

		ll r0=r/4,r3=(r-2)/4;
		ll l0=(l+3)/4,l3=(l+1)/4;
		auto v0=B(l0,r0),v3=B(l3,r3);
		auto a0=U(M(X(v0,v0),X(v3,v3)));
		auto a3=U(X(v0,v3));
		auto a1=v0;
		auto a2=v3;
		a0=U(M(a0,v0));
		a0=U(M(a0,{{0,0}}));
		a3=U(M(a3,v3));
		a1=U(M(a1,{{0,0}}));
		ll ans=L(a0)+L(a1)+L(a2)+L(a3);

		cout<<ans<<endl;
	}

	return 0;
}