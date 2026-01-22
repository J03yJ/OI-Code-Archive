#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;

int a[N],id[N],n,q,tot;
int fa[N],lc[N],rc[N];

ll tr[N];
inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}

inline void Build(){
	tot=n;
	queue<int> q;
	for(int i=1;i<=n;i++) q.push(i);
	while(q.size()>1){
		int x=q.front();
		q.pop();
		int y=q.front();
		q.pop();
		a[++tot]=min(a[x],a[y]);
		fa[x]=fa[y]=tot;
		lc[tot]=x,rc[tot]=y;
		id[tot]=tot-n;
		Add(id[tot],max(a[x],a[y]));
		q.push(tot);
	}
}
inline void F(int x,ll k){
	if(!x) return ;
	if(id[x]) Add(id[x],k*max(a[lc[x]],a[rc[x]]));
	F(fa[x],k);
}
inline void Upd(int x){
	if(!x) return ;
	if(lc[x]) a[x]=min(a[lc[x]],a[rc[x]]);
	Upd(fa[x]);
}
inline void M(int x,int k){
	F(x,-1);
	a[x]=k,Upd(x);
	F(x,1);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build();
	while(q--){
		char op;
		int x,y;
		cin>>op>>x>>y;
		if(op=='C'){
			int k1=a[x],k2=a[y];
			M(x,k2),M(y,k1);
		}else{
			cout<<Ask(x,y)<<endl;
		}
	}

	return 0;
}