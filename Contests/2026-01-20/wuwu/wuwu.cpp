#include<bits/stdc++.h>

using namespace std;

ifstream fin("wuwu.in");
ofstream fout("wuwu.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e1+9;

int a[N],f[N][N],n,k;
namespace N1{
	inline void Solve(){
		if(1ll*(a[0]-1)*f[0][0]==k){
			cout<<"Yes"<<endl;
			while(a[0]--) cout<<0<<' ';cout<<endl;
		}else cout<<"No"<<endl;
	}
}

signed main(){
	cin>>n>>k,n++;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) cin>>f[i][j];
	}

	if(n==1) N1::Solve();
	else cout<<"No"<<endl;

	return 0;
}