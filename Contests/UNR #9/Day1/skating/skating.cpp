#include<bits/stdc++.h>

using namespace std;

const int N=5e3+9;

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
int n,m;
char a[N][N];

bool vis[N][N];
inline bool Check(){
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) vis[i][j]=0;
	queue<pii> q;
	for(int i=1;i<=n&&q.empty();i++){
		for(int j=1;j<=m&&q.empty();j++) if(a[i][j]=='.') q.push({i,j});
	}

	while(q.size()){
		pii x=q.front();
		int i=fir(x),j=sec(x);
		q.pop();
		if(i<1||j<1||i>n||j>m) continue ;
		if(vis[i][j]) continue ;
		if(a[i][j]=='#') continue ;
		vis[i][j]=1;
		q.push({i-1,j});
		q.push({i+1,j});
		q.push({i,j-1});
		q.push({i,j+1});
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) if(!vis[i][j]&&a[i][j]=='.') return 0;
	}
	return 1;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) cin>>a[i][j];
		}

		if(Check()){
			if(n==3&&m==3){
				int err=0,cnt1=0,cnt2=0;
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++) err+=(a[i][j]=='#');
				}
				for(int i=1;i<=n;i++){
					cnt1+=a[i][2]=='#';
					cnt2+=a[2][i]=='#';
				}
				if(!err){
					for(int i=1;i<=n;i++) a[i][2]=a[2][i]='*';
				}else if(err-cnt1-cnt2){
					for(int i=1;i<=n;i++){
						for(int j=1;j<=m;j++) if(a[i][j]=='.') a[i][j]='*';
					}
				}else if(err==1&&a[2][2]=='#'){
					for(int i=1;i<=n;i++){
						for(int j=1;j<=m;j++) if(a[i][j]=='.') a[i][j]='*';
					}
				}if(cnt1){
					for(int i=1;i<=n;i++){
						if(a[i][2]!='#') a[i][2]='*';
					}
				}else if(cnt2){
					for(int i=1;i<=n;i++){
						if(a[2][i]!='#') a[2][i]='*';
					}
				}
			}else{
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++) if(a[i][j]=='.') a[i][j]='*';
				}
			}
		}

		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) cout<<a[i][j];
			cout<<endl;
		}
	}

	return 0;
}