#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n,x;
		cin>>n>>x;
		set<int> s;
		for(int i=1;i<=n;i++){
			char c;
			cin>>c;
			if(c=='#') s.insert(i);
		}
		s.insert(0);
		s.insert(n+1);
		int l=*prev(s.upper_bound(x)),r=*s.lower_bound(x);
		int ans=max(min(l,n-(x+1)+1),min(n-r+1,(x-1)))+1;

		cout<<ans<<endl;
	}

	return 0;
}