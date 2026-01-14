#include<bits/stdc++.h>

using namespace std;

ifstream fin("inflict.in");
ofstream fout("inflict.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e3+9;
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

int a[N],b[N],l[N],r[N],n,q;

int f[N][N];
inline int Work(int k){
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int p=max(0,i-(n-k));p<=min(i,k);p++){
			f[i][p]=0;
			int q=i-p;
			if(p&&a[i]>b[p]) AddAs(f[i][p],f[i-1][p-1]);
			if(q&&a[i]<b[q+k]) AddAs(f[i][p],f[i-1][p]);
		}
	}
	return f[n][k];
}

namespace LEqR{
	inline bool Check(){return q==1&&l[1]==r[1];}
	inline void Solve(){cout<<Work(l[1])<<endl;}
}
namespace ALtB{
	inline bool Check(){return a[n]<b[1];}
	inline void Solve(){
		for(int i=1;i<=q;i++) cout<<(l[i]==0)<<endl;
	}
}
namespace OddEven{
	int ans[N];
	inline bool Check(){
		for(int i=1;i<=n;i++) if(a[i]!=2*i-1) return 0;
		for(int i=1;i<=n;i++) if(b[i]!=2*i) return 0;
		return 1;
	}
	inline void Solve(){
		Init(n);
		for(int k=0;k<=n;k++) ans[k]=C(n-1,k);
		for(int i=1;i<=n;i++) AddAs(ans[i],ans[i-1]);
		for(int i=1;i<=q;i++){
			cout<<(l[i]?Sub(ans[r[i]],ans[l[i]-1]):ans[r[i]])<<endl;
		}
	}
}
namespace Brute{
	int ans[N];
	inline void Solve(){
		for(int k=0;k<=n;k++) ans[k]=Work(k);
		for(int i=1;i<=n;i++) AddAs(ans[i],ans[i-1]);
		for(int i=1;i<=q;i++){
			cout<<(l[i]?Sub(ans[r[i]],ans[l[i]-1]):ans[r[i]])<<endl;
		}
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>l[i]>>r[i];

	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	
	if(LEqR::Check()) LEqR::Solve();
	else if(ALtB::Check()) ALtB::Solve();
	else if(OddEven::Check()) OddEven::Solve();
	else Brute::Solve();

	return 0;
}