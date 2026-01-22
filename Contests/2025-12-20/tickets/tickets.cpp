#include<bits/stdc++.h>
#include"tickets.h"

using namespace std;

using ll=long long;

ll find_maximum(int k,vector<vector<int>> a){
	int n=a.size(),m=a[0].size();
	vector<vector<ll>> s(n);
	vector<vector<int>> p(n);
	for(int i=0;i<n;i++){
		p[i].resize(m);
		iota(p[i].begin(),p[i].end(),0);
		sort(p[i].begin(),p[i].end(),[&](int x,int y){return a[i][x]<a[i][y];});
		s[i].resize(m);
		for(int j=0;j<m;j++) s[i][j]=(j?s[i][j-1]:0)+a[i][p[i][j]];
	}
	auto Sum=[&](int i,int l,int r){return (r<0?0:s[i][r])-(l>0?s[i][l-1]:0);};
	auto W=[&](int i,int t){return Sum(i,m-k+t,m-1)-Sum(i,0,t-1);};
	
	ll ans=0;
	vector<int> len(n,k);
	priority_queue<pair<ll,int>> q;
	for(int i=0;i<n;i++){
		ans+=W(i,len[i]);
		q.push({W(i,len[i]-1)-W(i,len[i]),i});
	}
	for(int o=0;o<(n/2)*k;o++){
		int i=q.top().second;
		ans+=q.top().first;
		q.pop();
		if(--len[i]) q.push({W(i,len[i]-1)-W(i,len[i]),i});
	}

	vector<vector<int>> b(n);
	vector<array<int,2>> lp,rp;
	int lc=k-1,rc=0;
	auto Allc=[&](){return lc=(lc+1)%k;};
	auto Arrc=[&](){return rc=(rc+k-1)%k;};
	for(int i=0;i<n;i++){
		b[i].resize(m,-1);
		for(int j=0;j<len[i];j++) b[i][p[i][j]]=Allc();
		for(int j=m-k+len[i];j<m;j++) b[i][p[i][j]]=Arrc();
	}
	allocate_tickets(b);

	return ans;
}