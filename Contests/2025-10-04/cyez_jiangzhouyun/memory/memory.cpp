#include<bits/stdc++.h>

using namespace std;

ifstream fin("memory.in");
ofstream fout("memory.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=7e2+9;
const int M=2e3+9;

int n,m,p;
vector<int> e[M];

double est[M],stp[N][N],f[N][N];
inline void GetE(int x){
	est[x]=1;
	for(int y:e[x]){
		GetE(y);
		est[x]+=est[y]/e[x].size();
	}
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>p;
		for(int i=1,u,v;i<=m-n;i++){
			cin>>u>>v;
			e[u].push_back(v);
		}

		for(int i=1;i<=n;i++) GetE(i);

		for(int i=1;i<=n;i++){
			double p=1,ex=0;
			for(int j=i;j<=n;j++){
				stp[i][j]=ex*((1)/p)+j-i;
				ex+=p*e[j].size()/(e[j].size()+1)*(est[j]+j-i);
				p/=e[j].size()+1;
			}
		}

		for(int i=1;i<=n;i++) for(int j=0;j<=p;j++) f[i][j]=1e18;
		f[1][1]=0;
		for(int i=2;i<=n;i++){
			for(int j=1;j<=p;j++){
				for(int l=1;l<i;l++){
					f[i][j]=min(f[i][j],f[l][j-1]+stp[l][i]);
				}
			}
		}

		cout<<fixed<<setprecision(4)<<f[n][p]<<endl;

		for(int i=1;i<=m;i++) est[i]=0,e[i].clear();
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++) stp[i][j]=f[i][j]=0;
		}
	}

	return 0;
}