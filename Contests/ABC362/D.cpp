#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int inf=1e18;

int fi[N],ne[N<<2],to[N<<2],w[N<<2],adj=1;
void adeg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int cst[N],dis[N],vis[N],n,m;
void dij(){
    for(int i=1;i<=n;i++) dis[i]=inf;
    dis[1]=cst[1];
    priority_queue<pair<int,int>> q;
    q.push({-cst[1],1});
    while(q.size()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            if(dis[x]+w[i]+cst[y]<dis[y]){
                dis[y]=dis[x]+w[i]+cst[y];
                q.push({-dis[y],y});
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>cst[i];
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        adeg(x,y,z);
        adeg(y,x,z);
    }

    dij();
    for(int i=2;i<=n;i++) cout<<dis[i]<<' ';
    cout<<endl;
    
    return 0;
}