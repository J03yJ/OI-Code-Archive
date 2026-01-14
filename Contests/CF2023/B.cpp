#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int inf=1e18;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj,n;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
void Clear(){
    for(int i=1;i<=n;i++) fi[i]=0;
}

int dis[N],vis[N],a[N],b[N];
void Dij(int s){
    priority_queue<pair<int,int>> q;
    q.push({0,s});
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    dis[s]=0;
    while(q.size()){
        int x=q.top().second;
        q.pop();
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            if(dis[x]+w[i]<dis[y]){
                dis[y]=dis[x]+w[i];
                q.push({-dis[y],y});
            }
        }
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];

        for(int i=1;i<=n;i++) AdEg(i,b[i],a[i]);
        for(int i=2;i<=n;i++) AdEg(i,i-1,0);
        for(int i=1;i<=n;i++) a[i]+=a[i-1];
        
        Dij(1);
        int ans=0;
        for(int i=1;i<=n;i++) ans=max(ans,a[i]-dis[i]);
        cout<<ans<<endl;
        Clear();
    }

    return 0;
}