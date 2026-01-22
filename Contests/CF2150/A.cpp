#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		vector<char> a(n);
		vector<int> p(m);
		for(char &c:a) cin>>c;
		for(int &x:p) cin>>x;

		set<int> b(p.begin(),p.end());
		int cur=1,lst=1;
		auto O=[&](int x,char c){
			if(c=='A') return x+1;
			else{
				x++;
				while(b.find(x)!=b.end()) x++;
				return x;
			}
		};
		for(int i=0;i<n;i++){
			if(i>0) cur=O(lst,a[i-1]);
			lst=cur,cur=O(cur,a[i]);
			b.insert(cur);
		}

		cout<<b.size()<<endl;
		for(int x:b) cout<<x<<' ';cout<<endl;
	}

	return 0;
}