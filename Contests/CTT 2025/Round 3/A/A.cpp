#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e4+9;
const ll inf=1e18;
template<class T> inline void ChMax(T &x,T y){if(y>x) x=y;}

vector<int> e[N];
ll s[N],su[N][N];
int c[N],v[N],fa[N],siz[N],l[N],r[N],elr[N<<1],n,k,t,ecnt;
inline void DFS(int x){
	elr[l[x]=++ecnt]=x;
	su[x][siz[x]=1]=s[x]=s[fa[x]]+v[x];
	for(int y:e[x]){
		fa[y]=x;
		DFS(y);
		vector<ll> tmp(siz[x]+siz[y]);
		merge(su[x]+1,su[x]+siz[x]+1,su[y]+1,su[y]+siz[y]+1,tmp.begin(),greater<ll>());
		copy(tmp.begin(),tmp.end(),su[x]+1);
		siz[x]+=siz[y];
	}
	elr[r[x]=++ecnt]=x;
}
inline void Conquer(int x,vector<ll> &f,vector<ll> &g,int l,int r,int vl,int vr){
	if(l>r) return ;
	int mid=l+r>>1;
	array<ll,2> tmp={-inf,0};	
	for(int i=mid;i<=vr;i++) ChMax(tmp,{f[i]+su[x][i-mid],i});
	int mp=tmp[1];
	ChMax(g[mid],f[mp]+su[x][mp-mid]);
	if(tmp[0]>=0) Conquer(x,f,g,l,mid-1,vl,mp);
	Conquer(x,f,g,mid+1,r,mp,vr);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>k>>t;
	for(int i=1;i<=n;i++) cin>>c[i]>>v[i];
	for(int i=2,f;i<=n;i++) cin>>f,e[f].push_back(i);

	DFS(1);
	for(int x=1;x<=n;x++){
		for(int i=1;i<=siz[x];i++) su[x][i]+=su[x][i-1];
	}

	vector<vector<vector<ll>>> f(ecnt+2,vector<vector<ll>>(k+1,vector<ll>(t+1,-inf)));
	f[1][k][t]=0; 
	for(int i=1;i<=ecnt;i++){
		int x=elr[i];
		if(i==l[x]){
			for(int p=0;p<=t;p++){
				list<int> li;
				auto W=[&](int j,int _j){return f[i][_j][p]+1ll*(_j-j)*v[x];};
				for(int j=k-1;~j;j--){
					while(li.size()&&j+c[x]-p<li.front()) li.pop_front();
					while(li.size()&&W(j,li.back())<W(j,j+1)) li.pop_back();
					li.push_back(j+1);
					if(li.size()) ChMax(f[i+1][j][p],W(j,li.front()));
				}
			}
			for(int j=0;j<=k;j++) Conquer(x,f[i][j],f[r[x]+1][j],0,t,0,t);
		}else{
			for(int p=0;p<=t;p++){
				list<int> li;
				auto W=[&](int j,int _j){return f[i][_j][p]+1ll*(_j-j)*v[x];};
				for(int j=k;~j;j--){
					while(li.size()&&j+p<li.front()) li.pop_front();
					while(li.size()&&W(j,li.back())<W(j,j)) li.pop_back();
					li.push_back(j);
					if(li.size()) ChMax(f[i+1][j][p],W(j,li.front()));
				}
			}
			for(int p=0;p<t;p++){
				list<int> li;
				auto W=[&](int j,int _j){return f[i][_j][p+1]+1ll*(_j-j)*v[x]+s[x];};
				for(int j=k;~j;j--){
					while(li.size()&&j+p<li.front()) li.pop_front();
					while(li.size()&&W(j,li.back())<W(j,j)) li.pop_back();
					li.push_back(j);
					if(li.size()) ChMax(f[i+1][j][p],W(j,li.front()));
				}
			}
		}
	}

	ll ans=0;
	for(int j=0;j<=k;j++){
		for(int p=0;p<=t;p++) ChMax(ans,f[ecnt+1][j][p]);
	}
	cout<<ans<<endl;

	return 0;
}