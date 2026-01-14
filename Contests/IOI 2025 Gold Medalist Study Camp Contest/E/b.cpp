#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int a[N],n,q;
inline int Solve(vector<int> v){
	int m=v.size();
	vector<int> d(m,-1);
	vector<vector<int>> e(m);
	vector<int> stk;
	for(int i=0;i<m;i++){
		while(stk.size()&&v[i]>v[stk.back()]){
			e[i].push_back(stk.back());
			stk.pop_back();
		}
		stk.push_back(i);
	}
	stk.clear();
	for(int i=m-1;~i;i--){
		while(stk.size()&&v[i]>v[stk.back()]){
			e[i].push_back(stk.back());
			stk.pop_back();
		}
		stk.push_back(i);
	}
	int rt=max_element(v.begin(),v.end())-v.begin();
	d[rt]=1;
	queue<int> q;
	q.push(rt);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int y:e[x]){
			if(~d[y]) continue ;
			d[y]=d[x]+1;
			q.push(y);
		}
	}
	return *max_element(d.begin(),d.end());
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<Solve(vector<int>(a+l,a+r+1))<<endl;
	}

	return 0;
}