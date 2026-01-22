#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e5+9;
const int B=1e3+9;
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

vector<int> e[N];

int dep[N],fa[N],dfn[N],idfn[N],siz[N],n,k,lim,dcnt;
inline void GetDep(int x){
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
	siz[x]=1;
	for(int y:e[x]){
		dep[y]=dep[x]+1;
		GetDep(y);
		siz[x]+=siz[y];
	}
}

int cnt[B<<1],ans;
inline void Work(int x){
	if(fa[x]){
		for(int i=lim;i;i--) cnt[i]=cnt[i-1];
		cnt[0]=0;
		for(int i=dfn[x];i<dfn[x]+siz[x];i++){
			int y=idfn[i];
			cnt[dep[y]-dep[x]+2]--;
			cnt[dep[y]-dep[x]]++;
		}
	}
	for(int i=1;i<=lim;i++) AddAs(ans,C(cnt[i],k-1));
	int rec[B<<1];
	memcpy(rec,cnt,sizeof cnt);
	for(int y:e[x]){
		Work(y);
		memcpy(cnt,rec,sizeof cnt);
	}
}

inline void Solve(){
	cin>>n>>k;
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		e[fa[i]].push_back(i);
	}

	Init(n);
	GetDep(1);
	for(int i=1;i<=n;i++) cnt[dep[i]]++,lim=max(lim,dep[i]);
	lim<<=1;
	Work(1);
	if(k==1) ans=n;

	cout<<ans<<endl;

	for(int i=0;i<=lim;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		dep[i]=fa[i]=dfn[i]=idfn[i]=siz[i]=0;
		e[i].clear();
	}
	dcnt=ans=lim=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}