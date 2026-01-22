#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int vis[N],c[N],cnt[3],ecnt,vcnt,n,m,err;
void DFS(int x){
    vis[x]=1;
    cnt[c[x]]++;
    vcnt++;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        ecnt++;
        if(vis[y]){
            if(c[y]!=(c[x]+w[i])%3) err=1;
            continue ;
        }
        c[y]=(c[x]+w[i])%3;
        DFS(y);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v,1);
        AdEg(v,u,2);
    }

    long long ans=0;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        err=ecnt=vcnt=0;
        for(int k:{0,1,2}) cnt[k]=0;
        DFS(i);
        if(err) ans+=1ll*vcnt*vcnt;
        else{
            if(!cnt[0]||!cnt[1]||!cnt[2]) ans+=ecnt>>1;
            else for(int k:{0,1,2}) ans+=1ll*cnt[k]*cnt[(k+1)%3];
        }
    }
    cout<<ans<<endl;

    return 0;
}