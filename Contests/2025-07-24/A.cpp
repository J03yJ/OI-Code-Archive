#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e3+9;

int a[N][N],b[N][N],n,m,k;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) cin>>a[i][j];
		}

		int sum=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++) b[i][j]=m+1;
			for(int j=m;j>=1;j--) b[i][a[i][j]]=j;
			if(i!=1) for(int j=1;j<=k;j++) b[i][j]=min(b[i][j],b[i-1][j]);
			int mx=0;
			for(int j=1;j<=k;j++) mx=max(mx,b[i][j]);
			sum+=m-mx+1;
		}

		cout<<sum<<endl;
	}

	return 0;
}