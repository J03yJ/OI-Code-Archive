#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int inf=1e9;
const int N=1e2+9;

int n,dis[N][N];
char a[N][N];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            dis[i][j]=-1;
        }
    }

    queue<pii> q;
    for(int i=1;i<=n;i++) dis[i][i]=0,q.push({i,i});
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(~dis[i][j]) continue ;
            if(a[i][j]=='-') continue ;
            dis[i][j]=1;
            q.push({i,j});
        }
    }
    while(q.size()){
        int x=fir(q.front()),y=sec(q.front());
        q.pop();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(~dis[i][j]) continue ;
                if(a[i][x]=='-') continue ;
                if(a[y][j]=='-') continue ;
                if(a[i][x]!=a[y][j]) continue ;
                dis[i][j]=dis[x][y]+2;
                q.push({i,j});
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<dis[i][j]<<' ';
        cout<<endl;
    }

    return 0;
}