#include<bits/stdc++.h>

using namespace std;

ifstream fin("flow.in");
ofstream fout("flow.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=4e4+9;
const int K=1e1+9;
const int S=(1<<10)+9;

int e[N][K][K],f[N][S],g[K][S],nxt[S],n,k;

signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		for(int p=0;p<k;p++){
			for(int q=0;q<k;q++){
				char c;
				cin>>c;
				e[i][p][q]=c-'0';
			}
		}
	}

	for(int i=n;i>=1;i--){
		if(i==n) for(int sta=0;sta<(1<<k);sta++) f[i][sta]=i;
		else{
			for(int c=0;c<=k;c++){
				for(int sta=0;sta<(1<<k);sta++) g[c][sta]=i;
			}
			for(int sta=0;sta<(1<<k);sta++) g[__builtin_popcount(sta)][sta]=f[i+1][sta];
			for(int c=0;c<=k;c++){
				for(int j=0;j<k;j++){
					for(int sta=0;sta<(1<<k);sta++){
						if(sta>>j&1) g[c][sta]=max(g[c][sta],g[c][sta^(1<<j)]);
					}
				}
			}
			nxt[0]=0;
			for(int sta=1;sta<(1<<k);sta++){
				int j=__builtin_ctz(sta),tta=0;
				for(int p=0;p<k;p++) tta|=e[i][j][p]<<p;
				nxt[sta]=nxt[sta^(1<<j)]|tta;
			}
			for(int sta=0;sta<(1<<k);sta++) f[i][sta]=g[__builtin_popcount(sta)][nxt[sta]];
			for(int j=0;j<k;j++){
				for(int sta=0;sta<(1<<k);sta++){
					if(sta>>j&1) f[i][sta]=min(f[i][sta],f[i][sta^(1<<j)]);
				}
			}
		}
	}

	ll ans=0;
	for(int i=1;i<=n;i++){
		vector<int> c(k+2,i);
		for(int sta=0;sta<(1<<k);sta++){
			c[__builtin_popcount(sta)]=max(c[__builtin_popcount(sta)],f[i][sta]);
		}
		for(int j=0;j<=k;j++) ans+=j*(c[j]-c[j+1]);
	}
	cout<<ans<<endl;

	return 0;
}