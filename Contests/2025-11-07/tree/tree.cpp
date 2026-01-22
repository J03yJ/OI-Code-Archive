#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2.5e3+9;

int vis[N],n,x,y;

signed main(){
	cin>>n>>x,y=11000;

	if(n==5){
		cout<<"5"<<endl;
		cout<<"10 15 6 8 4"<<endl;
		for(int i=1;i<5;i++) cout<<i<<' '<<i+1<<endl;
		return 0;
	}

	vector<int> res,tmp;
	for(int i=1;i<=n;i++){
		if(__gcd(i,6)!=1) continue ;
		if(i*2>n){
			tmp.push_back(i);
			continue ;
		}
		vector<int> t,cnt;
		t.push_back(i);
		while(t.back()<=n) t.push_back(t.back()*3);
		cnt.resize(t.size());
		for(int j=0;j<t.size();j++){
			while((t[j]<<cnt[j])<=n) cnt[j]++;
		}
		res.push_back(t[0]<<cnt[0]);
		for(int j=1;j<t.size();j++){
			for(int k=cnt[j-1]-1;k>=cnt[j];k--) res.push_back(t[j]<<k);
		}
	}

	for(int i=0;i<tmp.size();i++){
		if(vis[i]) continue ;
		for(int j=i+1;j<tmp.size();j++){
			if(vis[j]) continue ;
			if(tmp[i]/__gcd(tmp[i],tmp[j])*tmp[j]<=y){
				vis[i]=vis[j]=1;
				res.push_back(tmp[i]);
				res.push_back(tmp[i]/__gcd(tmp[i],tmp[j])*tmp[j]);
				res.push_back(tmp[j]);
				break ;
			}
		}
	}

	for(int i=0;i<tmp.size();i++){
		if(vis[i]) continue ;
		res.push_back(tmp[i]);
		res.push_back(tmp[i]<<1);
	}

	cout<<res.size()<<endl;
	for(int x:res) cout<<x<<' ';cout<<endl;
	for(int i=1;i<res.size();i++) cout<<i<<' '<<i+1<<endl;

	return 0;
}