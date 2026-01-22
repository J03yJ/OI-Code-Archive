#include<bits/stdc++.h>

using namespace std;

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

inline int BruteC(int n,int m){
	int p=1,q=1;
	for(int i=1;i<=m;i++) MulAs(q,i);
	for(int i=1;i<=m;i++) MulAs(p,n-i+1);
	return Mul(p,Inv(q));
}

signed main(){
	int n,m;
	cin>>n>>m;
	vector<int> a(n);
	for(int &x:a) cin>>x;

	int sum=accumulate(a.begin(),a.end(),0);
	cout<<BruteC(m+n,sum+n)<<endl;

	return 0;
}