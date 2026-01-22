#include<bits/stdc++.h>

using namespace std;

ifstream fin("array.in");
ofstream fout("array.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

struct Node{
	int l,r;
	int dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat+=k,tr[x].tag+=k;}
inline void PushDown(int x){if(tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=0;}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline int Query(int x,int pos){
	if(tr[x].l==tr[x].r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos);
}
inline int Find(int x,int k){
	if(tr[x].l==tr[x].r) return tr[x].l-(tr[x].dat<k);
	PushDown(x);
	if(tr[x<<1].dat<k) return Find(x<<1,k);
	else return Find(x<<1|1,k);
}

int a[N],ql[N],qr[N],ans[N],n,q;
vector<int> qry[N];

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		ql[i]=1+ql[i],qr[i]=n-qr[i];
		if(ql[i]>qr[i]) continue ;
		qry[qr[i]].push_back(i);
	}

	Build(1,1,n);
	for(int i=1;i<=n;i++){
		if(a[i]<=i){
			int pos=min(Find(1,i-a[i]),i);
			if(pos) Modify(1,1,pos,1);
		}
		for(int j:qry[i]) ans[j]=Query(1,ql[j]);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}