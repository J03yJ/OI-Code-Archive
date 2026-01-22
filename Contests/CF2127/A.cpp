#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e2+9;

int a[N],n;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];

		vector<int> v(a+1,a+n+1);
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());
		if(v.front()==-1) v.erase(v.begin());
		if(v.size()>1||!v.front()) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}

	return 0;
}