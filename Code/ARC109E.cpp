#include<bits/stdc++.h>

using namespace std;

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
#define Inv(x) QPow(x,mod-2)

int n;

signed main(){
	cin>>n;

	vector<int> pre(n+1,0);
	for(int i=2;i<=(n-1)/2;i++) pre[i]=Mul(2*i-1,QPow(2,2*i-3)),AddAs(pre[i],pre[i-1]);
	for(int s=1;s<=n;s++){
		int sum=Mul(n,QPow(2,n-1));
		AddAs(sum,pre[min(s-1,n-s)]);
		cout<<Mul(sum,Inv(QPow(2,n)))<<endl;
	}

	return 0;
}