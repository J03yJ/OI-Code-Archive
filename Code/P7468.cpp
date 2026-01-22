#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e5+9;
const int K=5e2+9;
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

int fac[K],ifac[K];
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

int k;
string n;

using Poly=vector<int>;
inline Poly Shift(Poly a,int k){
	Poly b(a.size(),0);
	for(int i=0;i<a.size();i++){
		for(int j=i,t=1;j>=0;j--,MulAs(t,k)){
			AddAs(b[j],Mul(a[i],k));
		}
	}
	return b;
}
inline int Val(Poly f,int x){
	int res=0;
	for(int i=0,y=1;i<f.size();i++,MulAs(y,x)) AddAs(res,Mul(f[i],y));
	return res;
}
inline Poly Add(Poly f,Poly g){
	Poly h(max(f.size(),g.size()),0);
	for(int i=0;i<max(f.size(),g.size());i++) h[i]=f[i]+g[i];
	return h;
}
inline Poly Mul(Poly f,Poly g){
	Poly h(f.size()+g.size()-1);
	for(int i=0;i<f.size();i++){
		for(int j=0;j<g.size();j++) AddAs(h[i+j],Mul(f[i],g[i]));
	}
	return h;
}
inline Poly Mul(Poly f,int k){
	for(int &x:f) MulAs(x,k);
	return f;
}
inline Poly ConInterp(vector<int> y){
	Poly ans(y.size()-1,0);
	vector<int> inv(y.size()<<1|1,0);
	for(int i=0;i<inv.size();i++) inv[i]=Inv(Sub(i,y.size()));
	for(int i=0;i<y.size();i++){
		Poly tmp({y[i]});
		for(int j=0;j<y.size();j++){
			if(i==j) continue ;
			tmp=Mul(Mul(tmp,{Sub(0,y[j]),1}),inv[i-j+y.size()]);
		}
		ans=Add(ans,tmp);
	}
	return ans;
}
Poly F[K],G[K];
inline int ToValue(string s){
	int res=0;
	for(int i=0;i<s.size();i++) res=Add(Add(res,res),s[i]-'0');
	return res;
}
inline int PopCount(string s){
	int res=0;
	for(char c:s) res+=c-'0';
	return res;
}

signed main(){
	cin>>n>>k;
	Poly a(k,0);
	for(int &x:a) cin>>x;

	Init(k+1);
	F[0]=a;
	G[0]=Poly(k,0);
	for(int i=1;i<=k;i++){
		F[i]=Add(F[i-1],Shift(G[i-1],QPow(2,i-1)));
		G[i]=Add(G[i-1],Shift(F[i-1],QPow(2,i-1)));
	}

	vector<int> sum(k+2,0);
	for(int i=1;i<=k+1;i++) sum[i]=Add(sum[i-1],Val(a,i));
	Poly H=ConInterp(sum);

	reverse(n.begin(),n.end());
	int cnt=PopCount(n),cur=ToValue(n),ans=0;
	for(int i=0;i<=min(k,(signed)n.size()-1);i++){

		if(n[i]=='1') SubAs(cur,QPow(2,i)),cnt--;
	}

	return 0;
}