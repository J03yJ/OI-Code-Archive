#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;
const int M=1e6+9;
#define int long long

ifstream fin("garden.in");
ofstream fout("garden.out");
#define cin fin
#define cout fout

int a[N][N],n,m;

int F(int x,int y){
	return (x-1)*m+y;
}
vector<pair<int,int>> C[M];

int fa[M],siz[M];
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void mrg(int x,int y){
	x=find(x);y=find(y);
	if(x==y) return ;
	fa[y]=x;
	siz[x]+=siz[y];
}

int ans,edge;
void merge(int x,int y){
	x=find(x);y=find(y);
	if(x==y) return ;
	if(y==edge) swap(x,y);
	if(x==edge) ans-=siz[y];
	mrg(x,y);
}

const int dx[4]={0,-1,0,1};
const int dy[4]={-1,0,1,0};
bool Edge(int x,int y){
	if(x<1||y<1||x>n||y>m) return 1;
	else return 0;
}

signed main(){
	int Max=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j],C[a[i][j]].emplace_back(i,j),Max=max(Max,a[i][j]);
	}
	
	edge=n*m+1;
	for(int i=1;i<=edge;i++) fa[i]=i,siz[i]=1;
	
	int res=0;
	for(int i=0;i<=Max;i++){
		for(pair<int,int> p:C[i]){
			ans++;
			int x=p.first,y=p.second;
			for(int k=0;k<4;k++){
				int xx=x+dx[k],yy=y+dy[k];
				if(Edge(xx,yy)) merge(edge,F(x,y));
				else if(a[xx][yy]<=i) merge(F(x,y),F(xx,yy));
			}
//			cout<<x<<" "<<y<<' '<<ans<<endl;
		}
		res+=ans;
	}
	
	cout<<res<<endl;
	
	return 0;
}
