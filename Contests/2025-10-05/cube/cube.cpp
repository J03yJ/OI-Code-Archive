#include<bits/stdc++.h>

using namespace std;

ifstream fin("cube.in");
ofstream fout("cube.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e2+9;
const int C=1e6+9;

int n;
char a[N][N][N],f[N][N],r[N][N],u[N][N];
inline int Valid(int i,int j,int k){return 1<=i&&i<=n&&1<=j&&j<=n&&1<=k&&k<=n;}
inline int Id(int i,int j,int k){return (i-1)*n*n+(j-1)*n+k;}

int fa[C],vis[C],c[C];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	const int dx[6]={1,0,0,-1,0,0};
	const int dy[6]={0,1,0,0,-1,0};
	const int dz[6]={0,0,1,0,0,-1};

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>f[i][j];
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>r[i][j];
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>u[i][j];
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					a[i][j][k]='.';
					fa[Id(i,j,k)]=Id(i,j,k);
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(f[i][j]=='.') continue ;
				for(int k=1;k<=n;k++){
					if(r[i][k]=='#'&&u[n-k+1][j]=='#') a[i][j][k]='#';
				}
			}
		}

		int cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					if(a[i][j][k]=='.') continue ;
					for(int p=0;p<6;p++){
						int ii=i+dx[p],jj=j+dy[p],kk=k+dz[p];
						if(a[ii][jj][kk]=='#'&&Valid(ii,jj,kk)){
							Merge(Id(i,j,k),Id(ii,jj,kk));
						}
					}
					cnt++;
				}
			}
		}
		if(!cnt){
			cout<<"NO"<<endl;
			continue ;
		}
		
		int tot=0,root=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(f[i][j]=='.') continue ;
				vector<int> tmp;
				for(int k=1;k<=n;k++) if(a[i][j][k]=='#') tmp.push_back(Find(Id(i,j,k)));
				for(int x:tmp) if(!vis[x]) c[x]++,vis[x]=1;
				for(int x:tmp) vis[x]=0;
				tot++;
			}
		}
		for(int i=1;i<=n;i++){
			for(int k=1;k<=n;k++){
				if(r[i][k]=='.') continue ;
				vector<int> tmp;
				for(int j=1;j<=n;j++) if(a[i][j][k]=='#') tmp.push_back(Find(Id(i,j,k)));
				for(int x:tmp) if(!vis[x]) c[x]++,vis[x]=1;
				for(int x:tmp) vis[x]=0;
				tot++;
			}
		}
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if(u[n-k+1][j]=='.') continue ;
				vector<int> tmp;
				for(int i=1;i<=n;i++) if(a[i][j][k]=='#') tmp.push_back(Find(Id(i,j,k)));
				for(int x:tmp) if(!vis[x]) c[x]++,vis[x]=1;
				for(int x:tmp) vis[x]=0;
				tot++;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					if(a[i][j][k]=='.') continue ;
					if(c[Id(i,j,k)]==tot){
						root=Id(i,j,k);
						break ;
					}
				}
				if(root) break ;
			}
			if(root) break ;
		}
		for(int i=1;i<=n*n*n;i++) c[i]=0;

		if(!root){
			cout<<"NO"<<endl;
			continue ;
		}

		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					if(a[j][k][i]=='.'||Find(Id(j,k,i))!=root) cout<<'.';
					else cout<<'#';
				}
				cout<<endl;
			}
		}
	}

	return 0;
}