#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int M=2e5+9;
const ll inf=1e18;
const int mod=1e9+7;

ll d[3][3][M],ans;
int a[3][M],vis[3][M],n,m;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
inline void Dij(int si,int sj,int l,int r,ll ld,ll rd,ll dis[3][M]){
	for(int i:{0,1,2}) for(int j=l;j<=r;j++) dis[i][j]=inf,vis[i][j]=0;
	dis[si][sj]=a[si][sj];
	priority_queue<array<ll,3>> q;
	q.push({-dis[si][sj],si,sj});
	while(q.size()){
		int i=q.top()[1],j=q.top()[2];
		q.pop();
		if(vis[i][j]) continue ;
		vis[i][j]=1;
		if(j==l&&(~i&1)){
			int k=i^2;
			if(dis[i][j]+a[k][j]+ld<dis[k][j]){
				dis[k][j]=dis[i][j]+a[k][j]+ld;
				q.push({-dis[k][j],k,j});
			}
		}
		if(j==r&&(~i&1)){
			int k=i^2;
			if(dis[i][j]+a[k][j]+rd<dis[k][j]){
				dis[k][j]=dis[i][j]+a[k][j]+rd;
				q.push({-dis[k][j],k,j});
			}
		}
		for(int o:{0,1,2,3}){
			int ii=i+dx[o],jj=j+dy[o];
			if(ii<0||jj<l||ii>2||jj>r) continue ;
			if(dis[i][j]+a[ii][jj]<dis[ii][jj]){
				dis[ii][jj]=dis[i][j]+a[ii][jj];
				q.push({-dis[ii][jj],ii,jj});
			}
		}
	}
}

struct Fenw{
	int lim;
	ll tr[M<<2];
	inline void Add(int x,ll k){while(x<=lim) tr[x]+=k,x+=x&-x;}
	inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
	inline void Clear(){while(lim) tr[lim--]=0;}
}C,S;

inline void Conquer(int l,int r,ll ld,ll rd){
	if(l>r) return ;
	int mid=l+r>>1;
	for(int i:{0,1,2}){
		Dij(i,mid,l,r,ld,rd,d[i]);
		for(int j:{0,1,2}){
			for(int k=l;k<=r;k++){
				if(k!=mid||i<j) ans=(ans+d[i][j][k])%mod;
			}
		}
	}
	for(int i:{0,1,2}) for(int j:{0,1,2}) for(int k=r;k>mid;k--) d[i][j][k]-=a[i][mid];
	for(int i:{0,1,2}){
		int x=(i+1)%3,y=(i+2)%3;
		vector<ll> val;
		vector<array<ll,3>> lv,rv;
		for(int j:{0,1,2}){
			for(int k=l;k<mid;k++){
				lv.push_back({(d[i][j][k]-d[x][j][k])*3+i-x,(d[i][j][k]-d[y][j][k])*3+i-y,d[i][j][k]});
			}
			for(int k=r;k>mid;k--){
				rv.push_back({(d[x][j][k]-d[i][j][k])*3,(d[y][j][k]-d[i][j][k])*3,d[i][j][k]});
			}
		}
		val.push_back(-inf);
		for(auto &t:lv) val.push_back(t[1]);
		for(auto &t:rv) val.push_back(t[1]);
		sort(lv.begin(),lv.end());
		sort(rv.begin(),rv.end());
		sort(val.begin(),val.end());
		for(auto &t:lv) t[1]=lower_bound(val.begin(),val.end(),t[1])-val.begin();
		for(auto &t:rv) t[1]=lower_bound(val.begin(),val.end(),t[1])-val.begin();
		C.lim=S.lim=val.size()-1;
		for(int j=0,k=0;k<rv.size();k++){
			while(j<lv.size()&&lv[j][0]<=rv[k][0]){
				C.Add(lv[j][1],1);
				S.Add(lv[j][1],lv[j][2]);
				j++;
			}
			ans=(ans+C.Ask(rv[k][1])*rv[k][2])%mod;
			ans=(ans+S.Ask(rv[k][1]))%mod;
		}
		C.Clear();
		S.Clear();
	}
	ll md=d[0][2][mid];
	Conquer(l,mid-1,ld,md),Conquer(mid+1,r,md,rd);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	Conquer(1,m,inf,inf);
	ans=(ans<<1)%mod;

	cout<<ans<<endl;

	return 0;
}