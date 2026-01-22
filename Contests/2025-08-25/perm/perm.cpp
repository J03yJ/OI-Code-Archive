#include<bits/stdc++.h>

using namespace std;

ifstream fin("perm.in");
ofstream fout("perm.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using bint=__int128;
const int N=1e1+9;
const int L=16;

struct F{
	bint p,q;
	inline void Div(){bint g=__gcd(p,q);p/=g,q/=g;}
	F(){p=0,q=1;}
	F(bint _p){p=_p,q=1;}
	F(bint _p,bint _q){p=_p,q=_q,Div();}
	inline friend F operator +(F x,F y){return F(y.q*x.p+x.q*y.p,x.q*y.q);}
	inline friend F operator -(F x,F y){return F(y.q*x.p-x.q*y.p,x.q*y.q);}
	inline friend F operator *(F x,F y){return F(x.p*y.p,x.q*y.q);}
	inline friend F operator /(F x,F y){return F(x.p*y.q,x.q*y.p);}
	inline friend bool operator <=(F x,F y){return (long double)x.p/x.q<=(long double)y.p/y.q;}
	inline string ToString(){return to_string(ll(p))+"/"+to_string(ll(q));}
};

inline int GetT(vector<int> p){
	int n=p.size(),cnt=0;
	for(int i=0;i<n;i++) for(int j=i;j<n;j++) cnt+=(p[i]>p[j]);
	return cnt;
}

ll t[N][N*N],fac[N];
inline void CalcCount(){
	t[0][0]=1,fac[0]=1;
	for(int n=1;n<=L;n++){
		fac[n]=fac[n-1]*n;
		for(int i=0;i<=n*(n-1)/2;i++){
			for(int j=0;j<n&&j<=i;j++) t[n][i]+=t[n-1][i-j];
		}
	}
}

signed main(){
	CalcCount();

	int T;
	cin>>T;
	while(T--){
		int n,q;
		ll a,b,c;
		cin>>n>>a>>b>>c>>q;
		int lim=n*(n-1)/2;
		vector<ll> f(lim+1,0),pre(lim+1,0),suf(lim+1,0);
		vector<int> p(lim+1);
		for(int i=0;i<=lim;i++) f[i]=min(a*i,a*(lim-i)+b);
		iota(p.begin(),p.end(),0);
		sort(p.begin(),p.end(),[f](int i,int j){return f[i]<f[j];});
		for(int i=0;i<=lim;i++) pre[i]=i?pre[i-1]+t[n][p[i]]*f[p[i]]:t[n][p[i]]*f[p[i]];
		for(int i=lim;i>=0;i--) suf[i]=i!=lim?suf[i+1]+t[n][p[i]]:t[n][p[i]];
		vector<F> ans(lim+1);
		for(int i=0;i<=lim;i++){
			if(i==lim){
				for(int j=0;j<=lim;j++) ans[p[j]]=F(f[p[j]]);
			}else{
				F x(pre[i]+fac[n]*c,fac[n]-suf[i+1]);
				if(F(f[p[i]])<=x&&x<=F(f[p[i+1]])){
					for(int j=i+1;j<=lim;j++) ans[p[j]]=x;
					for(int j=0;j<=i;j++) ans[p[j]]=F(f[p[j]]);
					break ;
				}
			}
		}
		
		while(q--){
			vector<int> p(n);
			for(int &x:p) cin>>x;
			int tao=GetT(p);
			cout<<ans[tao].ToString()<<endl;
		}
	}

	return 0;
}