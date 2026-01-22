#include<bits/stdc++.h>

using namespace std;

ifstream fin("war.in");
ofstream fout("war.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=3e2+9;
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

int p[N],a[N],co[N][N],lim[N],f[N][N],n,k;
inline void GetSumCoef(int *co,int k){
	vector<int> val(k+1,0),_inv(k<<1|1,0);
	auto inv=_inv.begin()+k;
	for(int x=0;x<=k;x++) val[x]=Add(x?val[x-1]:0,QPow(x,k-1));
	for(int i=-k;i<=k;i++) inv[i]=Inv(Add(i,mod));
	
	vector<int> f(k+2,0);
	auto M=[k,&f](int x){
		for(int i=k+1;i>=0;i--){
			MulAs(f[i],Sub(0,x));
			if(i) AddAs(f[i],f[i-1]);
		}
	};
	auto D=[k,inv,&f](int x){
		for(int i=k+1;i>=0;i--) if(i<k+1) SubAs(f[i],Mul(Sub(0,x),f[i+1]));
		for(int i=0;i<=k+1;i++) f[i]=i==k+1?0:f[i+1];
	};
	f[0]=1;
	for(int x=0;x<=k;x++) M(x);
	for(int x=0;x<=k;x++){
		D(x);
		int c=val[x];
		for(int i=0;i<=k;i++) if(i!=x) MulAs(c,inv[x-i]);
		for(int i=0;i<=k;i++) AddAs(co[i],Mul(c,f[i]));
		M(x);
	}
}

signed main(){
	cin>>n;
	for(int i=2;i<=n;i++) cin>>p[i];
	cin>>k;
	for(int i=1;i<=n;i++) cin>>a[i];

	Init(n);
	for(int i=0;i<=n;i++) GetSumCoef(co[i],i+1);
	
	for(int i=2;i<=n;i++) lim[i]=lim[p[i]]+1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=lim[i]+1;j++) f[i][j]=QPow(a[i],j);
	}
	for(int i=n;i>=2;i--){
		vector<int> tmp(f[i],f[i]+lim[i]+2);
		f[i][lim[i]+1]=0;
		for(int j=0;j<=lim[i];j++){
			f[i][j]=0;
			for(int k=0;k<=j+1;k++){
				AddAs(f[i][j],Mul(tmp[k],co[j][k]));
			}
		}
		tmp=vector<int>(f[p[i]],f[p[i]]+lim[i]+1);
		for(int j=0;j<=lim[i];j++){
			f[p[i]][j]=0;
			MulAs(f[i][j],QPow(k,j));
			for(int k=0;k<=j;k++){
				AddAs(f[p[i]][j],Mul(C(j,k),Mul(f[i][k],tmp[j-k])));
			}
		}
	}

	cout<<f[1][0]<<endl;

	return 0;
}