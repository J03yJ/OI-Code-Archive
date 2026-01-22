#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,k;
		string s;
		cin>>n>>k>>s;

		vector<int> cnt(n<<1|1);
		s=" "+s+s;
		for(int i=1;i<=(n<<1)-6;i++){
			if(s.substr(i,7)=="nanjing") cnt[i]++;
		}
		for(int i=1;i<=(n<<1);i++) cnt[i]+=cnt[i-1];

		int ans=0;
		for(int i=1;i<=min(n,k+1);i++) ans=max(ans,cnt[max(i-1,i+n-7)]-cnt[i-1]);
		cout<<ans<<endl;
	}

	return 0;
}