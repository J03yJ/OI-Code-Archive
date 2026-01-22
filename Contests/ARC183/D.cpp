#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N],to[N],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dep[N],siz[N],son[N],fa[N],n,G;
bool vis[N];
void DFS(int x){
    vis[x]=1;
    siz[x]=1;
    son[x]=0;
    bool flag=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        fa[y]=x;
        son[x]++;
        dep[y]=dep[x]+1;
        DFS(y);
        siz[x]+=siz[y];
        if(siz[y]>n/2) flag=1;
    }
    if(n-siz[x]>n/2) flag=1;
    if(!flag) G=x;
    vis[x]=0;
}
void Push(int x,vector<int> &v){
    // cout<<x<<endl;
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==G) continue ;
        Push(y,v);
    }
    if(!son[x]) v.push_back(x);
    vis[x]=0;
}
bool Cmp(int x,int y){
    return siz[x]>siz[y];
}

int main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AdEg(u,v),AdEg(v,u);

    dep[1]=0;DFS(1);
    dep[G]=0;DFS(G);
    // cout<<G<<endl;

    priority_queue<pair<int,int>> q[2];
    vector<int> tmp;
    for(int i=fi[G];i;i=ne[i]) tmp.push_back(to[i]);
    sort(tmp.begin(),tmp.end(),Cmp);
    for(int u:tmp){
        vector<int> v;
        Push(u,v);
        priority_queue<pair<int,int>> cur[2];
        // cout<<u<<" : "<<endl;
        for(int x:v) cur[dep[x]&1].push({dep[x],x});

        // cout<<cur[0].size()<<' '<<cur[1].size()<<' '<<q[0].size()<<' '<<q[1].size()<<endl;

        while(q[0].size()&&cur[1].size()||cur[0].size()&&q[1].size()){
            // cout<<cur[0].size()<<' '<<cur[1].size()<<' '<<q[0].size()<<' '<<q[1].size()<<endl;
            while(q[0].size()&&cur[1].size()){
                int x=q[0].top().second,y=cur[1].top().second;
                q[0].pop();cur[1].pop();
                cout<<x<<' '<<y<<endl;
                // cout<<fa[x]<<' '<<fa[y]<<' '<<son[fa[x]]<<' '<<son[fa[y]]<<endl;
                son[fa[x]]--;if(son[fa[x]]==(fa[x]==G)) q[1].push({dep[fa[x]],fa[x]});
                son[fa[y]]--;if(son[fa[y]]==(fa[y]==G)) cur[0].push({dep[fa[y]],fa[y]});
            }
            while(cur[0].size()&&q[1].size()){
                int x=cur[0].top().second,y=q[1].top().second;
                cur[0].pop();q[1].pop();
                cout<<x<<' '<<y<<endl;
                // cout<<fa[x]<<' '<<fa[y]<<' '<<son[fa[x]]<<' '<<son[fa[y]]<<endl;
                son[fa[x]]--;if(son[fa[x]]==(fa[x]==G)) cur[1].push({dep[fa[x]],fa[x]});
                son[fa[y]]--;if(son[fa[y]]==(fa[y]==G)) q[0].push({dep[fa[y]],fa[y]});
            }
            // cout<<"  "<<cur[0].size()<<' '<<cur[1].size()<<' '<<q[0].size()<<' '<<q[1].size()<<endl;
        }

        while(cur[0].size()) q[0].push(cur[0].top()),cur[0].pop();
        while(cur[1].size()) q[1].push(cur[1].top()),cur[1].pop();
    }

    // while(q[0].size()) cout<<q[0].top().second<<' ',q[0].pop();cout<<endl;
    // while(q[1].size()) cout<<q[1].top().second<<' ',q[1].pop();cout<<endl;

    return 0;
}