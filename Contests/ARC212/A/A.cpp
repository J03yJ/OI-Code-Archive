#include<bits/stdc++.h>

using namespace std;

using ll=long long;
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

int z[4][4],g[51];
inline void DFS(int x,int sta,int cur,int &ans){
	if(cur>ans) return ;
	sta|=1<<x;
	for(int i=0;i<4;i++){
		if(i==x) continue ;
		DFS(x,sta,cur+z[x][i],ans);
	}
}

signed main(){
	int k;
	cin>>k;

	for(int n=0;n<=10;n++){
		for(int a=1;a<=n;a++){
			for(int b=1;a+b<=n;b++){
				for(int c=1;a+b+c<=n;c++){
					for(int d=1;a+b+c+d<=n;d++){
						for(int e=1;a+b+c+d+e<=n;e++){
							for(int f=1;a+b+c+d+e+f<=n;f++){
								z[0][1]=z[1][0]=a;
								z[0][2]=z[2][0]=b;
								z[0][3]=z[3][0]=c;
								z[1][2]=z[2][1]=d;
								z[1][3]=z[3][1]=e;
								z[2][3]=z[3][2]=f;
								int ans=INT_MAX;
								DFS(0,0,0,ans);
								AddAs(g[n],ans);
							}
						}
					}
				}
			}
		}
	}

	int ans=0;
	for(int i=0;i<=10;i++){
		int mul=1;
		for(int j=0;j<=10;j++){
			if(i==j) continue ;
			mul=mul*((k-j+mod)%mod)%mod;
			mul=mul*QPow((i-j+mod)%mod,mod-2)%mod;
		}
		mul=mul*g[i]%mod;
		ans=(ans+mul)%mod;
	}

	cout<<ans<<endl;

	return 0;
}