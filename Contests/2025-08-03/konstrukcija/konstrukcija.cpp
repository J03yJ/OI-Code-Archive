#include<bits/stdc++.h>

using namespace std;

ifstream fin("konstrukcija.in");
ofstream fout("konstrukcija.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;

signed main(){
	ll trg;
	cin>>trg;

	bool flag=trg<0;
	trg=abs(trg);
	
	int n=1,lim=__lg(abs(trg+1))+1;
	if(lim&1) lim++;
	vector<int> p;
	vector<vector<int>> flr;
	vector<pair<int,int>> e;
	flr.push_back({1});
	p.push_back(0);
	for(int i=1;i<=lim;i++){
		vector<int> tmp;
		for(int k:{0,1,2}){
			tmp.push_back(++n);
			for(int x:flr.back()){
				e.push_back({n,x});
			}
		}
		flr.push_back(tmp);
		p.push_back(0);
	}

	vector<int> node;
	for(int i=0;i<lim;i++){
		if(~trg>>i&1) continue ;
		if(~i&1){
			node.push_back(++n);
			e.push_back({n,flr[i+1][0]});
			e.push_back({n,flr[i+1][1]});
			node.push_back(++n);
			e.push_back({n,flr[i+2][0]});
			e.push_back({n,flr[i+2][1]});
		}else{
			node.push_back(++n);
			e.push_back({n,flr[i+1][0]});
			e.push_back({n,flr[i+1][1]});
		}
	}

	n++;
	for(int k:{0,1,2}) e.push_back({n,flr[lim][k]});
	n++;
	e.push_back({n,n-1});
	for(int u:node) e.push_back({n,u});

	if(flag){
		n++;
		e.push_back({n,n-2});
		for(int u:node) e.push_back({n,u});
		n++;
		e.push_back({n,n-1});
		e.push_back({n,n-2});
	}

	cout<<n<<' '<<e.size()<<endl;
	for(auto p:e) cout<<n-p.first+1<<' '<<n-p.second+1<<endl;

	return 0;
}