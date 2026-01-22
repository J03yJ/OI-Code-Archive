#include<bits/stdc++.h>

using namespace std;

ifstream fin("chain.in");
ofstream fout("chain.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=3e3+9;
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
inline int IC(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(ifac[n],Mul(fac[m],fac[n-m]));
}

int e[N][N],p[N][N],cnt[N],n;
char c[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];

	for(int i=1;i<=n;i++) cnt[i]=cnt[i-1]+(c[i]=='0');
	int m=cnt[n],inv=Inv(m),cst=Mul(m+1,inv);

	Init(n);
	e[0][0]=0,p[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=cnt[n]-cnt[i-1];j++){
			if(c[i]=='0'){
				int t=cnt[n]-cnt[i-1]-j,q=Mul(C(t+j-1,j),IC(t+j,j));
				AddAs(e[i][j],Mul(e[i-1][j],q));
				AddAs(p[i][j],Mul(p[i-1][j],q));
				if(j){
					int qq=Mul(Sub(1,q),Mul(t,inv));
					AddAs(e[i][j],Mul(Add(e[i-1][j],Mul(p[i-1][j],cst)),qq));
					AddAs(p[i][j],Mul(p[i-1][j],qq));
					AddAs(e[i][j-1],Mul(Add(e[i-1][j],Mul(p[i-1][j],cst)),Sub(Sub(1,q),qq)));
					AddAs(p[i][j-1],Mul(p[i-1][j],Sub(Sub(1,q),qq)));
				}
			}else{
				int t=cnt[n]-cnt[i-1]-j,q=Mul(t,inv);
				AddAs(e[i][j+1],Mul(Add(e[i-1][j],Mul(p[i-1][j],cst)),q));
				AddAs(p[i][j+1],Mul(p[i-1][j],q));
				AddAs(e[i][j],Mul(Add(e[i-1][j],Mul(p[i-1][j],cst)),Sub(1,q)));
				AddAs(p[i][j],Mul(p[i-1][j],Sub(1,q)));
			}
		}
	}

	cout<<e[n][0]<<endl;

	return 0;
}