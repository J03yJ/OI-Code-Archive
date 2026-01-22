#include<bits/stdc++.h>

using namespace std;

ifstream fin("egypt.in");
ofstream fout("egypt.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e3+9;

int a[N][N],n,m;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char c;
				cin>>c;
				a[i][j]=c-'0';
			}
		}

		for(int i=1;i<n;i++){
			for(int j=1;j<m;j++){
				if(!a[i][j]){
					a[i][j]^=1;
					a[i][j+1]^=1;
					a[i+1][j]^=1;
					a[i+1][j+1]^=1;
				}
			}
		}

		int cnt1=0,cnt2=0,f=0;
		for(int i=1;i<n;i++) cnt1+=(a[i][m]==0);
		for(int i=1;i<m;i++) cnt2+=(a[n][i]==0);
		f=(a[n][m]==0);

		int ans=max(cnt1,cnt2);
		f^=min(cnt1,cnt2)&1;
		if(f) ans++;

		cout<<ans<<endl;
	}

	return 0;
}