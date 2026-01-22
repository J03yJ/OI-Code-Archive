#include<bits/stdc++.h>

using namespace std;

ifstream fin("sequence.in");
ofstream fout("sequence.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int K=1e3+9;
int f[K],fs[K],g[K],gs[K],suf[K],sufs[K],n,k,mod;

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


signed main(){
	int c,T;
	cin>>c>>T;
	while(T--){
		cin>>n>>k>>mod;
		memset(f,0,sizeof f);
		memset(fs,0,sizeof fs);
		f[0]=1,fs[0]=0;
		for(int t=0;t<n;t++){
			memset(g,0,sizeof g);
			memset(gs,0,sizeof gs);
			AddAs(f[0],f[k]),AddAs(fs[0],fs[k]);
			for(int i=k-1;i>=1;i--){
				g[i]=Add(g[i+1],f[i]);
				gs[i]=Add(gs[i+1],fs[i]);
			}
			for(int i=0;i<k;i++){
				g[i+1]=(g[i+1]+1ll*(k-i)*f[i])%mod;
				gs[i+1]=(gs[i+1]+1ll*(k-i)*fs[i])%mod;
			}
			AddAs(gs[k],g[k]);
			memcpy(f,g,sizeof g);
			memcpy(fs,gs,sizeof gs);
		}
		int ans=0;
		for(int i=0;i<=k;i++) AddAs(ans,fs[i]);
		cout<<ans<<endl;
	}
	return 0;
}