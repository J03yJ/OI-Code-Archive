#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

const int N=1e5+9;
const int B=20;

struct Basis{
	int b[B],z;
	inline void Insert(int x){
		for(int i=B-1;~i;i--){
			if(~x>>i&1) continue ;
			if(!b[i]){
				b[i]=x;
				return ;
			}else x^=b[i];
		}
		z++;
	}
	inline bool Find(int x){
		for(int i=B-1;~i;i--){
			if(~x>>i&1) continue ;
			x^=b[i];
		}
		return !x;
	}
}b[N];

int a[N],n,q;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++){
		b[i]=b[i-1];
		b[i].Insert(a[i]);
	}

	while(q--){
		int x,p;
		cin>>p>>x;
		if(!b[p].Find(x)) cout<<0<<endl;
		else cout<<QPow(2,b[p].z)<<endl;
	}

	return 0;
}