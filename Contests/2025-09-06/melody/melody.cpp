#include<bits/stdc++.h>

using namespace std;

ifstream fin("melody.in");
ofstream fout("melody.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e6+9;
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

int a[N],pmul[N],f[N],sum[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	pmul[0]=1;
	for(int i=1;i<=n;i++) pmul[i]=Mul(pmul[i-1],a[i]);

	if(*max_element(a+1,a+n+1)!=*min_element(a+1,a+n+1)){
		for(int i=1;i<=n;i++){
			f[i]=pmul[i];
			for(int j=1;(j<<1)<=i;j++){
				SubAs(f[i],Mul(f[j],Mul(pmul[i-j],Inv(pmul[j]))));
			}
		}
		cout<<f[n]<<endl;
	}else{
		for(int i=1;i<=n;i++){
			f[i]=Sub(pmul[i],Mul(pmul[i],sum[i>>1]));
			sum[i]=Add(sum[i-1],Mul(f[i],Inv(Mul(pmul[i],pmul[i]))));
		}
		cout<<f[n]<<endl;
	}

	return 0;
}