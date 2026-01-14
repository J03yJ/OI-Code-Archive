#include<bits/stdc++.h>

using namespace std;

const int N=1e1+9;
const int dx[4]={0,-1,0,1};
const int dy[4]={-1,0,1,0};

int a[N][N],ans,n,m,k;
void DFS(int dep,int x,int y){
    if(dep==k){
        ans++;
        return ;
    }
    a[x][y]=1;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx<1||yy<1||xx>n||yy>m) continue ;
        if(a[xx][yy]) continue ;
        DFS(dep+1,xx,yy);
    }
    a[x][y]=0;
}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='#') a[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]) continue ;
            DFS(0,i,j);
        }
    }
    cout<<ans<<endl;

    return 0;
}