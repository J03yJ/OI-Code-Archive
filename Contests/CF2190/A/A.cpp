#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int n;
char a[N];

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	if(is_sorted(a+1,a+n+1)) cout<<"Bob"<<endl;
	else{
		int p=count(a+1,a+n+1,'0');
		vector<int> ans;
		for(int i=1;i<=p;i++) if(a[i]=='1') ans.push_back(i);
		for(int i=p+1;i<=n;i++) if(a[i]=='0') ans.push_back(i);

		cout<<"Alice"<<endl;
		cout<<ans.size()<<endl;
		for(int x:ans) cout<<x<<' ';cout<<endl;
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}