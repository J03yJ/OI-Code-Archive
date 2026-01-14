#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		string s,t;
		int n,m;
		cin>>n>>m;
		cin>>s>>t;

		vector<int> pos(m-n+1);
		iota(pos.begin(),pos.end(),0);
		for(int i=0;i<n&&pos.size()>1;i++){
			vector<int> cur[2];
			for(int j:pos) cur[(s[i]-'0')^(t[i+j]-'0')].push_back(j);
			if(cur[1].size()) pos=cur[1];
			else pos=cur[0];
		}

		int x=pos.front(),cnt=0;
		for(int i=0;i<n;i++) cnt+=(s[i]-'0')^(t[i+x]-'0');
		cout<<cnt<<endl;
	}

	return 0;
}