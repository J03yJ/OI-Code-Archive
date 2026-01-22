#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;

ll a[N];
int typ[N],n,q;

struct Node{
	int son[2],fa,typ;
	ll siz,vsiz;
}tr[N];

inline void PushUp(int x){tr[x].siz=a[x]+tr[tr[x].son[0]].siz+tr[tr[x].son[1]].siz+tr[x].vsiz;}
inline bool IsRoot(int x){return x!=tr[tr[x].fa].son[0]&&x!=tr[tr[x].fa].son[1];}
inline bool Id(int x){return x==tr[tr[x].fa].son[1];}

inline void Rotate(int x){
	int y=tr[x].fa,z=tr[y].fa,f=Id(x);
	if(!IsRoot(y)) tr[z].son[Id(y)]=x;
	tr[y].son[f]=tr[x].son[!f],tr[tr[x].son[!f]].fa=y,PushUp(y);
	tr[x].son[!f]=y,tr[y].fa=x,PushUp(x);
	tr[x].fa=z;
}
inline void Splay(int x){
	for(int y=tr[x].fa;!IsRoot(x);Rotate(x),y=tr[x].fa){
		if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
	}
}

ll ans;
vector<int> e[N];
inline void DFS(int x,int fa){
	tr[x].vsiz=0;
	ll mx=a[x];int hson=0;
	for(int y:e[x]){
		if(y==fa) continue ;
		tr[y].fa=x;
		DFS(y,x);
		tr[x].vsiz+=tr[y].siz;
		if(tr[y].siz>mx) mx=tr[y].siz,hson=y;
	}
	tr[x].siz=tr[x].vsiz+a[x];
	if(mx*2>tr[x].siz){
		ans+=(tr[x].siz-mx)*2;
		if(hson){
			tr[x].vsiz-=tr[hson].siz;
			tr[x].son[1]=hson;
			typ[x]=0;
		}else typ[x]=1;
	}else ans+=tr[x].siz-1,typ[x]=2;
}
inline void Access(int x,int k){
	int p=0;
	while(x){
		Splay(x);
		
		ll sum=tr[x].siz-tr[tr[x].son[0]].siz;
		if(typ[x]==0) ans-=(sum-tr[tr[x].son[1]].siz)*2;
		else if(typ[x]==1) ans-=(sum-a[x])*2;
		else if(typ[x]==2) ans-=sum-1;
		
		if(p) tr[x].vsiz+=k;
		else a[x]+=k;
		PushUp(x);

		sum=tr[x].siz-tr[tr[x].son[0]].siz;
		if(2*tr[p].siz>sum){
			tr[x].vsiz+=tr[tr[x].son[1]].siz;
			tr[x].son[1]=p;
			tr[x].vsiz-=tr[tr[x].son[1]].siz;
		}
		if(2*tr[tr[x].son[1]].siz>sum) ans+=(sum-tr[tr[x].son[1]].siz)*2,typ[x]=0;
		else{
			if(tr[x].son[1]){
				tr[x].vsiz+=tr[tr[x].son[1]].siz;
				tr[x].son[1]=0;
			}
			if(2*a[x]>sum) ans+=(sum-a[x])*2,typ[x]=1;
			else ans+=sum-1,typ[x]=2;
		}

		p=x,x=tr[x].fa;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	DFS(1,-1);
	cout<<ans<<endl;
	while(q--){
		int x,k;
		cin>>x>>k;
		Access(x,k);
		cout<<ans<<endl;
	}

	return 0;
}