#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=4e3+9;
const int M=4000;

int f[2][2][N][N],a[N],s[N],p[N],q[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];

	int lim=1;
	while(lim*(lim-1)/2<=n) lim++;

	for(int i=1;i<=lim;i++){
		for(int j=1;j<i;j+=2) p[i]+=j;
		q[i]=i*(i-1)/2;
	}

	memset(f,0x3f,sizeof f);
	for(int c:{0,1}){
		for(int i=1;i<=n;i++){
			for(int j=i-1;j<=n;j++){
				f[c][0][i][j]=s[i-1]-(s[n]-s[j]);
				f[c][1][i][j]=(s[n]-s[j])-s[i-1];
			}
		}
	}

	for(int c=lim;c>=1;c--){
		for(int i=n;i>=p[c];i--){
			for(int j=max(i+c-1,n-(i+c)+1);j<=min(n-(i-c)+1,n);j++){
				f[c&1][0][i][j]=-min(f[c&1][1][i+c][j],f[~c&1][1][i+c+1][j]);
				f[c&1][1][i][j]=-min(f[c&1][0][i][j-c],f[~c&1][0][i][j-c-1]);
			}
		}
	}

	cout<<f[1][0][1][n]<<endl;

	return 0;
}