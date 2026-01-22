#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e3+9;
const long double k=1.01;
const int mod=998244353;

template<class S,class T> inline void AddAs(S &x,T y){if((x+=y)>=mod) x-=mod;}
template<class S,class T> inline void SubAs(S &x,T y){if((x-=y)<0) x+=mod;}
template<class S,class T> inline void MulAs(S &x,T y){x=1ll*x*y%mod;}
template<class S,class T> inline S Add(S x,T y){if((x+=y)>=mod) x-=mod;return x;}
template<class S,class T> inline S Sub(S x,T y){if((x-=y)<0) x+=mod;return x;}
template<class S,class T> inline S Mul(S x,T y){return 1ll*x*y%mod;}
template<class S,class T> inline S QPow(S x,T y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

int n;
ll a[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<array<ll,3>> cur;
	cur.push_back({0,0,1});
	for(int i=1;i<=n;i++){
		auto f=cur,g=cur;
		for(auto &x:g) x[0]+=a[i],x[1]+=a[i];
		vector<array<ll,3>> tmp;
		auto Insert=[&](array<ll,3> x){
			while(tmp.size()&&tmp.back()[1]+(tmp.back()[1]+99)/100>x[0]){
				AddAs(x[2],tmp.back()[2]);
				x[0]=min(x[0],tmp.back()[0]);
				x[1]=max(x[1],tmp.back()[1]);
				tmp.pop_back();
			}
			tmp.push_back(x);
		};
		int j=0,k=0;
		while(j<f.size()&&k<g.size()){
			if(f[j][0]<g[k][0]) Insert(f[j++]);
			else Insert(g[k++]);
		}
		while(j<f.size()) Insert(f[j++]);
		while(k<g.size()) Insert(g[k++]);
		cur=tmp;
	}

	ll sum=0;
	cout<<cur.size()-1<<endl;
	for(int i=0;i+1<cur.size();i++){
		AddAs(sum,cur[i][2]);
		cout<<cur[i][1]<<' '<<cur[i+1][0]<<' '<<sum<<endl;
	}

	return 0;
}