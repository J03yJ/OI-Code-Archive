#include<bits/stdc++.h>
#include "guess.h"

using namespace std;

mt19937 rng(4649);
using ull=unsigned long long;
using bint=__int128;
using Seg=pair<ull,ull>;

inline ull Work(ull L,ull R){
	if(L==R) return L;
	ull mid=bint(L)+R>>1; 
	while(true){
		if(Query({{L,mid}})) return Work(L,mid);
		if(Query({{mid+1,R}})) return Work(mid+1,R);
	}
}
inline ull MaxLen(vector<Seg> &v){
	ull res=0;
	for(auto p:v) res=max(res,p.second-p.first+1);
	return res;
}
inline Seg F(int l,int r,vector<Seg> &v){
	if(l==r) return v[l];
	int mid=l+r>>1;
	while(true){
		if(Query(vector<Seg>(v.begin()+mid+1,v.begin()+r+1))) return F(mid+1,r,v);
		if(Query(vector<Seg>(v.begin()+l,v.begin()+mid+1))) return F(l,mid,v);
	}
}
const int D=2;
inline ull Find(ull L,ull R,int c,vector<Seg> &T){
	if(L==R){
		if(!c) return L;
		else{
			T.push_back({L,R});
			auto p=F(0,T.size()-1,T);
			T.clear();
			return Find(p.first,p.second,0,T);
		}
	}
	if(T.size()>=D){
		T.push_back({L,R});
		auto p=F(0,T.size()-1,T);
		T.clear();
		return Find(p.first,p.second,0,T);
	}
	ull mid=bint(L)+R>>1; 
	if(Query({{mid+1,R}})){
		T.clear();
		return Find(mid+1,R,0,T);
	}else{
		T.push_back({mid+1,R});
		return Find(L,mid,c+1,T);
	}
}
inline ull Korw(ull L,ull R){
	vector<Seg> T;
	return Find(L,R,0,T);
}

ull Guess(){
	return Korw(10,ULLONG_MAX-10);
}
