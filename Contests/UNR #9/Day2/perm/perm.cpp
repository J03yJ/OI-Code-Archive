#include<bits/stdc++.h>
#include"perm.h"

using namespace std;

vector<bool> query(const vector<int> &);
inline vector<int> Solve1(int);
inline vector<int> Solve2(int);
vector<int> solve(int n,int Tid){
	if(n==1e3) return Solve1(n);
	else return Solve2(n);
}

inline vector<int> GetAns(int n,auto &nxt){
	vector<int> vis(n+1,0);
	vector<int> p;
	int pos=1;
	do{
		p.push_back(pos);
		vis[pos]=1;
		if(vis[nxt[pos][0]]&&vis[nxt[pos][1]]) break ;
		pos=nxt[pos][vis[nxt[pos][0]]];
	}while(pos!=1);
	return p;
}
inline vector<int> Solve1(int n){
	vector<int> tmp;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++) tmp.insert(tmp.end(),{i,j,i,j});
	}

	vector<vector<int>> nxt(n+1,vector<int>());
	vector<bool> res=query(tmp);
	for(int i=1,cnt=0;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(res[cnt++<<2|1]){
				nxt[i].push_back(j);
				nxt[j].push_back(i);
			}
		}
	}
	return GetAns(n,nxt);
}

inline void Work(int l,int r,auto &v,auto &nxt){
	if(!v.size()) return ;
	// cerr<<l<<' '<<r<<endl;
	cout<<l<<' '<<r<<' '<<v.size()<<endl;
	// for(int i:v) cout<<i<<' ';cout<<endl;
	if(l==r){
		for(int i:v) nxt[i].push_back(l),cout<<i<<" <-> "<<l<<endl;
		// assert(v.size()==2);
		return ;
	}
	int mid=l+r>>1,llen=mid-l+1,rlen=r-mid;
	vector<int> lq,rq;
	for(int i=l;i<=mid;i++) lq.push_back(i);
	for(int i:v) lq.insert(lq.end(),{i,i});
	for(int i=l;i<=mid;i++) lq.push_back(i);
	for(int i=mid+1;i<=r;i++) rq.push_back(i);
	for(int i:v) rq.insert(rq.end(),{i,i});
	for(int i=mid+1;i<=r;i++) rq.push_back(i);
	cout<<l<<" ~ "<<mid<<endl;
	vector<bool> lres=query(lq);
	cout<<mid+1<<" ~ "<<r<<endl;
	vector<bool> rres=query(rq);
	vector<int> lv,rv;
	for(int i=0;i<v.size();i++){
		if(lres[llen+(i<<1)+1]) lv.push_back(v[i]);
		if(rres[rlen+(i<<1)+1]) rv.push_back(v[i]);
	}
	v.clear();
	Work(l,mid,lv,nxt),Work(mid+1,r,rv,nxt);
}
inline vector<int> Solve2(int n){
	vector<vector<int>> nxt(n+1,vector<int>());
	vector<int> v(n);
	iota(v.begin(),v.end(),1);
	Work(1,n,v,nxt);
	return GetAns(n,nxt);
}