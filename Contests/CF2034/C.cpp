#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int vis[N][N],n,m;
char a[N][N];
vector<pair<int,int>> son[N][N],edge;
#define Ok(x,y) ((x)>=1&&(y)>=1&&(x)<=n&&(y)<=m)

void DFS1(int x,int y){
    if(!Ok(x,y)) return ;
    if(vis[x][y]) return ;
    vis[x][y]=1;
    for(auto p:son[x][y]) DFS1(p.first,p.second);
}
const int dx[4]={0,-1,0,1};
const int dy[4]={-1,0,1,0};
int DFS2(int x,int y){
    if(!Ok(x,y)) return 0;
    if(vis[x][y]) return 0;
    int ans=1;
    vis[x][y]=1;
    for(int k:{0,1,2,3}){
        int xx=x+dx[k],yy=y+dy[k];
        ans+=DFS2(xx,yy);
    }
    return ans;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cin>>a[i][j];
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='?') continue ;
                int ii=i,jj=j;
                if(a[i][j]=='L') jj--;
                else if(a[i][j]=='R') jj++;
                else if(a[i][j]=='U') ii--;
                else if(a[i][j]=='D') ii++;
                if(Ok(ii,jj)) son[ii][jj].push_back({i,j});
                else edge.push_back({i,j});
            }
        }
        for(auto p:edge) DFS1(p.first,p.second);
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int tmp=DFS2(i,j);
                if(tmp>1) ans+=tmp;
            }
        }
        cout<<ans<<endl;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) son[i][j].clear(),vis[i][j]=0;
        }
        edge.clear();
    }

    return 0;
}