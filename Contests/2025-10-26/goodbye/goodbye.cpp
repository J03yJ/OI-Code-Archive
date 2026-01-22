#include<bits/stdc++.h>

using namespace std;

ifstream fin("goodbye.in");
ofstream fout("goodbye.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;
const ll inf=1e18;

int w[N],n,a,b;
ll cst[N],f[N];

signed main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>w[i];

	for(int i=1;i<=b;i++) cst[i]=inf,f[i]=inf;
	for(int i=1;i<n;i++){
		int g=__gcd(i,n-i),x=i/g,y=(n-i)/g;
		ll c=1ll*x*w[i]+1ll*y*w[i+1],p=x+y;
		cst[p]=min(cst[p],c);
	}

	for(int i=1;i<=n;i++){
		if(cst[i]==inf) continue ;
		for(int j=i;j<=b;j++){
			f[j]=min(f[j],f[j-i]+cst[i]);
		}
	}

	for(int i=b;i>=0;i--){
		if(f[i]==inf) continue ;
		cout<<i<<' '<<f[i]<<endl;
		break ;
	}

	return 0;
}