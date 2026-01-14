#include<bits/stdc++.h>

using namespace std;

ifstream fin("reverse.in");
ofstream fout("reverse.out");
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
inline int Inv(int x){return QPow(x,mod-2);}

int typ;
ll n,k;

namespace A{
	#define popc __builtin_popcount
	int f[(1<<23)+9];
	inline void Solve(){
		string str;
		cin>>str;

		int s=0;
		for(int i=0;i<n;i++) s|=str[i]-'0'<<i;
		
		if(popc(s)<k){
			cout<<0<<endl;
			return ;
		} 

		f[s]=1;
		int ans=0;
		for(int sta=(1<<n)-1;~sta;sta--){
			if(!f[sta]) continue ;
			for(int i=0;i<n;i++){
				if(~sta>>i&1) continue ;
				for(int j=i;j<n;j++){
					if((sta>>j&1)^(j-i+1&1)) break ;
					if(sta>>j&1){
						int msk=((1<<j+1)-1>>i)<<i;
						AddAs(f[sta^msk],f[sta]);
					}
				}
			}
			if(popc(sta)+k==popc(s)) AddAs(ans,f[sta]);
		}

		cout<<ans<<endl;
	}
}
namespace B{
	inline void Solve(){
		n++;
		int ans=1;
		for(int i=n-k+1;i<=n+k;i++) MulAs(ans,i);
		for(int i=1;i<=k;i++) MulAs(ans,mod+1>>1);
		for(int i=1;i<=k;i++) MulAs(ans,Inv(i));
		cout<<ans<<endl;
	}
}
namespace C{
	const int B=10000000;
	int f[100]={1,602870105,973057368,785631611,272938552,663613190,201683836,640052352,405904067,221325174,598048000,621781911,234259666,154800848,448810879,281056452,59923617,742170701,747754636,534436782,229675900,119792223,466018540,935843236,67753993,351468303,265944861,332166658,626895088,966658272,165767177,983003272,632144796,942254222,270052522,513317092,233677970,493956304,522185256,882171809,847523741,723672329,856665103,63847217,991424449,9129324,248535523,43940659,995908414,176831428};
	inline void Solve(){
		if(2*n+1>=mod){
			cout<<0<<endl;
			return ;
		}
		int ans=f[n/B];
		for(int i=n/B*B+1;i<=n;i++) MulAs(ans,2*i+1);
		cout<<ans<<endl;
	}
}

signed main(){
	cin>>typ>>n>>k;
	
	if(typ==1) A::Solve();
	else if(k<=n) B::Solve();
	else C::Solve();

	return 0;
}