#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int f[N][2],fa[N],n,ans=-1;
inline void DFS(int x){
    f[x][1]=-n;
    priority_queue<int> q;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        ans=max(ans,f[y][1]+1);
        q.push({-max(f[y][0],f[y][1])});
        if(q.size()>4) q.pop();
    }
    if(q.size()==4){
        int tmp=-q.top(),sum=0;
        while(q.size()) sum-=q.top(),q.pop();
        ans=max(ans,sum+1);
        sum-=tmp;
        f[x][1]=sum+1;
    }else if(q.size()==3){
        int sum=0;
        while(q.size()) sum-=q.top(),q.pop();
        f[x][1]=sum+1;
    }
    f[x][0]=1;
}

signed main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    
    DFS(1);
    cout<<ans<<endl;

    return 0;
}