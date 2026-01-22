#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
const int V=(1<<10)+9;
const int mod=998244353;

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

int a[N],f[V][V],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	for(int i=0;i<1024;i++){
		for(int j=0;j<1024;j++) f[i][j]=1;
	}

	for(int i=1;i<=n;i++){
		int hi=a[i]>>10,lo=a[i]&1023;
		for(int j=0;j<1024;j++){
			if((hi|j)==j) MulAs(f[j][lo],a[i]);
		}
		int res=1;
		for(int j=0;j<1024;j++){
			if((j|lo)==lo) MulAs(res,f[hi][j]);
		}
		cout<<res<<endl;
	}

	return 0;
}