#include<bits/stdc++.h>

using namespace std;

ifstream fin("explore.in");
ofstream fout("explore.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int V=1e6+9;
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

vector<int> d[V];
int ntp[V],mu[V],pri[V],pcnt;
inline void Init(int lim){
	ntp[1]=1;
	for(int i=2;i<=lim;i++){
		if(!ntp[i]) pri[++pcnt]=i,mu[i]=mod-1;
		for(int j=1;j<=pcnt&&i*pri[j]<=lim;j++){
			ntp[i*pri[j]]=1;
			if(i%pri[j]) mu[i*pri[j]]=mod-mu[i];
			else{
				mu[i*pri[j]]=0;
				break ;
			}
		}
	}
	for(int i=1;i<=lim;i++){
		for(int j=i;j<=lim;j+=i) d[j].push_back(i);
	}
}

int a[N],f[N],s[V],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	Init(1e6);

	f[1]=1;
	for(int i=1;i<=n;i++){
		for(int x:d[a[i]]) AddAs(f[i],Mul(Sub(0,mu[x]),s[x]));
		for(int x:d[a[i]]) AddAs(s[x],f[i]);
	}
	
	cout<<f[n]<<endl;
	
	return 0;
}