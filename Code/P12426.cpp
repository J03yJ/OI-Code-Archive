#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e3+9;

int a[N][N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++) cin>>a[i][j];
	}

	int l=0,r=0;
	for(int i=1;i<=n;i++) if(a[i][n]==a[1][n]) l=i;
	for(int i=n;i>=1;i--) if(a[1][i]==a[1][n]) r=i;
	
	if(a[1][n]==1) cout<<l<<endl;
	else if(a[1][n]==2) cout<<l<<' '<<r<<endl;
	else{
		cout<<l<<' ';
		for(int i=l+1;i<r;i++){
			if(a[l][i]==a[l+1][i]+1){
				if(a[l][i]==a[l][i-1]+1) cout<<i<<' ';
			}else if(a[i][r]==a[i][r-1]+1){
				if(a[i][r]==a[i+1][r]+1) cout<<i<<' ';
			}else{
				if(a[l+1][i]==a[l+1][i-1]&&a[i][r-1]==a[i+1][r-1]) cout<<i<<' ';
			}
		}
		cout<<r<<endl;
	}

	return 0;
}