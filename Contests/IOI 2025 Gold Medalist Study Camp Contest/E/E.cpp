#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int lgN=2e1;
const int inf=1e9+7;

struct Node{
	int l,r,dat;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return tr[x].dat=-inf,void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline int Query(int x,int l,int r){
	if(l>r) return -inf;
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
}

vector<int> lq[N],rq[N];
int a[N],ql[N],qr[N],mx[lgN][N],rm[N],ans[N],n,q;
inline int Cmp(int i,int j){return a[i]>a[j]?i:j;}
inline void Init(){
	for(int i=1;i<=n;i++) mx[0][i]=i;
	for(int k=1;k<=__lg(n);k++){
		for(int i=1;i+(1<<k)-1<=n;i++){
			mx[k][i]=Cmp(mx[k-1][i],mx[k-1][i+(1<<k-1)]);
		}
	}
}
inline int MaxP(int l,int r){
	int k=__lg(r-l+1);
	return Cmp(mx[k][l],mx[k][r-(1<<k)+1]);
}

int f[N],g[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

	Init();
	for(int i=1;i<=q;i++){
		lq[ql[i]].push_back(i);
		rq[qr[i]].push_back(i);
		rm[i]=MaxP(ql[i],qr[i]);
	}

	Build(1,0,n);
	vector<int> stk;
	for(int i=1;i<=n;i++){
		f[i]=g[i]=1;
		int lst=0;
		while(stk.size()&&Cmp(i,stk.back())==i){
			f[i]=max(f[i],f[lst]+1);
			Set(1,stk.size()-1,-inf);
			lst=stk.back();
			stk.pop_back();
		}
		
		if(stk.size()){
			f[stk.back()]=max(f[stk.back()],f[lst]+1);
			g[stk.back()]=max(g[stk.back()],f[lst]+1);
			Set(1,stk.size()-1,f[stk.back()]+(stk.size()-1));
		}
		stk.push_back(i);
		Set(1,stk.size()-1,f[i]+(stk.size()-1));
		
		for(int j:rq[i]){
			ans[j]=max(ans[j],g[rm[j]]);
			int p=lower_bound(stk.begin(),stk.end(),rm[j])-stk.begin();
			ans[j]=max(ans[j],Query(1,p+1,stk.size()-1)-p);
		}
	}

	Build(1,0,n);
	stk.clear();
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	for(int i=n;i>=1;i--){
		f[i]=g[i]=1;
		int lst=0;
		while(stk.size()&&Cmp(i,stk.back())==i){
			f[i]=max(f[i],f[lst]+1);
			Set(1,stk.size()-1,-inf);
			lst=stk.back();
			stk.pop_back();
		}
		if(stk.size()){
			f[stk.back()]=max(f[stk.back()],f[lst]+1);
			g[stk.back()]=max(g[stk.back()],f[lst]+1);
			Set(1,stk.size()-1,f[stk.back()]+(stk.size()-1));
		}
		stk.push_back(i);
		Set(1,stk.size()-1,f[i]+(stk.size()-1));
		
		for(int j:lq[i]){
			ans[j]=max(ans[j],g[rm[j]]);
			int p=lower_bound(stk.begin(),stk.end(),rm[j],greater<int>())-stk.begin();
			ans[j]=max(ans[j],Query(1,p+1,stk.size()-1)-p);
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}