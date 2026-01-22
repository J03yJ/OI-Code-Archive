#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int mod=998244353;

namespace jiangly{
	constexpr int P = 998244353;

	int power(int a, int b) {
		int res = 1;
		for (; b; b /= 2, a = 1LL * a * a % P) {
			if (b % 2) {
				res = 1LL * res * a % P;
			}
		}
		return res;
	}

	std::vector<int> rev, roots {0, 1};

	void dft(std::vector<int> &a) {
		int n = a.size();
		if (int(rev.size()) != n) {
			int k = __builtin_ctz(n) - 1;
			rev.resize(n);
			for (int i = 0; i < n; i++) {
				rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
			}
		}
		for (int i = 0; i < n; i++) {
			if (rev[i] < i) {
				std::swap(a[i], a[rev[i]]);
			}
		}
		if (roots.size() < n) {
			int k = __builtin_ctz(roots.size());
			roots.resize(n);
			while ((1 << k) < n) {
				int e = power(31, 1 << (__builtin_ctz(P - 1) - k - 1));
				for (int i = 1 << (k - 1); i < (1 << k); i++) {
					roots[2 * i] = roots[i];
					roots[2 * i + 1] = 1LL * roots[i] * e % P;
				}
				k++;
			}
		}

		for (int k = 1; k < n; k *= 2) {
			for (int i = 0; i < n; i += 2 * k) {
				for (int j = 0; j < k; j++) {
					int u = a[i + j];
					int v = 1LL * a[i + j + k] * roots[k + j] % P;
					a[i + j] = (u + v) % P;
					a[i + j + k] = (u - v + P) % P;
				}
			}
		}
	}

	void idft(std::vector<int> &a) {
		int n = a.size();
		std::reverse(a.begin() + 1, a.end());
		dft(a);
		int inv = (1 - P) / n;
		for (int i = 0; i < n; i++) {
			a[i] = 1LL * a[i] * inv % P;
		}
	}

	std::vector<int> mul(std::vector<int> a, std::vector<int> b) {
		int n = 1, tot = a.size() + b.size() - 1;
		while (n < tot) {
			n *= 2;
		}
		if (tot < 1024) {
			std::vector<int> c(a.size() + b.size() - 1);
			for (int i = 0; i < a.size(); i++) {
				for (int j = 0; j < b.size(); j++) {
					c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % P;
				}
			}
			return c;
		}
		a.resize(n);
		b.resize(n);
		dft(a);
		dft(b);
		for (int i = 0; i < n; i++) {
			a[i] = 1LL * a[i] * b[i] % P;
		}
		idft(a);
		a.resize(tot);
		return a;
	}
}

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

const int gmod=3;
const int invg=Inv(gmod);
using Poly=vector<int>;

inline void NTT(Poly &f,Poly &r,int lim,int flag){
    for(int i=0;i<lim;i++) if(i<r[i]) swap(f[i],f[r[i]]);
    for(int k=1;k<lim;k<<=1){
        int len=k<<1,gn=QPow(flag>0?gmod:invg,(mod-1)/len);
        for(int i=0;i<lim;i+=len){
            for(int j=0,g=1;j<k;j++,MulAs(g,gn)){
                int tmp=Mul(f[i+j+k],g);
                f[i+j+k]=Sub(f[i+j],tmp);
                f[i+j]=Add(f[i+j],tmp);
            }
        }
    }
    if(!~flag){
        int inv=Inv(lim);
        for(int &x:f) MulAs(x,inv);
    }
}
inline Poly Conv(Poly f,Poly g){
    int len=f.size()+g.size()-1,lim=1;
    while(lim<len) lim<<=1;
    f.resize(lim,0),g.resize(lim,0);

    Poly rev(lim,0),h(lim,0);
    for(int i=0;i<lim;i++){
        rev[i]=rev[i>>1]>>1;
        if(i&1) rev[i]|=lim>>1;
    }
    NTT(f,rev,lim,1),NTT(g,rev,lim,1);
    for(int i=0;i<lim;i++) h[i]=Mul(f[i],g[i]);
    NTT(h,rev,lim,-1);

    h.resize(len,0);
    return h;
}

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

const int inv2=Inv(2);
int c[N],ans[N],n;
vector<int> e[N];

int siz[N],vis[N];
inline void GetGrv(int x,int fa,int tot,int &grv){
	bool flag=0;
	siz[x]=1;
	for(int y:e[x]){
		if(vis[y]) continue ;
		if(y==fa) continue ;
		GetGrv(y,x,tot,grv);
		siz[x]+=siz[y];
		if(siz[y]>tot/2) flag=1;
	}
	if(tot-siz[x]>tot/2) flag=1;
	if(!flag) grv=x;
}
inline void GetNode(int x,int fa,vector<int> &v){
	v.push_back(x);
	for(int y:e[x]){
		if(vis[y]) continue ;
		if(y==fa) continue ;
		GetNode(y,x,v);
	}
}
int dep[N];
inline void GetDep(int x,int fa){
	if(!~fa) dep[x]=0;
	for(int y:e[x]){
		if(vis[y]) continue ;
		if(y==fa) continue ;
		dep[y]=dep[x]+1;
		GetDep(y,x);
	}
}
inline void Solve(int x,int tot,int fa,int ftot){
	GetGrv(x,-1,tot,x);
	GetGrv(x,-1,tot,x);
	vis[x]=1;
	
	vector<int> node;
	GetNode(x,-1,node);
	if(~fa){
		int tmp=0;
		for(int u:node) tmp=max(tmp,dep[u]);
		tmp<<=1;
		vector<int> f(tmp+5,0);
		for(int u:node) f[dep[u]]++;
		f=jiangly::mul(f,f);
		for(int u:node) f[dep[u]*2]--;
		for(int i=0;i<=tmp;i++) MulAs(f[i],inv2);
		for(int i=0;i<=tmp;i++) SubAs(c[i+1],f[i]);
	}
	GetDep(x,-1);
	int tmp=0;
	for(int u:node) tmp=max(tmp,dep[u]);
	tmp<<=1;
	vector<int> g(tmp+5,0);
	for(int u:node) g[dep[u]]++;
	g=jiangly::mul(g,g);
	for(int u:node) g[dep[u]*2]--;
	for(int i=0;i<=tmp;i++) MulAs(g[i],inv2);
	for(int i=0;i<=tmp;i++) AddAs(c[i+1],g[i]);

	for(int y:e[x]){
		if(vis[y]) continue ;
		Solve(y,siz[y],x,tot);
	}
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	Init(n);
	Solve(1,n,-1,n);
	for(int i=1;i<=n;i++) cout<<c[i]<<' ';cout<<endl;

	vector<int> f(n+1,0),g(n+1,0);
	for(int i=0;i<=n;i++){
		f[i]=ifac[i];
		g[i]=Mul(fac[n-i],c[i]);
	}
	vector<int> h=jiangly::mul(f,g);
	for(int i=1;i<=n-2;i++) ans[i]=Mul(Mul(fac[i],ifac[n-i-2]),h[i+2]);

	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}