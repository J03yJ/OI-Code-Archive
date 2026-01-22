#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e2+9;

int n,k;
double f[N][N][N],g[N][N][N],p;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k>>p;
	p/=100;

	auto T=[](int x){
		if(!x) return 0;
		int cnt=0;
		while(~x&1) x>>=1,cnt++;
		return cnt;
	};
	f[0][0][0]=1;
	for(int i=0;i<=k;i++){
		if(i) f[i][0][i]=f[i-1][0][i-1]*p;
		for(int j=1;j<=k;j++){
			for(int t=i+1;t<=k;t++){
				if(j*2<=k) f[i][j][t]+=f[i-1][j*2][t-1]*p;
				f[i][j][t]+=f[i][j-1][t-1]*(1-p);
				if(j&1) g[i][i][t]+=f[i][j][t];
			}
		}
		for(int j=0;j<i;j++){
			for(int t=0;t<=k;t++){
				g[i][j][t]+=g[i-1][j][t-1]*p;
				g[i][j][t]+=g[i][j][t-1]*(1-p);
			}
		}
	}

	double ans=0;
	for(int s=0;s<=k;s++){
		for(int x=0;x<=k;x++){
			ans+=(T(n+x)+s)*f[s][x][k];
		}
		for(int t=0;t<s;t++){
			ans+=t*g[s][t][k];
		}
	}
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}