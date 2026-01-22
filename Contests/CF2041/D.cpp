#include<bits/stdc++.h>

using namespace std;

const int N=2e4+9;
int dx[4]={0,-1,0,1};
int dy[4]={-1,0,1,0};

int n,m;
vector<char> a[N];
vector<int> f[4][4][N];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        a[i]=vector<char>(m+1,0);
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }

    for(int i=1;i<=n;i++){
        for(int k:{0,1,2,3}){
            for(int d:{0,1,2,3}){
                f[k][d][i]=vector<int>(m+1,1e9);
            }
        }
    }

    int sx,sy,tx,ty;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='S') sx=i,sy=j;
            else if(a[i][j]=='T') tx=i,ty=j;
        }
    }

    queue<array<int,4>> q;
    q.push({sx,sy,0,0});
    f[0][0][sx][sy]=0;
    while(q.size()){
        int x=q.front()[0],y=q.front()[1],k=q.front()[2],d=q.front()[3];
        q.pop();
        // cout<<x<<' '<<y<<' '<<d<<' '<<k<<" "<<f[k][d][x][y]<<endl;
        for(int kk:{0,1,2,3}){
            int dd=1,xx=x+dx[kk],yy=y+dy[kk];
            if(xx<1||yy<1||xx>n||yy>m) continue ;
            if(a[xx][yy]=='#') continue ;
            if(kk==k) dd+=d;
            // cout<<" : "<<xx<<' '<<yy<<' '<<kk<<' '<<dd<<endl;
            if(dd>3) continue ;
            if(f[kk][dd][xx][yy]<1e9) continue ;
            f[kk][dd][xx][yy]=f[k][d][x][y]+1;
            q.push({xx,yy,kk,dd});
        }
    }
    int ans=1e9;
    for(int k:{0,1,2,3}){
        for(int d:{1,2,3}) ans=min(ans,f[k][d][tx][ty]);
    }
    if(ans==1e9) cout<<-1<<endl;
    else cout<<ans<<endl;

    return 0;
}