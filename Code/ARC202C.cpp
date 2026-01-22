#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const int mod=998244353;

inline void AddAs(int &x,int y,int mod){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y,int mod){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y,int mod){x=1ll*x*y%mod;}
inline int Add(int x,int y,int mod){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y,int mod){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y,int mod){return 1ll*x*y%mod;}
inline int QPow(int x,int y,int mod){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x,mod);
		MulAs(x,x,mod);
		y>>=1;
	}
	return res;
}
inline int Inv(int x,int mod){return QPow(x,mod-2,mod);}

vector<int> rd[N],d[N],p[N];
int ntp[N],pri[N],r[N],pcnt;
inline void Init(int lim){
	ntp[1]=1;
	for(int i=2;i<=lim;i++){
		if(!ntp[i]) pri[++pcnt]=i;
		for(int j=1;pri[j]*i<=lim&&j<=pcnt;j++){
			ntp[pri[j]*i]=1;
			if(i%pri[j]==0) break ;
		}
	}
	for(int i=1;i<=lim;i++){
		for(int j=i;j<=lim;j+=i) d[j].push_back(i);
		if(!ntp[i]) for(int j=i;j<=lim;j+=i) p[j].push_back(i);
	}
	for(int i=1;i<=lim;i++) rd[i]=d[i],reverse(rd[i].begin(),rd[i].end());
	for(int i=1;i<=lim;i++) r[i]=Add(Mul(r[i-1],10,mod),1,mod);
}

int f[N],s[N],tmp[N],a[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	int cur=1;
	Init(2e5);
	for(int i=1;i<=n;i++){
		for(int k:d[a[i]]) tmp[k]=Sub(0,s[k],mod-1);
		for(int x:p[a[i]]){
			for(int k:d[a[i]]){
				if(a[i]%(x*k)==0) SubAs(tmp[k],tmp[x*k],mod-1);
			}
		}
		AddAs(tmp[a[i]],1,mod-1);
		for(int k:d[a[i]]){
			MulAs(cur,QPow(r[k],tmp[k],mod),mod);
			AddAs(f[k],tmp[k],mod-1);
		}
		for(int x:p[a[i]]){
			for(int k:rd[a[i]]){
				if(a[i]%(x*k)==0) AddAs(tmp[k],tmp[x*k],mod-1);
			}
		}
		for(int k:d[a[i]]){
			AddAs(s[k],tmp[k],mod-1);
			tmp[k]=0;
		}
		cout<<cur<<endl;
	}

	return 0;
}