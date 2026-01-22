#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
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

int a[N],siz[N],f[N],lc[N],rc[N],lf[N],rf[N],n,root;
inline void DFS(int x){
	if(!x) return ;
	DFS(lc[x]),DFS(rc[x]);
	siz[x]=1+siz[lc[x]]+siz[rc[x]];
	if(!lf[x]&&!rf[x]){
		f[x]=Mul(Mul(f[lc[x]],f[rc[x]]),C(siz[x]-1,siz[lc[x]]));
	}else if(lf[x]&&!rf[x]){
		f[x]=Mul(Mul(f[lc[x]],f[rc[x]]),C(siz[x],siz[lc[x]]+1));
	}else if(!lf[x]&&rf[x]){
		f[x]=Mul(Mul(f[lc[x]],f[rc[x]]),C(siz[x],siz[rc[x]]+1));
	}else{
		AddAs(f[x],Mul(Mul(f[lc[x]],f[rc[x]]),C(siz[x],siz[lc[x]]+1)));
		AddAs(f[x],Mul(Mul(f[lc[x]],f[rc[x]]),C(siz[x],siz[rc[x]]+1)));
		SubAs(f[x],Mul(Mul(f[lc[x]],f[rc[x]]),C(siz[x]-1,siz[lc[x]])));
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	Init(n);
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int lst=0;
		while(stk.size()&&a[stk.back()]<=a[i]){
			rf[stk.back()]=i;
			lst=stk.back();
			stk.pop_back();
		}
		if(lst) lc[i]=lst;
		stk.push_back(i);
	}
	stk.clear();
	for(int i=n;i>=1;i--){
		int lst=0;
		while(stk.size()&&a[stk.back()]<=a[i]){
			lf[stk.back()]=i;
			lst=stk.back();
			stk.pop_back();
		}
		if(lst) rc[i]=lst;
		stk.push_back(i);
	}
	root=stk.front();
	siz[0]=0,f[0]=1;
	DFS(root);

	cout<<f[root]<<endl;

	return 0;
}