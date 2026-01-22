#include<bits/stdc++.h>

using namespace std;

ifstream fin("song.in");
ofstream fout("song.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;

ll n,k;
struct FastMod { // 请将该结构体直接复制，粘贴到你的代码中
    unsigned long long b, m;
    FastMod() = default;
    FastMod(unsigned long long m) : b(((unsigned __int128)1 << 64) / m), m(m) {}
    unsigned long long operator()(unsigned long long a) {
        unsigned long long q = (unsigned __int128)a * b >> 64;
        unsigned long long r = a - q * m;
        return r >= m ? r - m : r;
    }
} fastmod;
int mod;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=fastmod(1ll*x*y);}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
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

const int K=1e3+9;
int fac[K],ifac[K];
inline void Init(int lim){
	fastmod=FastMod(mod);
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}
inline int iC(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(ifac[n],Mul(fac[m],fac[n-m]));
}

int f[2][K],pf[K][2],ipf[K][2];

inline void Solve(){
	cin>>n>>k>>mod;

	Init(k);
	if(n<=k){
		int ans=Mul(C(k,n),fac[n]);
		for(int i=1;i<k;i++){
			AddAs(ans,Mul(Mul(Mul(C(k,i),fac[i]),i),Mul(C(k-1,n-1-i),fac[n-1-i])));
		}
		cout<<ans<<endl;
	}else{
		int ans=0;
		for(int i=0;i<=k;i++){
			pf[i][0]=ipf[i][0]=1;
			for(int j=1;j<=k;j++){
				pf[i][j]=Mul(pf[i][j-1],fac[i]);
				ipf[i][j]=Mul(ipf[i][j-1],ifac[i]);
			}
		}
		for(int i=1;i<=k;i++){
			int t=(n-i)/k%(mod-1),r=(n-i)%k;
			for(int j=0;j<=k;j++){
				for(int c:{0,1}){
					pf[j][c]=QPow(fac[j],t+c);
					ipf[j][c]=Inv(pf[j][c]);
				}
			}
			auto F=[&](int i,int j){
				if(i<r&&r<=j) return Mul(Mul(C(k-i,k-j),pf[j-i][0]),Mul(C(j-i,r-i),fac[r-i]));
				else return Mul(C(k-i,k-j),pf[j-i][j<r]);
			};
			auto G=[&](int p){
				return Mul(pf[k-p][0],Mul(C(k-p,max(r-p,0)),fac[max(r-p,0)]));
			};
			auto iG=[&](int p){
				return Mul(ipf[k-p][0],Mul(iC(k-p,max(r-p,0)),ifac[max(r-p,0)]));
			};
			f[1][0]=G(0);
			for(int j=0;i+j<=k;j++){
				for(int p=j+1;i+p<=k;p++){
					for(int c:{0,1}){
						AddAs(f[!c][p],Mul(f[c][j],Mul(F(j,p),Mul(iG(j),G(p)))));
					}
				}
			}
			for(int j=0;j<=k;j++){
				AddAs(ans,Mul(Mul(C(k-j,i),fac[i]),Sub(f[1][j],f[0][j])));
				f[0][j]=f[1][j]=0;
			}
		}
		cout<<ans<<endl;
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}