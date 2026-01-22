#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;

int a[N],n;

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	sort(a+1,a+n+1);
	set<array<int,2>> s;
	auto Query=[&](int x){
		auto it=s.lower_bound({x+1,});
		if(it==s.begin()) return -1;
		else return (*--it)[1];
	};
	auto Insert=[&](array<int,2> x){
		if(Query(x[0])>=x[1]) return ;
		s.insert(x);
		while(true){
			auto it=s.upper_bound(x);
			if(it==s.end()) break ;
			if((*it)[1]<=x[1]) s.erase(it);
			else break ;
		}
	};

	int p=-1,q=-1;
	Insert({a[1],1});
	for(int i=3;i<=n;i++){
		int cp=-1,cq=-1;
		cq=Query(a[i]);
		if(a[i]+a[i-2]<2*a[i-1]) s.clear();
		if(~p&&a[i]+a[i-3]>=2*a[i-1]) Insert({a[i-2]*2-a[p],i-2});
		if(~p&&a[i]+a[p]>=2*a[i-2]) cp=max(cp,i-3);
		if(~q&&a[i]+a[q]>=2*a[i-1]) Insert({a[i-2]*2-a[i-3],i-2});
		if(~q&&a[i]+a[i-3]>=2*a[i-2]) cp=max(cp,q);
		p=cp,q=cq;
	}

	if(~p||~q||s.size()) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}