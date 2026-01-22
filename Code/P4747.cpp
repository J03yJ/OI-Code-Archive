#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

int p[N],ql[N],qr[N],al[N],ar[N],n,q;
vector<int> qry[N];

struct Node{
	int l,r,dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat+=k,tr[x].tag+=k;}
inline void PushDown(int x){
	if(!tr[x].tag) return ;
	Push(x<<1,tr[x].tag);
	Push(x<<1|1,tr[x].tag);
	tr[x].tag=0;
}
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
inline int LFind(int x,int l,int r){
	if(tr[x].dat>0) return r+1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return LFind(x<<1,l,r);
	else if(l>mid) return LFind(x<<1|1,l,r);
	else{
		int res=LFind(x<<1,l,r);
		return res>r?LFind(x<<1|1,l,r):res;
	}
}
inline int RFind(int x,int l,int r){
	if(tr[x].dat>0) return l-1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return RFind(x<<1,l,r);
	else if(l>mid) return RFind(x<<1|1,l,r);
	else{
		int res=RFind(x<<1|1,l,r);
		return res<l?RFind(x<<1,l,r):res;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i],qry[qr[i]].push_back(i);

	Build(1,1,n);
	vector<int> mn,mx;
	priority_queue<array<int,2>> h;
	for(int i=1;i<=n;i++){
		if(i>1) Modify(1,1,i-1,-1);
		while(mn.size()&&p[i]<p[mn.back()]){
			int k=p[mn.back()]-p[i],r=mn.back();
			mn.pop_back();
			int l=mn.size()?mn.back()+1:1;
			Modify(1,l,r,k);
		}
		mn.push_back(i);
		while(mx.size()&&p[i]>p[mx.back()]){
			int k=p[i]-p[mx.back()],r=mx.back();
			mx.pop_back();
			int l=mx.size()?mx.back()+1:1;
			Modify(1,l,r,k);
		}
		mx.push_back(i);

		int pos=LFind(1,1,i);
		for(int j:qry[i]) h.push({ql[j],j});
		while(h.size()&&h.top()[0]>=pos){
			int j=h.top()[1],k=RFind(1,1,ql[j]);
			h.pop();
			al[j]=k,ar[j]=i;
		}
	}

	for(int i=1;i<=q;i++) cout<<al[i]<<' '<<ar[i]<<endl;

	return 0;
}