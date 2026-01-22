#include<bits/stdc++.h>

using namespace std;

int cnt=0;
mt19937 rng(4649);
inline int Query(int x,vector<int> s){
	int k;
	cout<<"? "<<x<<' '<<s.size()<<' ';
	for(int y:s) cout<<y<<' ';cout<<endl;
	cout.flush();
	cin>>k;
	assert(~k);
	return k;
}
inline void Solve(int n,vector<int> lft,vector<int> q){
	if(lft.size()==1){
		cout<<"! "<<lft.back()<<endl;
		cout.flush();
		return ;
	}
	int k=q.size()>>1;
	shuffle(q.begin(),q.end(),rng);
	vector<int> t[2]={vector<int>(q.begin(),q.begin()+k),
	vector<int>(q.begin()+k,q.end())};
	vector<int> p[2];
	int sum[2]={t[0].size(),t[1].size()};
	for(int x:lft){
		int f[2]={Query(x,t[0]),Query(x,t[1])};
		if(f[0]&&f[1]) sum[0]--,sum[1]--;
		else if(f[0]) sum[0]-=2,p[0].push_back(x);
		else if(f[1]) sum[1]-=2,p[1].push_back(x);
	}
	if(sum[0]==-1) Solve(n,p[0],t[0]);
	else Solve(n,p[1],t[1]);
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		assert(~n);

		vector<int> tmp(n),q(2*n-1);
		iota(tmp.begin(),tmp.end(),1);
		iota(q.begin(),q.end(),1);
		Solve(n,tmp,q);
	}

	return 0;
}