#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e3+9;
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

int f[N][2][2],n,m;
bitset<N> a[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		a[u].flip(v);
	}

	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++) a[j][i]=a[j][i]^a[i][j],a[i][j]=0;
		int p=i+1;
		while(p<=n&&!a[p][i]) p++;
		if(p>n) continue ;
		else if(p!=i+1){
			swap(a[i+1],a[p]);
			for(int j=1;j<=n;j++){
				a[j][i+1]=a[j][p]^a[j][i+1];
				a[j][p]=a[j][p]^a[j][i+1];
				a[j][i+1]=a[j][p]^a[j][i+1];
			}
		}
		bitset<N> b;
		for(int j=i+2;j<=n;j++){
			if(!a[j][i]) continue ;
			a[j]^=a[i+1];
			b.set(j);
		}
		for(int j=1;j<=n;j++) if(a[j][i+1]) a[j]^=b;
	}

	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int s:{0,1}){
			for(int p:{0,1}){
				for(int q:{0,1}){
					AddAs(f[i][s^(q&a[i][i])^(p&q&a[i][i-1])][q],f[i-1][s][p]);
				}
			}
		}
	}
	
	int ans=0;
	for(int p:{0,1}) AddAs(ans,f[n][0][p]);

	cout<<ans<<endl;

	return 0;
}