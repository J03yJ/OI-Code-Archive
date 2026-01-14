#include<bits/stdc++.h>

using namespace std;

ifstream fin("ggd.in");
ofstream fout("ggd.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pil=pair<int,ll>;
const int N=1e3+9;
const ll inf=1e18;

int a[N],grf[N][N],n,k;
vector<int> e[N];
ll w[N];

int vis[N];
inline void DFS(int x,int c,vector<int> &node,bool &err){
	vis[x]=c;
	node.push_back(x);
	for(int y:e[x]){
		if(!vis[y]) DFS(y,-c,node,err);
		else if(vis[y]!=-vis[x]) err|=1;
	}
}

ll f[N][N];
int op[N][N],col[N],ans[N];

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cin>>grf[i][j];
	}

	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(grf[i][j]&&grf[j][i]){
				e[i].push_back(j);
				e[j].push_back(i);
				w[i]+=a[i];
				w[j]+=a[j];
			}else if(grf[i][j]||grf[j][i]){
				w[i]+=2ll*a[i]*a[j];
				w[j]+=2ll*a[i]*a[j];
			}
		}
	}

	bool err=0;
	vector<array<int,2>> c;
	vector<array<ll,2>> v;
	vector<vector<int>> pt;
	for(int i=1;i<=n;i++){
		if(vis[i]) continue ;
		vector<int> node;
		DFS(i,1,node,err);
		array<int,2> cnt={0,0};
		array<ll,2> val={0,0};
		for(int x:node){
			cnt[vis[x]>0]++;
			val[vis[x]>0]+=w[x];
		}
		c.push_back(cnt);
		v.push_back(val);
		pt.push_back(node);
	}
	
	k=n-k;
	int m=c.size();
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++) f[i][j]=-inf;
	}
	f[0][0]=0;
	for(int i=1;i<=m;i++){
		auto cnt=c[i-1];
		auto val=v[i-1];
		for(int o:{0,1}){
			for(int j=n;j>=cnt[o];j--){
				if(f[i-1][j-cnt[o]]==-inf) continue ;
				if(f[i-1][j-cnt[o]]+val[o]>f[i][j]){
					f[i][j]=f[i-1][j-cnt[o]]+val[o];
					op[i][j]=o;
				}
			}
		}
	}

	if(f[m][k]==-inf) cout<<"NO"<<endl;
	else{
		cout<<"YES"<<endl;
		ll res=0;
		for(int i=m,cur=k;i>=1;i--){
			col[i-1]=op[i][cur];
			res+=v[i-1][col[i-1]];
			cur-=c[i-1][col[i-1]];
		}
		for(int i=0;i<m;i++){
			for(int x:pt[i]) ans[x]=col[i]^(vis[x]>0);
		}
		for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
		cout<<endl;
	}

	return 0;
}