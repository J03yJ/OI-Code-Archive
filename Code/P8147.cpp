#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;
const int L=5e5+9;
const int V=1e3;
const int lgL=2e1;

namespace PSgT{
	struct Node{
		int lc,rc,siz;
	}tr[N<<5];
	int cnt;
	inline int Allc(){return ++cnt;}
	inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
	inline void PushUp(int x){tr[x].siz=tr[tr[x].lc].siz+tr[tr[x].rc].siz;}
	inline void Insert(int &x,int L,int R,int pos){
		x=Clone(x);
		if(L==R) return tr[x].siz++,void();
		int mid=L+R>>1;
		if(pos<=mid) Insert(tr[x].lc,L,mid,pos);
		else Insert(tr[x].rc,mid+1,R,pos);
		PushUp(x);
	}
	inline int Query(int x,int L,int R,int l,int r){
		if(!x) return 0;
		if(l<=L&&R<=r) return tr[x].siz;
		int mid=L+R>>1;
		if(r<=mid) return Query(tr[x].lc,L,mid,l,r);
		else if(l>mid) return Query(tr[x].rc,mid+1,R,l,r);
		else return Query(tr[x].lc,L,mid,l,r)+Query(tr[x].rc,mid+1,R,l,r);
	}
}
namespace ACAM{
	struct Node{
		int son[4],fail,t;
		vector<int> ed;
	}tr[L];

	int cnt,root;
	inline int Allc(){return ++cnt;}
	inline void Insert(string &s,int val){
		int x=root;
		for(auto c:s){
			if(!tr[x].son[c-'a']) tr[x].son[c-'a']=Allc();
			x=tr[x].son[c-'a'];
		}
		tr[x].ed.push_back(val);
	}
	inline void GetFail(){
		queue<int> q;
		for(int i:{0,1,2,3}){
			if(!tr[root].son[i]) continue ;
			tr[tr[root].son[i]].fail=root;
			q.push(tr[root].son[i]);
		}
		while(q.size()){
			int x=q.front();
			q.pop();
			tr[x].t=tr[tr[x].fail].t;
			for(int val:tr[x].ed) PSgT::Insert(tr[x].t,1,V,val);
			for(int i:{0,1,2,3}){
				if(tr[x].son[i]){
					tr[tr[x].son[i]].fail=tr[tr[x].fail].son[i];
					q.push(tr[x].son[i]);
				}else tr[x].son[i]=tr[tr[x].fail].son[i];
			}
		}
	}

	vector<int> to[L];
	int elr[L<<1],pos[L],sop[L],ecnt;
	inline void GetElr(int x){
		elr[++ecnt]=x;
		pos[x]=ecnt;
		for(int y:to[x]){
			GetElr(y);
			elr[++ecnt]=x;
		}
		sop[x]=ecnt;
	}
	int mn[L<<1][lgL+1],lg[L<<1];
	inline void InitLCA(){
		for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
		for(int k=1;k<=lg[ecnt];k++){
			for(int i=1;i<=ecnt-(1<<k)+1;i++){
				mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
			}
		}
	}
	inline int LCA(int x,int y){
		x=pos[x],y=pos[y];
		if(x>y) swap(x,y);
		int k=lg[y-x+1];
		return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
	}
	inline void InitTree(){
		for(int i=1;i<=cnt;i++) to[tr[i].fail].push_back(i);
		GetElr(0);
		InitLCA();
	}

	inline int Query(string s,int k){
		vector<int> p;
		int x=root;
		for(char c:s){
			p.push_back(x);
			x=tr[x].son[c-'a'];
		}
		p.push_back(x);

		int c=p.size();
		sort(p.begin(),p.end(),[](int i,int j){return pos[i]<pos[j];});
		vector<int> q(p);
		for(int &x:q) x=pos[x];
		p.erase(unique(p.begin(),p.end()),p.end());
		for(int i=1;i<c;i++) p.push_back(LCA(p[i-1],p[i]));
		sort(p.begin(),p.end(),[](int i,int j){return pos[i]<pos[j];});
		p.erase(unique(p.begin(),p.end()),p.end());
		auto Count=[&](int mid){
			int ans=0;
			for(int i=1;i<p.size();i++){
				int x=p[i],f=LCA(p[i-1],p[i]);
				int cnt=upper_bound(q.begin(),q.end(),sop[x])-lower_bound(q.begin(),q.end(),pos[x]);
				int trg=(mid+cnt-1)/cnt;
				if(trg>V) continue ;
				ans+=PSgT::Query(tr[x].t,1,V,trg,V)-PSgT::Query(tr[f].t,1,V,trg,V);
			}
			return ans;
		};

		int l=0,r=1e9;
		while(l+1<r){
			int mid=l+r>>1;
			if(Count(mid)>=k) l=mid;
			else r=mid;
		}

		return l;
	}
}

string s[N];
int val[N],n,q;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>s[i]>>val[i];

	for(int i=1;i<=n;i++) ACAM::Insert(s[i],val[i]);
	ACAM::GetFail();
	ACAM::InitTree();

	while(q--){
		string t;int k;
		cin>>t>>k;
		cout<<ACAM::Query(t,k)<<endl;
	}

	return 0;
}