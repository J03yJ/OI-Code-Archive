#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e2+9;
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

int n,m;
char s[N][N];
inline int Id(int i,int j){return (i-1)*m+j;}

int fa[N*N],vsiz[N*N],esiz[N*N],slf[N*N];
inline void Init(){iota(fa+1,fa+n*m+1,1);}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	fa[y]=x;
	slf[x]|=slf[y];
	vsiz[x]+=vsiz[y];
	esiz[x]+=esiz[y];
}
inline void Clear(){
	for(int i=1;i<=n*m;i++) vsiz[i]=esiz[i]=slf[i]=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) s[i][j]=0;
}

inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>s[i][j];
	}
	
	Init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]!='*'){
				vsiz[Find(Id(i,j))]++;
				continue ;
			}
			if(s[i-1][j]!='.'&&s[i+1][j]!='.') return cout<<0<<endl,Clear();
			else if(s[i-1][j]!='.') esiz[Find(Id(i+1,j))]++,slf[Find(Id(i+1,j))]=1;
			else if(s[i+1][j]!='.') esiz[Find(Id(i-1,j))]++,slf[Find(Id(i-1,j))]=1;
			else{
				Merge(Id(i-1,j),Id(i+1,j));
				esiz[Find(Id(i-1,j))]++;
			}
			if(s[i][j-1]!='.'&&s[i][j+1]!='.') return cout<<0<<endl,Clear();
			else if(s[i][j-1]!='.') esiz[Find(Id(i,j+1))]++,slf[Find(Id(i,j+1))]=1;
			else if(s[i][j+1]!='.') esiz[Find(Id(i,j-1))]++,slf[Find(Id(i,j-1))]=1;
			else{
				Merge(Id(i,j-1),Id(i,j+1));
				esiz[Find(Id(i,j-1))]++;
			}
		}
	}

	int ans=1;
	for(int i=1;i<=n*m;i++){
		if(fa[i]!=i) continue ;
		if(!vsiz[i]) continue ;
		if(esiz[i]<vsiz[i]) MulAs(ans,vsiz[i]);
		else if(esiz[i]==vsiz[i]) MulAs(ans,2-slf[i]);
		else ans=0;
	}

	cout<<ans<<endl;
	
	Clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}