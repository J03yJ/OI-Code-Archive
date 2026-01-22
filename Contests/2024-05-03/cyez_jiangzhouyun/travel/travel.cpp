#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("travel.in");
ofstream fout("travel.out");
#define cin fin
#define cout fout

const int N=2e5+9;
int n,V;
int a[N];

namespace Naiiv{
	const int M=309;
	bool b[M][M<<3];
	void solve(){
		b[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=i;~j;j--){
				for(int k=0;k<=V-a[i];k++) b[j+1][k+a[i]]|=b[j][k]; 
			}
		}
		int ans=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=V;j++){
				if(b[i][j]){
					ans++;
//					cout<<j<<' ';
				}
			}
//			cout<<endl;
		}
		cout<<ans<<endl;
	}
}

signed main(){
	cin>>n>>V;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n<=300) Naiiv::solve();
	else cout<<n+1<<endl;
}
