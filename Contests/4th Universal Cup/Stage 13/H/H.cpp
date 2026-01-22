#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

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

int fac[N],ifac[N];
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

int n,m,a,b,c,d;

signed main(){
	cin>>n>>m>>a>>b>>c>>d;
	
	Init(max(n,m));
	int A=a-1,B=m-d,C=n-b,D=c-1,ans=0;
	for(int x=0;x<=A;x++){
		for(int y=0;x+y<=A;y++){
			for(int z=0;y+z<=B;z++){
				for(int w=0;z+w<=C&&x+w<=D;w++){
					AddAs(ans,Mul(Mul(Mul(ifac[x],ifac[y]),ifac[z]),ifac[w]));
				}
			}
		}
	}
	MulAs(ans,Mul(Mul(Mul(fac[A],fac[B]),fac[C]),fac[D]));

	cout<<ans<<endl;

	return 0;
}