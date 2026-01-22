#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
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
inline int Inv(int x){return QPow(x,mod-2);}

inline int B(int n,int m){
	if(m>n||m<0) return 0;
	int fac=1,res=1;
	for(int i=1;i<=m;i++) MulAs(fac,i);
	for(int i=1;i<=m;i++) MulAs(res,n-i+1);
	return Mul(res,Inv(fac));
}

void prec(int subtask_id){}
int solve(int n,int k){
	int ans=0;
	AddAs(ans,B(2*(n-1),k-2));
	AddAs(ans,Mul(2,B(2*(n-1),k-1)));
	AddAs(ans,Mul(3,Mul(n-1,B(2*(n-2),k-2))));
	AddAs(ans,Mul(2,Mul(n-1,B(2*(n-2),k-1))));
	return Mul(ans,Inv(B(2*n,k)));
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int Tid,T;
	cin>>Tid>>T;
	prec(T);
	while(T--){
		int n,k;
		cin>>n>>k;
		cout<<solve(n,k)<<endl;
	}

	return 0;
}