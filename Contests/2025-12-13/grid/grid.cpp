#include<bits/stdc++.h>

using namespace std;

ifstream fin("grid.in");
ofstream fout("grid.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e6+9;

using Data=array<int,2>;
struct Node{
	int tag;
	Data dat;
}tr[N<<2];
inline Data Merge(Data x,Data y){
	if(x[0]!=y[0]) return min(x,y);
	else return {x[0],x[1]+y[1]};
}
inline void PushUp(int x){tr[x].dat=Merge(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat[0]+=k,tr[x].tag+=k;}
inline void PushDown(int x){
	if(tr[x].tag){
		Push(x<<1,tr[x].tag);
		Push(x<<1|1,tr[x].tag);
		tr[x].tag=0;
	}
}
inline void Build(int x,int L,int R){
	tr[x].tag=0;
	if(L==R) return tr[x].dat={L,1},void();
	int mid=L+R>>1;
	Build(x<<1,L,mid),Build(x<<1|1,mid+1,R);
	PushUp(x);
}
inline void Modify(int x,int L,int R,int l,int r,int k){
	if(l>r) return ;
	if(l<=L&&R<=r) return Push(x,k);
	PushDown(x);
	int mid=L+R>>1;
	if(l<=mid) Modify(x<<1,L,mid,l,r,k);
	if(r>mid) Modify(x<<1|1,mid+1,R,l,r,k);
	PushUp(x);
}
inline void NoP(int x,int L,int R,int l,int r,int k){
	if(l>r) return ;
	if(l<=L&&R<=r) return Push(x,k);
	int mid=L+R>>1;
	if(l<=mid) NoP(x<<1,L,mid,l,r,k);
	if(r>mid) NoP(x<<1|1,mid+1,R,l,r,k);
}
inline void DownAll(int x,int L,int R){
	if(L==R) return ;
	PushDown(x);
	int mid=L+R>>1;
	DownAll(x<<1,L,mid),DownAll(x<<1|1,mid+1,R);
	PushUp(x);
}
inline Data Query(int x,int L,int R,int l,int r){
	if(l<=L&&R<=r) return tr[x].dat;
	PushDown(x);
	int mid=L+R>>1;
	if(r<=mid) return Query(x<<1,L,mid,l,r);
	else if(l>mid) return Query(x<<1|1,mid+1,R,l,r);
	else return Merge(Query(x<<1,L,mid,l,r),Query(x<<1|1,mid+1,R,l,r));
}

template<class T> struct DelHeap{
	priority_queue<T> p,q;
	inline void Insert(T x){p.push(x);}
	inline void Erase(T x){q.push(x);}
	inline T Top(){
		while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
		return p.top();
	}
	inline int Size(){return p.size()-q.size();}
	~DelHeap(){
		while(p.size()) p.pop();
		while(q.size()) q.pop();
	}
};

int n,m,q;
vector<vector<int>> a;
vector<DelHeap<int>> rs,cs;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
inline void Solve(){
	cin>>n>>m>>q;
	a.resize(n+1);
	for(auto &v:a) v.resize(m+1,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	int lim=n*m;
	Build(1,1,lim);
	NoP(1,1,lim,1,lim,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k:{0,1,2,3}){
				int p=i+dx[k],q=j+dy[k];
				if(p<1||q<1||p>n||q>m) continue ;
				if(a[i][j]<a[p][q]) continue ;
				NoP(1,1,lim,a[i][j],lim,-1);
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int tmp=0;
			for(int p:{0,1}) for(int q:{0,1}) tmp=max(tmp,a[i+p][j+q]);
			NoP(1,1,lim,tmp,lim,1);
		}
	}
	rs.resize(n+1),cs.resize(m+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			rs[i].Insert(-a[i][j]);
			cs[j].Insert(-a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			NoP(1,1,lim,a[i][j],a[i][j+1]-1,1);
		}
		NoP(1,1,lim,a[i][m],lim,1);
		NoP(1,1,lim,-rs[i].Top(),lim,-1);
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<n;i++){
			NoP(1,1,lim,a[i][j],a[i+1][j]-1,1);
		}
		NoP(1,1,lim,a[n][j],lim,1);
		NoP(1,1,lim,-cs[j].Top(),lim,-1);
	}
	DownAll(1,1,lim);

	auto Rep=[&](int i,int j,int t){
		int o=max(a[i][j],t);
		for(int k:{0,1,2,3}){
			int p=i+dx[k],q=j+dy[k];
			if(p<1||q<1||p>n||q>m) continue ;
			if(max(a[i][j],a[p][q])<=o) Modify(1,1,lim,max(a[i][j],a[p][q]),lim,1);
		}
		for(int p:{-1,0}){
			for(int q:{-1,0}){
				if(i+p<1||j+q<1||i+p+1>n||j+q+1>m) continue ;
				int tmp=0;
				for(int s:{0,1}) for(int t:{0,1}) tmp=max(tmp,a[i+p+s][j+q+t]);
				if(tmp<=o) Modify(1,1,lim,tmp,lim,-1);
			}
		}
		
		if(i>1) Modify(1,1,lim,a[i-1][j],a[i][j]-1,-1);
		if(i<n) Modify(1,1,lim,a[i][j],a[i+1][j]-1,-1);
		else Modify(1,1,lim,a[i][j],lim,-1);
		if(j>1) Modify(1,1,lim,a[i][j-1],a[i][j]-1,-1);
		if(j<m) Modify(1,1,lim,a[i][j],a[i][j+1]-1,-1);
		else Modify(1,1,lim,a[i][j],lim,-1);
		Modify(1,1,lim,-rs[i].Top(),lim,1);
		Modify(1,1,lim,-cs[j].Top(),lim,1);

		rs[i].Erase(-a[i][j]);
		cs[j].Erase(-a[i][j]);

		a[i][j]=t;

		rs[i].Insert(-a[i][j]);
		cs[j].Insert(-a[i][j]);

		for(int k:{0,1,2,3}){
			int p=i+dx[k],q=j+dy[k];
			if(p<1||q<1||p>n||q>m) continue ;
			if(max(a[i][j],a[p][q])<=o) Modify(1,1,lim,max(a[i][j],a[p][q]),lim,-1);
		}
		for(int p:{-1,0}){
			for(int q:{-1,0}){
				if(i+p<1||j+q<1||i+p+1>n||j+q+1>m) continue ;
				int tmp=0;
				for(int s:{0,1}) for(int t:{0,1}) tmp=max(tmp,a[i+p+s][j+q+t]);
				if(tmp<=o) Modify(1,1,lim,tmp,lim,1);
			}
		}

		if(i>1) Modify(1,1,lim,a[i-1][j],a[i][j]-1,1);
		if(i<n) Modify(1,1,lim,a[i][j],a[i+1][j]-1,1);
		else Modify(1,1,lim,a[i][j],lim,1);
		if(j>1) Modify(1,1,lim,a[i][j-1],a[i][j]-1,1);
		if(j<m) Modify(1,1,lim,a[i][j],a[i][j+1]-1,1);
		else Modify(1,1,lim,a[i][j],lim,1);
		Modify(1,1,lim,-rs[i].Top(),lim,-1);
		Modify(1,1,lim,-cs[j].Top(),lim,-1);
	};
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			int k1=a[x1][y1],k2=a[x2][y2];
			if(k1==k2) continue ;
			Rep(x1,y1,k2);
			Rep(x2,y2,k1);
		}else{
			int l,r;
			cin>>l>>r;
			auto res=Query(1,1,lim,l,r);
			cout<<(res[0]==2?res[1]:0)<<endl;
		}
	}

	rs.clear(),cs.clear();
}

signed main(){
	int Tid,T;
	cin>>Tid>>T;
	while(T--) Solve();

	return 0;
}