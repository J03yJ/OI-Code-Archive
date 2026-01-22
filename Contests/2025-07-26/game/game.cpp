#include<bits/stdc++.h>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
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

int a[N],h[8],f[N][16],n;
#define Val(x,y,z) h[(x)<<2|(y)<<1|(z)]
#define To(x,y) (1<<((x)<<1|(y)))

signed main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		for(int i=0;i<8;i++){
			char c;
			cin>>c;
			h[i]=c-'0';
		}
		cin>>s;
		n=s.size();
		for(int i=1;i<=n;i++) a[i]=s[i-1]=='?'?-1:s[i-1]-'0';

		memset(f,0,sizeof f);
		for(int p:{0,1}){
			if(!(a[1]^p^1)) continue ;
			for(int q:{0,1}){
				if(!(a[2]^q^1)) continue ;
				int tta=0;
				for(int r:{0,1}){
					tta|=To(r,Val(r,q,p));
				}
				AddAs(f[1][tta],1);
			}
		}

		for(int i=3;i<n;i+=2){
			for(int sta=0;sta<16;sta++){
				for(int p:{0,1}){
					if(!(a[i]^p^1)) continue ;
					for(int q:{0,1}){
						if(!(a[i+1]^q^1)) continue ;
						int tta=0;
						for(int r:{0,1}){
							for(int s:{0,1}){
								if(sta&To(p,s)){
									tta|=To(r,Val(r,q,s));
								}
								if(sta&To(Val(r,q,p),s)){
									tta|=To(r,s);
								}
							}
						}
						AddAs(f[i][tta],f[i-2][sta]);
					}
				}
			}
		}
		
		int ans=0,sta=0;
		for(int p:{0,1}){
			if(!(a[n]^p^1)) continue ;
			for(int i=0;i<16;i++) if(i&To(p,1)) AddAs(ans,f[n-2][i]);
		}

		cout<<ans<<endl;
	}

	return 0;
}