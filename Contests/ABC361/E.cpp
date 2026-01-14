#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=2e5+9;

int fi[N],to[N<<1],ne[N<<1],w[N<<1],adj;
void adeg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int dis[N];
void dfs(int x,int fa){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        dis[y]=dis[x]+w[i];
        dfs(y,x);
    }
}

signed main(){
    int n,ans=0;
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y,z;
        cin>>x>>y>>z;
        adeg(x,y,z);
        adeg(y,x,z);
        ans+=z*2;
    }

    dfs(1,-1);
    int mx=-1,pos=0;
    for(int i=1;i<=n;i++) if(dis[i]>mx) mx=dis[i],pos=i;
    dis[pos]=0;
    dfs(pos,-1);
    for(int i=1;i<=n;i++) mx=max(mx,dis[i]);

    cout<<ans-mx<<endl;

    return 0;
}