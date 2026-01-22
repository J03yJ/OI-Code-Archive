#include<bits/stdc++.h>

using namespace std;

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e4+9;
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

int a[N],b[N],ia[N],ib[N],vis[N],cnt[N],f[N][2][2],g[N][2][2],n,k;

int knp[N],_knp[N];
inline void Init(){knp[0]=1;}
inline void Insert(int v,int k){for(int i=n;i>=v;i--) AddAs(_knp[i],Mul(k,knp[i-v]));}
inline void Stamp(){for(int i=0;i<=n;i++) knp[i]=_knp[i],_knp[i]=0;}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],ia[a[i]]=i;
	for(int i=1;i<=n;i++) cin>>b[i],ib[b[i]]=i;

	for(int i=1;i<=n;i++){
		if(vis[i]) continue ;
		int x=i,c=0;
		while(!vis[x]){
			c++;
			vis[x]=1;
			x=ia[b[x]];
		}
		cnt[c]++;
	}

	Init();
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int k=1;k<=cnt[i];k++){
			for(int j=0;j<=i;j++){
				for(int p:{0,1}){
					for(int q:{0,1}){
						if(!f[j][p][q]) continue ;
						Insert(j+!p,f[j][p][q]);
						Insert(j+!q,f[j][p][q]);
					}
				}
			}
			Stamp();
		}
		memset(g,0,sizeof g);
		for(int j=0;j<=i;j++){
			for(int p:{0,1}){
				for(int q:{0,1}){
					AddAs(g[j+1][p][1],f[j][p][q]);
					if(i>1) AddAs(g[j+!q][p][0],f[j][p][q]);
					else AddAs(g[j+!q][1][0],f[j][p][q]);
				}
			}
		}
		memcpy(f,g,sizeof g);
	}

	int ans=0;
	for(int i=k;i<=n;i++) AddAs(ans,knp[i]);

	cout<<ans<<endl;

	return 0;
}