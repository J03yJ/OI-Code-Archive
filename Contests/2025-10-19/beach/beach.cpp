#include<bits/stdc++.h>

using namespace std;

ifstream fin("beach.in");
ofstream fout("beach.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using uint=unsigned int;
const int N=2e5+9;

char s[N];
int h[N],d[N],v[N],n,op;

mt19937 rng(4649);
struct Node{
	int lc,rc;
	uint prio;
	ll siz,sum;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define sum(x) tr[x].sum

int cnt;
inline int Allc(){return ++cnt;}
inline void PushUp(int x){
	siz(x)=siz(lc(x))+siz(rc(x));
	sum(x)=sum(lc(x))+sum(rc(x));
}
inline void Insert(int &x,int L,int R,int pos,ll k){
	if(!x) x=Allc();
	if(L==R) return siz(x)++,sum(x)+=k,void();
	int mid=L+R>>1;
	if(pos<=mid) Insert(lc(x),L,mid,pos,k);
	else Insert(rc(x),mid+1,R,pos,k);
	PushUp(x);
}
inline void Merge(int &x,int &y,int L,int R){
	if(!x||!y) return x=x|y,void();
	if(L==R){
		siz(x)+=siz(y);
		sum(x)+=sum(y);
		return ;
	}
	int mid=L+R>>1;
	Merge(lc(x),lc(y),L,mid),Merge(rc(x),rc(y),mid+1,R);
	PushUp(x);
}
inline ll GetCount(int x,int L,int R,int l,int r){
	if(!x) return 0;
	if(l<=L&&R<=r) return siz(x);
	int mid=L+R>>1;
	if(r<=mid) return GetCount(lc(x),L,mid,l,r);
	else if(l>mid) return GetCount(rc(x),mid+1,R,l,r);
	else return GetCount(lc(x),L,mid,l,r)+GetCount(rc(x),mid+1,R,l,r);
}
inline ll GetSum(int x,int L,int R,int l,int r){
	if(!x) return 0;
	if(l<=L&&R<=r) return sum(x);
	int mid=L+R>>1;
	if(r<=mid) return GetSum(lc(x),L,mid,l,r);
	else if(l>mid) return GetSum(rc(x),mid+1,R,l,r);
	else return GetSum(lc(x),L,mid,l,r)+GetSum(rc(x),mid+1,R,l,r);
}
inline void GetNode(int x,int L,int R,vector<array<ll,3>> &node){
	if(!x) return ;
	if(L==R) return node.push_back({L,siz(x),sum(x)}),void();
	int mid=L+R>>1;
	GetNode(lc(x),L,mid,node),GetNode(rc(x),mid+1,R,node);
}

int root[N],a[N];
vector<int> e[N];

ll ans;
inline void DFS(int x,int val){
	val=max(val,v[x]);
	if(x) Insert(root[x],1,n,h[x],d[x]);
	for(int y:e[x]){
		DFS(y,val);
		if(siz(root[x])>siz(root[y])) swap(root[x],root[y]);
		vector<array<ll,3>> node;
		GetNode(root[x],1,n,node);
		for(auto t:node){
			ans+=(t[2]*GetCount(root[y],1,n,t[0]-op,t[0]+op)+t[1]*GetSum(root[y],1,n,t[0]-op,t[0]+op))*val;
		}
		Merge(root[x],root[y],1,n);
	}
}

signed main(){
	cin>>n>>op;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;i<=n;i++) cin>>v[i];

	for(int i=2,j=0;i<=n;i++){
		while(j&&s[j+1]!=s[i]) j=a[j];
		if(s[j+1]==s[i]) j++;
		a[i]=j;
	}
	for(int i=1;i<=n;i++) e[a[i]].push_back(i);

	DFS(0,0);

	cout<<ans<<endl;

	return 0;
}