#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

struct Node{
	int lc,rc;
	ll siz,sum;
}tr[N*80];

int cnt;
inline int Allc(){return ++cnt;}
inline void PushUp(int x){
	tr[x].siz=tr[tr[x].lc].siz+tr[tr[x].rc].siz;
	tr[x].sum=tr[tr[x].lc].sum+tr[tr[x].rc].sum;
}

inline void Insert(int &x,int L,int R,int pos,int k){
	if(!x) x=Allc();
	if(L==R) return tr[x].siz+=k,tr[x].sum+=1ll*k*L,void();
	int mid=L+R>>1;
	if(pos<=mid) Insert(tr[x].lc,L,mid,pos,k);
	else Insert(tr[x].rc,mid+1,R,pos,k);
	PushUp(x);
}
inline ll PQuery(int x,int L,int R,ll k){
	if(!x) return 0;
	if(L==R) return min(tr[x].siz,k)*L;
	int mid=L+R>>1;
	if(k<=tr[tr[x].lc].siz) return PQuery(tr[x].lc,L,mid,k);
	else return PQuery(tr[x].rc,mid+1,R,k-tr[tr[x].lc].siz)+tr[tr[x].lc].sum;
}
inline ll SQuery(int x,int L,int R,ll k){
	if(!x) return 0;
	if(L==R) return min(tr[x].siz,k)*L;
	int mid=L+R>>1;
	if(k<=tr[tr[x].rc].siz) return SQuery(tr[x].rc,mid+1,R,k);
	else return SQuery(tr[x].lc,L,mid,k-tr[tr[x].rc].siz)+tr[tr[x].rc].sum;
}

int a[N],b[N],n,m,q,root;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>a[i],Insert(root,1,1e9,a[i],1);
	for(int i=1;i<=m;i++) cin>>b[i],Insert(root,1,1e9,b[i],1);

	while(q--){
		int t,i,x;
		cin>>t>>i>>x;
		if(t==1){
			Insert(root,1,1e9,a[i],-1);
			Insert(root,1,1e9,a[i]=x,1);
		}else{
			Insert(root,1,1e9,b[i],-1);
			Insert(root,1,1e9,b[i]=x,1);
		}

		cout<<PQuery(root,1,1e9,n>>1)+SQuery(root,1,1e9,n>>1)<<endl;
	}

	return 0;
}