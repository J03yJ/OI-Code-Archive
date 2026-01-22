#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;

int c[N][26],tot[26],n,m;
string s[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i];

	for(int i=1;i<=n;i++){
		for(auto t:s[i]){
			c[i][t-'A']++;
			tot[t-'A']++;
		}
	}

	for(int i=1;i<=n;i++){
		ll tmp[26],res=LLONG_MAX,err=0;
		for(int j=0;j<26;j++){
			tmp[j]=1ll*m*(tot[j]-c[i][j])-c[i][j];
			if(tot[j]-c[i][j]) res=min(res,tmp[j]/(tot[j]-c[i][j]));
			err|=(tmp[j]<0);
		}
		if(err) cout<<-1<<' ';
		else cout<<res<<' ';
	}

	cout<<endl;

	return 0;
}