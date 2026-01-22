#include<bits/stdc++.h>

using namespace std;

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

string S;
int f[N][N],g[N][N],n;
inline void InitF(){

}
inline void InitG(){
	for(int j=1;j<=n;j++){
		vector<int> a(n+1,0),b(n+1,0),cnt(n+1,0);
		int ld=j-1;
		a[ld+1]=0,cnt[ld+1]=1;
		for(int k=2,p=0;ld+k<=n;k++){
			while(p&&S[ld+p+1]!=S[ld+k]) p=a[ld+p];
			if(S[ld+p+1]==S[ld+k]) p++;
			a[ld+k]=p,cnt[ld+k]=cnt[ld+a[ld+k]]+1;
		}
		for(int k=1,p=0;k<=n;k++){
			while(p&&S[ld+p+1]!=S[k]) p=a[ld+p];
			if(S[ld+p+1]==S[k]) p++;
			b[k]=p;
		}
		for(int i=1;i<j;i++) g[i][j]=cnt[ld+b[i]];
	}
}

signed main(){
	cin>>S;
	n=S.size();
	S="#"+S+" ";

	InitG();
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++) cout<<g[i][j]<<' ';cout<<endl;
	}

	return 0;
}