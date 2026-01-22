#include<bits/stdc++.h>

using namespace std;

ifstream fin("travel.in");
ofstream fout("travel.out");
#define cin fin
#define cout fout

#define int long long
const int N=5e2+9;
const int inf=1e15;

int a[N][N],dis[N][N],f[N][N],n,m;
void BFS(int root){
    queue<int> q;
    q.push(root);
    for(int i=1;i<=n;i++) dis[root][i]=0;
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=1;i<=n;i++){
            if(i==root) continue ;
            if(dis[root][i]) continue ;
            if(a[x][i]==inf) continue ;
            dis[root][i]=dis[root][x]+1;
            q.push(i);
        }
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=f[i][j]=inf;
        for(int i=1,u,v,w;i<=m;i++){
            cin>>u>>v>>w;
            a[u][v]=a[v][u]=min(a[u][v],w);
        }
        
        for(int i=1;i<=n;i++) BFS(i);
        
        int ans=inf;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i][j]==inf) continue ;
                ans=min(ans,(dis[1][i]+1+dis[j][n])*a[i][j]);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    if(a[j][k]==inf) continue ;
                    ans=min(ans,(max(dis[i][j],dis[i][k])+dis[1][i]+dis[i][n]+1)*a[j][k]);
                }
            }
        }
        
        cout<<ans<<endl;
    }

    return 0;
}