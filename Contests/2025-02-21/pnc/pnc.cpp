#include <bits/stdc++.h>
#include "pnc.h"

using namespace std;

const int N=2e5+9;
using ll=long long;

int a[N];
vector<int> e[N];
void init(int tid,int n,int x,int y,int m,vector<int> u,vector<int> v,vector<int> l,vector<int> r){
	for(int i=0;i<u.size();i++){
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}
}
int query1(long long v){
	return -1;
}
vector<int> query2(long long v,int k){
	vector<int> ret;
	ret.push_back(-1);
	return ret;
}
