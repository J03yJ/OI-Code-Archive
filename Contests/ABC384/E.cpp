#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e2+9;

int s[N][N],vis[N][N],n,m,sx,sy,k;
const int dx[4]={0,-1,0,1};
const int dy[4]={1,0,-1,0};

signed main(){
    cin>>n>>m>>k>>sx>>sy;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>s[i][j];
    }

    priority_queue<array<int,3>> q;
    int sth=0;vis[sx][sy]=1;
    auto Ins=[&q,&sth](int x,int y){
        sth+=s[x][y];
        for(int i:{0,1,2,3}){
            int xx=x+dx[i],yy=y+dy[i];
            if(vis[xx][yy]) continue ;
            if(xx<1||yy<1||xx>n||yy>m) continue ;
            q.push({-s[xx][yy],xx,yy});
            vis[xx][yy]=1;
        }
    };
    Ins(sx,sy);
    while(q.size()){
        int x=q.top()[1],y=q.top()[2];
        q.pop();
        if(__int128(1)*s[x][y]*k>=sth) break ;
        Ins(x,y);
    }

    cout<<sth<<endl;

    return 0;
}