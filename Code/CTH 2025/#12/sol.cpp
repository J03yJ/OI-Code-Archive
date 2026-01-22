#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int inf=1e9+7;

ll ans[N];
int op[N],w[N],t[N],n,q,tot;
vector<array<int,2>> opr[N];
vector<int> qry[N],val;

struct SgT{
	struct Node{
		int l,r;
		ll mn,sum;
	}tr[N<<2];

	inline ll Calc(int x,int k){
		if(k<=tr[x].mn) return 0;
		if(tr[x].l==tr[x].r) return w[tr[x].mn];
		if(k<=tr[x<<1|1].mn) return Calc(x<<1,k);
		else return Calc(x<<1|1,k)+tr[x].sum-tr[x<<1|1].sum;
	}
	inline void PushUp(int x){
		tr[x].mn=min(tr[x<<1].mn,tr[x<<1|1].mn);
		tr[x].sum=tr[x<<1|1].sum+Calc(x<<1,tr[x<<1|1].mn);
	}
	inline void Build(int x,int l,int r){
		tr[x].l=l,tr[x].r=r;
		if(tr[x].l==tr[x].r) return tr[x].mn=q+1,void();
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Set(int x,int pos,int k){
		if(tr[x].l==tr[x].r) return tr[x].mn=k,tr[x].sum=w[k],void();
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) Set(x<<1,pos,k);
		else Set(x<<1|1,pos,k);
		PushUp(x);
	}
	inline array<ll,2> Prefix(int x,int pos,ll k){
		if(pos<tr[x].l) return {0,q+1};
		if(tr[x].l==tr[x].r) return {Calc(x,k),min(k,tr[x].mn)};
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) return Prefix(x<<1,pos,k);
		else{
			auto res=Prefix(x<<1|1,pos,k);
			return {res[0]+Calc(x<<1,res[1]),min(res[1],tr[x<<1].mn)};
		}
	}
}T,R;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1,l,r,x;i<=q;i++){
		cin>>op[i];
		if(op[i]==1){
			cin>>l>>r>>w[i];
			opr[l].push_back({w[i],i});
			opr[r+1].push_back({w[i],q+1});
		}else{
			cin>>x>>w[i];
			qry[x].push_back(i);
		}
		val.push_back(w[i]);
	}

	val.push_back(0);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	tot=val.size()-1;
	
	w[q+1]=inf;
	T.Build(1,1,tot);
	R.Build(1,1,tot);
	for(int i=1;i<=tot;i++) t[i]=q+1;
	for(int i=1;i<=n;i++){
		for(auto p:opr[i]){
			p[0]=lower_bound(val.begin(),val.end(),p[0])-val.begin();
			T.Set(1,p[0],p[1]);
			R.Set(1,tot-p[0]+1,p[1]);
			t[p[0]]=p[1]+1;
		}
		for(int j:qry[i]){
			int p=lower_bound(val.begin(),val.end(),w[j])-val.begin();
			ans[j]=T.Prefix(1,p,min(j,t[p]))[0]+R.Prefix(1,tot-p,min(j,t[p]))[0];
		}
	}

	for(int i=1;i<=q;i++) if(op[i]==2) cout<<ans[i]<<endl;

	return 0;
}