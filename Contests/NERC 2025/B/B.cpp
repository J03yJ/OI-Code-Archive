#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

inline void Solve(){
	int n,m;
	cin>>n>>m;
	vector<int> a(n),b(m);
	for(int &x:a) cin>>x;
	for(int &x:b) cin>>x;

	priority_queue<int> q[2];
	for(int x:a) q[0].push(x);
	for(int x:b) q[1].push(x);

	for(int o=0;q[0].size()&&q[1].size();o^=1){
		int x=q[o^1].top()-q[o].top();
		q[o^1].pop();
		if(x>0) q[o^1].push(x);
	}

	if(!q[0].size()) cout<<"Bob"<<endl;
	else cout<<"Alice"<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}