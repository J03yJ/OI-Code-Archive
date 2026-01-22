#include<bits/stdc++.h>

using namespace std;

ifstream fin("erase.in");
ofstream fout("erase.out");
#define cin fin
#define cout fout
#define endl '\n'

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n+1);
		for(int i=1;i<=n;i++) cin>>a[i];

		multiset<int> v,d;
		d.insert(0);
		auto Insert=[&v,&d](int x){
			auto it=v.lower_bound(x);
			if(it!=v.end()&&it!=v.begin()) d.erase(d.find(*it-*prev(it)));
			if(it!=v.begin()) d.insert(x-*prev(it));
			if(it!=v.end()) d.insert(*it-x);
			v.insert(x);
		};
		auto Erase=[&v,&d](int x){
			auto it=v.find(x);
			if(it!=v.begin()) d.erase(d.find(*it-*prev(it)));
			if(next(it)!=v.end()) d.erase(d.find(*next(it)-*it));
			if(it!=v.begin()&&next(it)!=v.end()) d.insert(*next(it)-*prev(it));
			v.erase(it);
		};

		for(int i=1;i<=n;i++) Insert(a[i]);

		int q;
		cin>>q;
		while(q--){
			int i,x;
			cin>>i>>x;
			Erase(a[i]);
			Insert(a[i]=x);
			cout<<*d.rbegin()+*v.rbegin()<<endl;
		}
	}

	return 0;
}