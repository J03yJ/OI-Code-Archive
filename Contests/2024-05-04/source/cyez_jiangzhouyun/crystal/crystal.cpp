// Expect 19pts

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3+9;
const int p=998244353;

ifstream fin("crystal.in");
ofstream fout("crystal.out");
#define cin fin
#define cout fout

bool a[N],vis[N];
vector<int> G[N];
int bfs(int s,int n){
	for(int i=1;i<=n;i++) vis[i]=0;
	queue<pair<int,int>> q;
	q.push({s,0});
	while(q.size()){
		int x=q.front().first,cnt=q.front().second;
		q.pop();
		vis[x]=1;
		if(a[x]!=a[s]) return cnt;
		for(int y:G[x]){
			if(!vis[y]) q.push({y,cnt+1});
		}
	}
	return 0;
}

int dep[N][N];
int cnt[N][N];
void dfs(int root,int x){
	for(int y:G[x]){
		if(!dep[root][y]) dep[root][y]=dep[root][x]+1,dfs(root,y);
	}
}
int qpow(int x,int y){
	int m=1;
	while(y){
		if(y&1) m=m*x%p;
		x=x*x%p;
		y>>=1;
	}
	return m;
}

signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int fa;
		cin>>fa;
		G[fa].push_back(i+1);
		G[i+1].push_back(fa);
	}
	if(k==1){
		for(int i=1;i<=n;i++){
			dep[i][i]=1;
			dfs(i,i);
			for(int j=1;j<=n;j++) cnt[i][--dep[i][j]]++;
			for(int j=1;j<=n;j++) cnt[i][j]+=cnt[i][j-1];
//			for(int j=1;j<=n;j++) cout<<dep[i][j]<<' ';cout<<endl;
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<n;j++){
				int a=cnt[i][j-1],b=cnt[i][j]-cnt[i][j-1];
				ans=(ans+j*qpow(2,n-a-b)%p*(qpow(2,b)-1)%p*2%p)%p;
//				cout<<a<<'/'<<b<<' ';
			}
//			cout<<endl;
		}
		cout<<ans<<endl;
		return 0;
	}
	int ans=0;
	for(int sta=0;sta<(1<<n);sta++){
		for(int i=1;i<=n;i++) a[i]=(sta>>i-1)&1;
		int sum=0;
		for(int i=1;i<=n;i++) sum+=bfs(i,n);
		if(k==1) ans=(ans+sum)%p;
		else ans=(ans+sum*sum%p*sum%p)%p;
//		cout<<sum<<endl;
	}
	cout<<ans<<endl;
	return 0;
}
