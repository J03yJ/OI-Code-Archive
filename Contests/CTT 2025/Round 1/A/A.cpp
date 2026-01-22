#include<bits/stdc++.h>
#include"haru.h"

using namespace std;
using ll=long long;

mt19937 rng(998244353);

vector<vector<int>> u,v;
inline void InsChain(int n){
	u.push_back(vector<int>());
	v.push_back(vector<int>());
	for(int i=0;i<n-1;i++){
		u.back().push_back(i);
		v.back().push_back(i+1);
	}
}
inline void InsFlower(int n,int root){
	u.push_back(vector<int>());
	v.push_back(vector<int>());
	for(int i=0;i<n;i++){
		if(i==root) continue ;
		u.back().push_back(root);
		v.back().push_back(i);
	}
}

inline bool NotImp(vector<int> u,vector<int> l,vector<int> r,vector<int> trs,vector<int> d,ll val,ll t){
	vector<int> e1,e2;
	int c=trs.back(),lst=c;
	trs.pop_back();
	for(int i:u) e1.push_back(c),e2.push_back(i);
	for(int i:d) e1.push_back(c),e2.push_back(i);
	for(int i:l) e1.push_back(lst),e2.push_back(i),lst=i;
	lst=c;
	for(int i:r) e1.push_back(lst),e2.push_back(i),lst=i;
	for(int i:trs) e1.push_back(lst),e2.push_back(i),lst=i;
	ll q=t*(l.size()+r.size()+trs.size()-1)+val;
	return guess(e1,e2,q);
}
inline bool Check(vector<int> x,vector<int> y,vector<int> z,vector<int> w,vector<int> ans,ll val){
	vector<int> e1,e2;
	int lst=w.front();
	for(int i:w) if(i!=w.front()) e1.push_back(lst),e2.push_back(i),lst=i;
	for(int i:x) e1.push_back(w.front()),e2.push_back(i);
	for(int i:y) e1.push_back(w.back()),e2.push_back(i);
	for(int i:z) e1.push_back(w[1]),e2.push_back(i);
	ll q=val;
	for(int i:w) q+=ans[i];
	return guess(e1,e2,q);
}

vector<int> haru(int n){
	u.clear(),v.clear();
	for(int i=0;i<n;i++) InsFlower(n,i);
	InsChain(n);
	vector<ll> res=query(u,v);
	vector<ll> tmp(res.begin(),prev(res.end()));
	sort(tmp.begin(),tmp.end());

	ll val=0;
	for(int i=0;i<n;i++) val+=tmp[i];
	val-=res.back();
	val-=2*tmp.back();
	val/=n-3;
	ll t=tmp.back()-val;

	vector<int> ans(n,-1),a,b;
	for(int i=0;i<n;i++){
		if(res[i]==tmp.back()){
			a.push_back(i);
			continue ;
		}
		ans[i]=res[i]-val;
		b.push_back(i);
	}

	if(b.size()<=3){
		vector<int> s[4];
		int m=(a.size()-1)%3+1;
		for(int i=0;i<a.size()-m;i++) s[i%3].push_back(a[i]);
		for(int i=a.size()-m;i<a.size();i++) s[3].push_back(a[i]);
		if(NotImp(s[0],s[1],s[2],s[3],b,val,t)){
			for(int i:s[0]) ans[i]=t;
			b.insert(b.end(),s[0].begin(),s[0].end());
			s[0].clear();
		}else if(NotImp(s[1],s[2],s[0],s[3],b,val,t)){
			for(int i:s[1]) ans[i]=t;
			b.insert(b.end(),s[1].begin(),s[1].end());
			s[1].clear();
		}else{
			for(int i:s[2]) ans[i]=t;
			b.insert(b.end(),s[2].begin(),s[2].end());
			s[2].clear();
		}
		a.clear();
		for(int i:{0,1,2,3}) a.insert(a.end(),s[i].begin(),s[i].end());
	}

	for(int w=0;w<60;w++){
		vector<int> x,y;
		for(int i:a){
			if(~i>>w&1) x.push_back(i);
			else y.push_back(i);
		}
		if(!x.size()||!y.size()) continue ;
		if(Check(x,y,vector<int>(),b,ans,val)){
			vector<int> trs;
			while(x.size()>1){
				vector<int> s[2];
				for(int i=0;i<x.size();i++) s[i&1].push_back(x[i]);
				vector<int> tmp=trs;
				tmp.insert(tmp.end(),s[1].begin(),s[1].end());
				if(Check(s[0],y,tmp,b,ans,val)){
					x=s[0];
					for(int i:s[1]) ans[i]=t;
					trs.insert(trs.end(),s[1].begin(),s[1].end());
				}else{
					x=s[1];
					for(int i:s[0]) ans[i]=t;
					trs.insert(trs.end(),s[0].begin(),s[0].end());
				}
			}

			int u=x.front();
			vector<int> c;
			for(int v:y){
				if((u&(1<<w)-1)==(v&(1<<w)-1)) c.push_back(v);
				else{
					ans[v]=t;
					trs.push_back(v);
				}
			}

			while(c.size()>1){
				vector<int> s[2];
				for(int i=0;i<c.size();i++) s[i&1].push_back(c[i]);
				vector<int> tmp=trs;
				tmp.insert(tmp.end(),s[1].begin(),s[1].end());
				if(Check(s[0],x,tmp,b,ans,val)){
					c=s[0];
					for(int i:s[1]) ans[i]=t;
					trs.insert(trs.end(),s[1].begin(),s[1].end());
				}else{
					c=s[1];
					for(int i:s[0]) ans[i]=t;
					trs.insert(trs.end(),s[0].begin(),s[0].end());
				}
			}

			int v=c.front();

			break ;
		}
	}

	return ans;
}