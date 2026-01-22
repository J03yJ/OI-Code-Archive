#include<bits/stdc++.h>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e2+9;

ll sum[N];
int a[N],n,d,r;
bitset<N> f[N][N],g[N][N];
ll h[N][N];

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>d>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];

		for(int i=n;i>=1;i--){
			g[i][i].set(0);
			if((a[i]-r)%d==0) f[i][i].set(1);
			for(int j=i+1;j<=n;j++){
				int len=j-i+1;
				ll s=sum[j]-sum[i-1];
				for(int m=i;m<j;m++){
					for(int p=0;p<=m-i+1;p++){
						for(int q=0;q<=j-m;q++){
							g[i][j].set(p+q,g[i][j][p+q]|g[i][m][p]&g[m+1][j][q]);
							f[i][j].set(p+q,f[i][j][p+q]|f[i][m][p]&f[m+1][j][q]);
						}
					}
				}
				for(int k=1;k<=len;k++){
					if(!((s-ll(k)*r)%d)){
						f[i][j].set(k,g[i][j][k-1]);
					}
				}
				g[i][j]|=f[i][j];
			}
		}
		
		memset(h,-0x3f,sizeof h);
		h[0][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=i;j++) h[i][j]=-a[i]+h[i-1][j];
			for(int j=1;j<=i;j++){
				for(int k=0;k<=i;k++){
					if(!f[j][i][k]) continue ;
					for(int c=0;k+c<=i;c++){
						h[i][c+k]=max(h[i][c+k],h[j-1][c]);
					}
				}
			}
		}

		ll ans=0;
		for(int k=0;k<=n;k++) ans=max(ans,(sum[n]+h[n][k]-k*ll(r))/d);

		cout<<ans<<endl;

		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				f[i][j].reset();
				g[i][j].reset();
			}
		}
	}

	return 0;
}