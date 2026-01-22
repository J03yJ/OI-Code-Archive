#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ld=long double;
const int N=1e5+9;
const int K=3e1+9;
const ld eps=1e-12;

int p[N],n,k;
ld pw[N][K],qw[N][K],P[K][K],F[K][K];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>p[i];

	for(int i=1;i<=n;i++){
		const ld t=p[i]/ld(100);
		pw[i][0]=qw[i][0]=1;
		for(int j=1;j<=k+1;j++){
			pw[i][j]=pw[i][j-1]*t;
			qw[i][j]=qw[i][j-1]*(1-t);
		}
	}

	for(int i=0;i<=k;i++){
		for(int j=i;j<=k;j++){
			ld f=0,g=eps;
			for(int o=1;o<=n;o++) f+=pw[o][i+1]*qw[o][j-i];
			for(int o=1;o<=n;o++) g+=pw[o][i]*qw[o][j-i];
			P[i][j]=f/g;
		}
	}
	for(int i=0;i<=k;i++) F[i][k]=1;
	for(int j=k-1;j>=0;j--){
		for(int i=0;i<=j;i++){
			F[i][j]=max(P[i][j]*F[i+1][j+1]+(1-P[i][j])*F[i][j+1],2*P[i][j]*F[i+1][j+1]);
		}
	}

	cout<<fixed<<setprecision(10)<<1000*(F[0][0]-1)<<endl;

	return 0;
}