#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
const int lgN=2e1;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

vector<int> e[N];
int fa[N],c[N],cnt[N],w[N],root[N],n,ans,fk,all;

struct Node{
	int lc,rc,siz,f,g;
}tr[N<<5];

int tot;
inline int Allc(){return ++tot;}
inline void Clear(){
	for(int x=1;x<=tot;x++) tr[x].lc=tr[x].rc=tr[x].f=tr[x].g=tr[x].siz=0;
	tot=0;
}
inline void PushUp(int x){
	tr[x].f=Add(tr[tr[x].lc].f,tr[tr[x].rc].f);
	tr[x].g=Add(tr[tr[x].lc].g,tr[tr[x].rc].g);
}
inline void Insert(int &x,int L,int R,int k){
	if(!x) x=Allc();
	if(L==R){
		tr[x].siz++;
		tr[x].f=w[tr[x].siz];
		tr[x].g=Sub(w[cnt[L]],w[cnt[L]-tr[x].siz]);
		return ;
	}
	int mid=L+R>>1;
	if(k<=mid) Insert(tr[x].lc,L,mid,k);
	else Insert(tr[x].rc,mid+1,R,k);
	PushUp(x);
}
inline void Merge(int &x,int y,int L,int R){
	if(!x||!y) return x|=y,void();
	if(L==R){
		tr[x].siz+=tr[y].siz;
		tr[x].f=w[tr[x].siz];
		tr[x].g=Sub(w[cnt[L]],w[cnt[L]-tr[x].siz]);
		return ;
	}
	int mid=L+R>>1;
	Merge(tr[x].lc,tr[y].lc,L,mid);
	Merge(tr[x].rc,tr[y].rc,mid+1,R);
	PushUp(x);
}
inline int Query(int x,int L,int R,int k){
	if(!x) return 0;
	if(L==R) return tr[x].siz;
	int mid=L+R>>1;
	if(k<=mid) return Query(tr[x].lc,L,mid,k);
	else return Query(tr[x].rc,mid+1,R,k);
}

inline void DFS(int x){
	int sum=0,tmp=0,ss=0;
	Insert(root[x],1,n,c[x]);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		SubAs(tmp,tr[root[y]].f);
		AddAs(fk,Mul(tr[root[y]].f,sum));
		AddAs(sum,tr[root[y]].f);
		Merge(root[x],root[y],1,n);
	}
	AddAs(tmp,tr[root[x]].f);
	AddAs(ans,Mul(tmp,Sub(all,tr[root[x]].g)));
	// cout<<"# "<<x<<" : "<<tr[root[x]].f<<' '<<Sub(all,tr[root[x]].g)<<' '<<all<<' '<<tmp<<endl;
	// cout<<" -> ";for(int i=1;i<=n;i++) cout<<Query(root[x],1,n,i)<<' ';cout<<endl;
	// cout<<" -> ";cout<<ans<<' '<<fk<<endl;
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i],cnt[c[i]]++;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int i=1;i<=n;i++) w[i]=Sub(QPow(2,i),1);
	for(int i=1;i<=n;i++) AddAs(all,w[cnt[i]]);

	DFS(1);

	SubAs(ans,fk);
	MulAs(ans,2);

	cout<<ans<<endl;
	
	all=ans=fk=0;
	for(int i=1;i<=n;i++){
		c[i]=cnt[i]=w[i]=root[i]=fa[i]=0;
		e[i].clear();
	}
	Clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}