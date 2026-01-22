#include<bits/stdc++.h>

using namespace std;

ifstream fin("railway.in");
ofstream fout("railway.out");
#define cin fin
#define cout fout

const int N=5e5+9;
const int inf=1e9;

int fi[N],to[N<<1],ne[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dis1[N],dis2[N],vis[N],n,m;
void Dij(int s,int *dis){
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    dis[s]=0;
    priority_queue<pair<int,int>> q;
    q.push({0,s});
    while(q.size()){
        int x=q.top().second;
        q.pop();
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            if(dis[x]+1<dis[y]){
                dis[y]=dis[x]+1;
                q.push({-dis[y],y});
            }
        }
    }
}

int main(){
    vector<int> tmp;
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        if(u&&v) AdEg(u,v),AdEg(v,u);
        else tmp.push_back(u|v);
    }

    Dij(1,dis1);
    Dij(n,dis2);
    int ans=inf,lx=inf,rx=inf;
    for(int x:tmp) lx=min(lx,dis1[x]),rx=min(rx,dis2[x]);
    for(int i=1;i<=n;i++){
        int res=min(lx+1,dis1[i])+min(rx+1,dis2[i]);
        int x=min(res,dis1[n]);
        if(x==inf) cout<<-1<<endl;
        else cout<<x<<endl;
    }

    return 0;
}