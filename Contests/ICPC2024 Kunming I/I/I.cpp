#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;

		int ans=s.size()+1,res=0;
		list<array<int,2>> cur;
		for(char c:s){
			if(!cur.size()||cur.back()[0]!=c) cur.push_back({c,1});
			else{
				res-=cur.back()[1]>>1;
				cur.back()[1]++;
				res+=cur.back()[1]>>1;
			}
		}

		for(char c:s){
			if(cur.front()[1]<=1) cur.pop_front();
			else{
				res-=cur.front()[1]>>1;
				cur.front()[1]--;
				res+=cur.front()[1]>>1;
			}
			if(!cur.size()||cur.back()[0]!=c) cur.push_back({c,1});
			else{
				res-=cur.back()[1]>>1;
				cur.back()[1]++;
				res+=cur.back()[1]>>1;
			}
			ans=min(ans,res);
		}

		cout<<ans<<endl;
	}
	return 0;
}