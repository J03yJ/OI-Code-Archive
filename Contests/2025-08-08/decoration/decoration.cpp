#include<bits/stdc++.h>

using namespace std;

ifstream fin("decoration.in");
ofstream fout("decoration.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
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

int fac[N<<1],ifac[N<<1];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

int n,r,g,b;

signed main(){
	cin>>n>>r>>g>>b;

	int x=r+g-b>>1,y=g+b-r>>1,z=b+r-g>>1;
	if(x<0||y<0||z<0){
		cout<<0<<endl;
		return 0;
	}

	Init(n);
	int ans=0;
	for(int k:{0,1,2}){
		for(int lim:{x-1,x}){
			for(int c=0;c<=lim;c++){
				if((c&1)!=(y+z&1)) continue ;
				int p=c+y-z>>1;
				int q=c+z-y>>1;
				int lft=y-p-(lim-c);
				int res=QPow(2,lim-c);
				MulAs(res,C(lim,c));
				MulAs(res,C(c,p));
				MulAs(res,C(lim+lft-1,lft));
				AddAs(ans,res);
			}
		}
		swap(x,y);
		swap(y,z);
	}
	MulAs(ans,2);

	cout<<ans<<endl;

	return 0;
}