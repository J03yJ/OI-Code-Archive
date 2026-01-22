#include<bits/stdc++.h>

using namespace std;

ifstream fin("plant.in");
ofstream fout("plant.out");
#define cin fin
#define cout fout
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

int p[N],sum[N],nxt[N],n,m;
char a[N][N];
inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	int ans=0;
	for(int i=1;i<=n;i++) p[i]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			p[j]=max(p[j],i);
			while(p[j]<=m&&a[j][p[j]]=='0') p[j]++;
		}
		vector<int> stk;
		for(int j=n;j>=1;j--){
			while(stk.size()&&p[stk.back()]>=p[j]) stk.pop_back();
			if(stk.size()) nxt[j]=stk.back();
			else nxt[j]=n+1;
			sum[j]=Add(sum[nxt[j]],Mul(nxt[j]-j,p[j]-i));
			AddAs(ans,sum[j]);
			stk.push_back(j);
		}
		for(int j=1;j<=n+1;j++) nxt[j]=sum[j]=0;
	}

	cout<<ans<<endl;
}

signed main(){
	int T,Tid;
	cin>>T>>Tid;
	while(T--) Solve();

	return 0;
}