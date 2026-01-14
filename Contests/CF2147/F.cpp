#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

#define F(x) (1ll*(x)*((x)+1)/2)
struct Data{
	ll len,llen,rlen,ans;
	Data(){len=llen=rlen=ans=0;}
	Data(int _len,bool f){
		len=_len;
		if(f) llen=rlen=len,ans=F(len);
		else llen=rlen=ans=0;
	}
	inline friend Data operator +(Data x,Data y){
		Data res;
		res.len=x.len+y.len;
		res.llen=(x.llen==x.len?x.len+y.llen:x.llen);
		res.rlen=(y.rlen==y.len?y.len+x.rlen:y.rlen);
		res.ans=x.ans+y.ans-F(x.rlen)-F(y.llen)+F(x.rlen+y.llen);
		return res;
	}
};
struct Node{
	int lc,rc,tag;
	Data dat;
}tr[N<<4];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

int cnt=0;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void Clear(int c=0){while(cnt>c) memset(&tr[cnt--],0,sizeof Node());}
inline void PushUp(int x){dat(x)=tag(x)?Data(dat(x).len,1):dat(lc(x))+dat(rc(x));}
inline void Push(int x){tag(x)=1,dat(x)=Data(dat(x).len,1);}
inline void Build(int &x,int L,int R){
	x=Allc();
	if(L==R) return dat(x)=Data(1,0),void();
	int mid=L+R>>1;
	Build(lc(x),L,mid),Build(rc(x),mid+1,R);
	PushUp(x);
}
inline void PushSeg(int &x,int L,int R,int l,int r){
	x=Clone(x);
	if(l<=L&&R<=r) return Push(x),void();
	int mid=L+R>>1;
	if(l<=mid) PushSeg(lc(x),L,mid,l,r);
	if(r>mid) PushSeg(rc(x),mid+1,R,l,r);
	PushUp(x);
}

int p[N],s[N],ip[N],is[N],n,q;
vector<array<int,2>> seg[N<<2];
inline void Insert(int x,int L,int R,int l,int r,array<int,2> k){
	if(l<=L&&R<=r) return seg[x].push_back(k),void();
	int mid=L+R>>1;
	if(l<=mid) Insert(x<<1,L,mid,l,r,k);
	if(r>mid) Insert(x<<1|1,mid+1,R,l,r,k);
}
ll ans[N];
inline void Solve(int x,int L,int R,int lstroot=0){
	int root=lstroot;
	if(x==1) Build(root,1,n);
	for(auto t:seg[x]) PushSeg(root,1,n,t[0],t[1]);
	if(L==R){
		ans[L]=dat(root).ans;
		return ;
	}
	int mid=L+R>>1;
	Solve(x<<1,L,mid,root);
	Solve(x<<1|1,mid+1,R,root);
	seg[x].clear();
}
set<array<int,2>> pmt;
map<array<int,2>,int> tmp;
inline void Add(int T,int s,int t){
	if(!s||!t) return ;
	if(s>t) return ;
	if(tmp[{s,t-1}]) return ;
	tmp[{s,t-1}]=T+1;
	pmt.insert({s,t-1});
}
inline void Del(int T,int s,int t){
	if(!s||!t) return ;
	if(s>t) return ;
	if(!tmp[{s,t-1}]) return ;
	Insert(1,0,q,tmp[{s,t-1}]-1,T,{s,t-1});
	tmp[{s,t-1}]=0;
	pmt.erase({s,t-1});
}
inline void Clr(){
	for(auto t:pmt) Insert(1,0,q,tmp[t]-1,q,t);
	pmt.clear();
	tmp.clear();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++) cin>>ip[i],p[ip[i]]=i;
		for(int i=1;i<=n;i++) cin>>is[i],s[is[i]]=i;

		for(int i=1;i<=n;i++) Add(0,ip[s[i]],ip[s[i-1]]);
		for(int i=1;i<=q;i++){
			int typ,u,v;
			cin>>typ>>u>>v;
			if(typ==1){
				u=ip[u],v=ip[v];
				Del(i,ip[s[is[p[u]]]],ip[s[is[p[u]]-1]]);
				Del(i,ip[s[is[p[u]]+1]],ip[s[is[p[u]]]]);
				Del(i,ip[s[is[p[v]]]],ip[s[is[p[v]]-1]]);
				Del(i,ip[s[is[p[v]]+1]],ip[s[is[p[v]]]]);
				swap(ip[p[u]],ip[p[v]]);
				swap(p[u],p[v]);
				Add(i,ip[s[is[p[u]]]],ip[s[is[p[u]]-1]]);
				Add(i,ip[s[is[p[u]]+1]],ip[s[is[p[u]]]]);
				Add(i,ip[s[is[p[v]]]],ip[s[is[p[v]]-1]]);
				Add(i,ip[s[is[p[v]]+1]],ip[s[is[p[v]]]]);
			}else if(typ==2){
				u=is[u],v=is[v];
				Del(i-1,ip[s[u]],ip[s[u-1]]);
				Del(i-1,ip[s[u+1]],ip[s[u]]);
				Del(i-1,ip[s[v]],ip[s[v-1]]);
				Del(i-1,ip[s[v+1]],ip[s[v]]);
				swap(is[s[u]],is[s[v]]);
				swap(s[u],s[v]);
				Add(i,ip[s[u]],ip[s[u-1]]);
				Add(i,ip[s[u+1]],ip[s[u]]);
				Add(i,ip[s[v]],ip[s[v-1]]);
				Add(i,ip[s[v+1]],ip[s[v]]);
			}
		}
		Clr();

		Solve(1,0,q);
		for(int i=1;i<=q;i++) cout<<1ll*n*(n+1)/2+ans[i]<<endl;

		Clear();
		cerr<<" : "<<endl;
	}

	return 0;
}