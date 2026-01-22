#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int a[N],b[N],n,m;
inline void Solve(){
	cin>>m>>n;
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>a[i];

	ll ans=0;
	int cnt[2][2]={{0,0},{0,0}};
	unordered_map<int,int> f[2][2][28];
	for(int i=1;i<n;i++){
		if(((a[i]^a[i+1])&3)!=1) continue ;
		if((a[i]^a[i+1])>>2) continue ;
		int p=a[i]&1,q=a[i]>>1&1,x=a[i]>>2;
		for(int j=0;j<28;j++) f[p][q][j][x&((1<<j+1)-1)]++;
		cnt[p][q]++;
	}
	for(int i=1;i<m;i++){
		if(((b[i]^b[i+1])&3)!=2) continue ;
		int p=b[i]&1,q=b[i]>>1&1;
		int x=b[i]>>2,y=b[i+1]>>2;
		if(!(x^y)) ans+=cnt[p][q];
		for(int j=0;j<28;j++){
			if((x^y)>>j+1) continue ;
			int _x=x&((1<<j+1)-1),_y=y&((1<<j+1)-1);
			_x^=(1<<j)-1,_y^=(1<<j);
			if(_x!=_y) continue ;
			if(f[p][q^1][j].count(_x)) ans+=f[p][q^1][j][_x];
		}
	}

	cout<<ans<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}