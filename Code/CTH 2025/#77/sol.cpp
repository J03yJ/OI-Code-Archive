#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e4+9;
const int V=1e9;
const ll inf=1e18,hnf=1e12;

int a[N],n,q;

struct Node{
	int l,r;
	vector<ll> f[2][2],df[2][2];
}tr[N<<2];

inline vector<ll> Shift(vector<ll> f,int k){
	f.erase(f.begin(),f.begin()+k);
	return f;
}
inline vector<ll> Merge(vector<ll> f,vector<ll> g){
	adjacent_difference(f.begin(),f.end(),f.begin());
	adjacent_difference(g.begin(),g.end(),g.begin());
	vector<ll> h(f.size()+g.size()-1);
	h[0]=f[0]+g[0];
	merge(f.begin()+1,f.end(),g.begin()+1,g.end(),h.begin()+1,greater<ll>());
	for(int i=1;i<h.size();i++) h[i]+=h[i-1];
	return h;
}
inline void ChMax(vector<ll> &f,vector<ll> g){
	int len=max(f.size(),g.size());
	f.resize(len,LLONG_MIN);
	g.resize(len,LLONG_MIN);
	for(int i=0;i<len;i++) f[i]=max(f[i],g[i]);
}

inline void DF(int x){
	for(int i:{0,1}){
		for(int j:{0,1}){
			tr[x].df[i][j].resize(tr[x].f[i][j].size());
			adjacent_difference(tr[x].f[i][j].begin(),tr[x].f[i][j].end(),tr[x].df[i][j].begin());
			tr[x].df[i][j][0]=LLONG_MAX;
		}
	}
}
inline void PushUp(int x){
	for(int i:{0,1}){
		for(int j:{0,1}){
			for(int k:{0,1}){
				ChMax(tr[x].f[i][j],Shift(Merge(tr[x<<1].f[i][k],tr[x<<1|1].f[k][j]),k));
			}
		}
	}
	DF(x);
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r){
		for(int i:{0,1}) for(int j:{0,1}) tr[x].f[i][j]={-(i|j)*hnf,a[l]};
		DF(x);
		return ;
	}
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}

struct Data{
	array<ll,2> f[2][2];
	friend inline Data operator +(Data x,Data y){
		Data z;
		for(int i:{0,1}){
			for(int j:{0,1}){
				z.f[i][j]={LLONG_MIN,0};
				for(int k:{0,1}){
					z.f[i][j]=max(z.f[i][j],{x.f[i][k][0]+y.f[k][j][0],x.f[i][k][1]+y.f[k][j][1]-k});
				}
			}
		}
		return z;
	}
};

inline Data GetData(int x,ll dlt){
	Data t;
	for(int i:{0,1}){
		for(int j:{0,1}){
			int p=upper_bound(tr[x].df[i][j].begin(),tr[x].df[i][j].end(),dlt,greater<ll>())-tr[x].df[i][j].begin()-1;
			t.f[i][j]={(i||j)&&!p||!~p?-inf:tr[x].f[i][j][p]-p*dlt+i*dlt,p};
		}
	}
	return t;
}
inline Data Query(int x,int l,int r,ll dlt){
	if(l<=tr[x].l&&tr[x].r<=r) return GetData(x,dlt);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r,dlt);
	else if(l>mid) return Query(x<<1|1,l,r,dlt);
	else return Query(x<<1,l,r,dlt)+Query(x<<1|1,l,r,dlt);
}
inline ll Calc(int l,int r,int k){
	ll L=-V,R=V;
	while(L+1<R){
		ll mid=L+R>>1;
		if(Query(1,l,r,mid).f[0][0][1]>=k) L=mid;
		else R=mid;
	}
	return Query(1,l,r,L).f[0][0][0]+1ll*L*k;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build(1,1,n);
	while(q--){
		int l,r,k;
		cin>>l>>r>>k;
		cout<<Calc(l,r,k)<<endl;
	}

	return 0;
}