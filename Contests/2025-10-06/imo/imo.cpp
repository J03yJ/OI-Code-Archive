#include<bits/stdc++.h>

using namespace std;

ifstream fin("imo.in");
ofstream fout("imo.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e4+9;
const int M=1e2+9;
const int MK=1e4+9;

int a[N][M],sum[N],p[N],f[MK],g[MK],n,m,k;
bitset<MK> h[M];

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j],sum[i]+=a[i][j];
		p[i]=i;
	}
	sort(p+1,p+n+1,[](int i,int j){return sum[i]^sum[j]?sum[i]>sum[j]:i<j;});

	int lim=m*k;
	sum[0]=lim+1,p[n+1]=n+1;
	for(int i=1;i<=n;i++){
		int mlim=(sum[p[i-1]]-sum[p[i+1]])/k+2;
		h[0][0]=1;
		for(int j=1;j<=m;j++){
			for(int t=mlim-1;~t;t--){
				h[t+1]|=h[t]<<a[p[i]][j];
			}
		}
		for(int j=lim-1;j>=0;j--) f[j]=min(f[j],f[j+1]);
		memset(g,0x3f,sizeof g);
		for(int c=0;c<=mlim;c++){
			for(int j=h[c]._Find_first();j<=lim;j=h[c]._Find_next(j)){
				g[sum[p[i]]-j]=min(g[sum[p[i]]-j],f[sum[p[i]]-j+c*k+(i-1&&p[i]<p[i-1])]+m-c);
			}
		}
		memcpy(f,g,sizeof g);
		for(int j=0;j<=mlim;j++) h[j].reset();
	}
	
	int ans=INT_MAX;
	for(int i=0;i<=lim;i++) ans=min(ans,f[i]);
	
	cout<<ans<<endl;

	return 0;
}