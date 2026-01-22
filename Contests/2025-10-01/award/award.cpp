#include<bits/stdc++.h>

using namespace std;

ifstream fin("award.in");
ofstream fout("award.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;
const int lgN=2e1;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int elr[N<<1],pos[N],dep[N],fa[N],ecnt;
inline void GetElr(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetElr(y);
		elr[++ecnt]=x;
	}
}
int mn[N<<1][lgN],lg[N<<1],a[N],n,m;
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=lg[y-x+1];
	return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
}
inline int Dist(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}
inline int T(int x,int y){return Dist(x,y)+a[x]+a[y];}

struct Node{
	int l,r;
	array<int,2> p;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define p(x) tr[x].p

inline void PushUp(int x){
	p(x)=p(x<<1);
	vector<int> tmp({p(x<<1)[0],p(x<<1)[1],p(x<<1|1)[0],p(x<<1|1)[1]});
	for(int i=0;i<4;i++){
		for(int j=i+1;j<4;j++){
			if(T(tmp[i],tmp[j])>T(p(x)[0],p(x)[1])) p(x)={tmp[i],tmp[j]};
		}
	}
}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return p(x)={l(x),r(x)},void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Update(int x,int pos,int k){
	if(l(x)==r(x)) return a[l(x)]=k,void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) Update(x<<1,pos,k);
	else Update(x<<1|1,pos,k);
	PushUp(x);
}
inline int Query(){
	int x=p(1)[0],y=p(1)[1];
	return max(T(x,y)+1>>1,max(a[x],a[y]));
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}

	GetElr(1);
	InitLCA();
	Build(1,1,n);

	cin>>m;
	while(m--){
		int x,y;
		cin>>x>>y;
		Update(1,x,y);
		cout<<Query()<<endl;
	}

	return 0;
}