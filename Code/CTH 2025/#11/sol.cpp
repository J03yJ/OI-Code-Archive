#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int lgN=2e1;
const int inf=2e9;

int a[N],mn[lgN][N],n,q;
inline void InitRMQ(){
	for(int i=1;i<=n;i++) mn[0][i]=a[i];
	for(int k=1;k<=__lg(n);k++){
		for(int i=1;i+(1<<k)-1<=n;i++){
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
		}
	}
}
inline int Min(int l,int r){
	if(l>r) return inf;
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}

struct Node{
	int lc,rc,dat;
}tr[N<<7];

int root[N],cnt;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void PushUp(int x){tr[x].dat=tr[tr[x].lc].dat+tr[tr[x].rc].dat;}
inline void Modify(int &x,int L,int R,int pos,int k){
	x=Clone(x);
	if(L==R) return tr[x].dat+=k,void();
	int mid=ll(L)+R>>1;
	if(pos<=mid) Modify(tr[x].lc,L,mid,pos,k);
	else Modify(tr[x].rc,mid+1,R,pos,k);
	PushUp(x);
}
inline int Query(int x,int L,int R,int l,int r){
	if(!x) return 0;
	if(l<=L&&R<=r) return tr[x].dat;
	int mid=ll(L)+R>>1,ans=0;
	if(l<=mid) ans+=Query(tr[x].lc,L,mid,l,r);
	if(r>mid) ans+=Query(tr[x].rc,mid+1,R,l,r);
	return ans;
}

inline int LApr(int p,int k){
	int l=p-1,r=n+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(Min(p,mid)<=k) r=mid;
		else l=mid;
	}
	return r;
}
inline int RApr(int p,int k){
	int l=0,r=p+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(Min(mid,p)<=k) l=mid;
		else r=mid;
	}
	return l;
}
inline int Count(int l,int r,int w){
	int lp=LApr(l,w>>1),rp=RApr(r,w>>1),ans=0;
	if(lp>r||rp<l) return ans;
	ans+=Query(root[rp],0,inf,0,w)-Query(root[lp],0,inf,0,w)+1;
	ans+=(ll(min(Min(l,lp-1),Min(rp+1,r)))+max(a[lp],a[rp])<=w);
	return ans;
}
inline int Calc(int l,int r,int k){
	int L=-1,R=inf+1;
	while(L+1<R){
		int mid=ll(L)+R>>1;
		if(Count(l,r,mid)>=k) R=mid;
		else L=mid;
	}
	return R;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	InitRMQ();
	vector<int> stk;
	for(int i=1;i<=n;i++){
		Modify(root[i]=root[i-1],0,inf,a[i]<<1,1);
		while(stk.size()&&a[stk.back()]>=a[i]){
			if(stk.size()>1){
				int j=stk.end()[-1],k=stk.end()[-2];
				Modify(root[i],0,inf,a[j]+max(a[i],a[k]),1);
				Modify(root[i],0,inf,a[j]<<1,-1);
			}
			stk.pop_back();
		}
		stk.push_back(i);
	}

	while(q--){
		int l,r,k;
		cin>>l>>r>>k;
		cout<<Calc(l,r,k)<<endl;
	}
	
	return 0;
}