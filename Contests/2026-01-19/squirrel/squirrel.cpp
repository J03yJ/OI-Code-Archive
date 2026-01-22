#include<bits/stdc++.h>

using namespace std;

ifstream fin("squirrel.in");
ofstream fout("squirrel.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;
const int N=1e6+9;
const int lgK=64;
const int A=1e2+9;

struct FastMod{
    ull b,m;
    FastMod()=default;
    FastMod(ull m):b(((unsigned __int128)1<<64)/m),m(m){}
    ull operator()(ull a){
        ull q=(unsigned __int128)a*b>>64;
        ull r=a-q*m;
        return r>=m?r-m:r;
    }
}fastmod;
int mod;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
// inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline void MulAs(int &x,int y){x=fastmod(1ll*x*y);}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
// inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Mul(int x,int y){return fastmod(1ll*x*y);}
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

int fac[N<<1],ifac[N<<1],inv[N];
inline int fInv(int x){return Mul(ifac[x],fac[x-1]);}
inline void Init(int lim){
	fastmod=FastMod(mod);
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
	for(int i=1;i<=lim;i++) inv[i]=fInv(i);
}
inline int C(int n,int m){return n<mod?Mul(fac[n],Mul(ifac[m],ifac[n-m])):0;}

int f[lgK][A],tar[lgK],ni[lgK],mi[lgK],tx[N],ty[N];
ll n,m,k,a,b,c0,c1,c2,c3;
inline void Solve(){
	cin>>n>>m>>k>>a>>b>>mod>>c0>>c1>>c2>>c3;

	n--,m--;
	ll tmp=max(k,max(n,m));
	int lgk=0;
	while(tmp) tmp/=mod,lgk++;
	for(int i=0;i<lgk;i++){
		tar[i]=k%mod,k/=mod;
		ni[i]=n%mod,n/=mod;
		mi[i]=m%mod,m/=mod;
	}

	int ans=0;
	Init(mod-1);
	f[lgk][0]=1;
	for(int i=lgk-1;~i;i--){
		for(int j=0;j<=a+b;j++){
			if(!i&&j) break ;
			ll s=j;
			int d=Sub(tar[i],j);
			for(int x=0;x<mod;x++,SubAs(d,a),s+=a){
				int y=Mul(d,inv[b]),_j=(s+b*y)/mod;
				if(!f[i+1][_j]) continue ;
				int w=Mul(f[i+1][_j],Mul(C(ni[i]+x,x),C(mi[i]+y,y)));
				AddAs(f[i][j],w);
				if(!i) AddAs(ans,Mul(w,Add(Add(c0,Mul(x,c1)),Add(Mul(y,c2),Mul(Mul(x,y),c3)))));
			}
		}
	}
	for(int i=0;i<=lgk;i++) for(int j=0;j<=a+b;j++) f[i][j]=0;


	cout<<ans<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}