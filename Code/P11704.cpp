#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
const int K=2e3+9;
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

int fac[N<<1],ifac[N<<1];
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

int f[K][K],n,m,k;
array<int,2> p[K];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) cin>>p[i][0]>>p[i][1];
	Init(n+m);
	
	p[++k]={1,2};
	p[++k]={2,1};
	p[++k]={n,m-1};
	p[++k]={n-1,m};
	sort(p+1,p+k+1);
	k=unique(p+1,p+k+1)-p-1;
	map<array<int,2>,int> id;
	for(int i=1;i<=k;i++) id[p[i]]=i;
	
	f[id[{2,1}]][id[{2,1}]-1]=1;
	auto W=[](int i,int j){return C(p[j][0]-p[i][0]+p[j][1]-p[i][1],p[j][0]-p[i][0]);};
	for(int t=1;t<=k;t++){
		for(int i=1;i<t;i++){
			AddAs(f[t+1][i],Mul(W(t,t+1),f[t][i]));
			AddAs(f[t][t+1],Mul(W(i,t+1),f[t][i]));
			AddAs(f[i][t+1],Mul(W(t,t+1),f[i][t]));
			AddAs(f[t+1][t],Mul(W(i,t+1),f[i][t]));
		}
	}

	cout<<Mul(2,Sub(f[id[{n,m-1}]][id[{n-1,m}]],f[id[{n-1,m}]][id[{n,m-1}]]))<<endl;

	return 0;
}