#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e2+9;

int a[N][N],s[N][N],n,q;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;
			cin>>c;
			a[i][j]=(c=='#');
		}
	}
	
	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++){
			int tmp=(!a[i][j]&&!a[i+1][j]&&!a[i][j+1]&&!a[i+1][j+1]);
			s[i][j]=tmp+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}

	while(q--){
		int x0,x1,y0,y1;
		cin>>x0>>x1>>y0>>y1;
		x0--,x1--,y0--,y1--;
		cout<<s[x1][y1]-s[x1][y0]-s[x0][y1]+s[x0][y0]<<endl;
	}


	return 0;
}