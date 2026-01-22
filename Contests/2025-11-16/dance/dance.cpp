#include<bits/stdc++.h>

using namespace std;

ifstream fin("dance.in");
ofstream fout("dance.out");
#define cin fin
#define cout fout
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
#define Inv(x) QPow(x,mod-2)

const int N=1e6+9;

int f[N],n,k;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		
		int inv=Inv(k),ans=0;
		for(int i=1;i<=k;i++) f[i]=QPow(Mul(k/i,inv),n);
		for(int i=k;i>=1;i--){
			for(int j=2;j*i<=k;j++) SubAs(f[i],f[j*i]);
			AddAs(ans,Mul(i,f[i]));
		}

		cout<<ans<<endl;

		for(int i=1;i<=k;i++) f[i]=0;
	}

	return 0;
}