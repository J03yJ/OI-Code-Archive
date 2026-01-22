#include<bits/stdc++.h>

using namespace std;

ifstream fin("road.in");
ofstream fout("road.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=3e2+9;
const int M=N*N;

ll a[N][N];
int u[M],v[M],w[M],p[M],q[M],t[M],n,m,k;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i];

	memset(a,0x3f,sizeof a);
	for(int i=1;i<=n;i++) a[i][i]=0;
	for(int i=1;i<=m;i++) a[u[i]][v[i]]=a[v[i]][u[i]]=w[i];
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(i==k) continue ;
			for(int j=1;j<=n;j++){
				if(i==j) continue ;
				if(j==k) continue ;
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}

	cin>>k;
	for(int i=1;i<=k;i++) cin>>p[i]>>q[i]>>t[i];

	int cnt=0;
	for(int i=1;i<=m;i++){
		bool flag=0;
		for(int j=1;j<=k;j++){
			if(a[p[j]][u[i]]+w[i]+a[v[i]][q[j]]<=t[j]) flag|=1;
			else if(a[p[j]][v[i]]+w[i]+a[u[i]][q[j]]<=t[j]) flag|=1;
			if(flag) continue ;
		}
		cnt+=flag;
	}

	cout<<cnt<<endl;

	return 0;
}