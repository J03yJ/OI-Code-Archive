#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int d[N],n,m;

signed main(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		d[u]++,d[v]++;
	}

	ll c=0;
	for(int i=1;i<=n;i++) c+=((n-1)-(n-1-d[i]&1));
	
	cout<<c/2<<endl;

	return 0;
}