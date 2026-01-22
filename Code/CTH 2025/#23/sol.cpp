#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using Data=array<int,4>;
const int N=1e3+9;

char a[N][N];
int f[N][N],le[N],ri[N],n,m;
Data p[N][2],s[N][2];
inline int Mex(int x,int y){return __builtin_ctz(~(1<<x|1<<y));}
inline int Mex(int x,int y,int z){return __builtin_ctz(~(1<<x|1<<y|1<<z));}
inline Data Merge(Data x,Data y){
	Data z;
	for(int i:{0,1,2,3}) z[i]=y[x[i]];
	return z;
}
inline Data MexWith(int x){
	Data y;
	for(int i:{0,1,2,3}) y[i]=Mex(i,x);
	return y;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	int ans=0;
	for(int j=1;j<=m;j++) f[n+1][j]=3;
	for(int i=n;i>=1;i--){
		p[0][0]=p[0][1]=s[m+1][0]=s[m+1][1]={0,1,2,3};
		for(int j=1;j<=m;j++){
			le[j]=le[j-1]|(a[i][j]=='#');
			p[j][0]=a[i][j]=='#'?Data({3,3,3,3}):Merge(p[j-1][0],MexWith(f[i+1][j]));
			p[j][1]=le[j]?p[j-1][1]:Merge(MexWith(f[i+1][j]),p[j-1][1]);
		}
		for(int j=m;j>=1;j--){
			ri[j]=ri[j+1]|(a[i][j]=='#');
			s[j][0]=a[i][j]=='#'?Data({3,3,3,3}):Merge(s[j+1][0],MexWith(f[i+1][j]));
			s[j][1]=ri[j]?s[j+1][1]:Merge(MexWith(f[i+1][j]),s[j+1][1]);
		}
		for(int j=1;j<=m;j++){
			f[i][j]=a[i][j]=='#'?3:Mex(f[i+1][j],
				le[j]?p[j-1][0][3]:p[j-1][0][s[j+1][1][3]],
				ri[j]?s[j+1][0][3]:s[j+1][0][p[j-1][1][3]]);
			if(a[i][j]=='B') ans^=f[i][j];
		}
	}

	cout<<(ans?"Alice":"Bob")<<endl;

	return 0;
}