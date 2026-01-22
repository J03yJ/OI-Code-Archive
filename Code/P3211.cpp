#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],n,m;
vector<int> bel[N];

int siz[N],vis[N];
inline void FindG(int x,int fa,int &g,int tot){
    bool flag=1;
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==fa) continue ;
        FindG(y,x,g,tot);
        siz[x]+=siz[y];
        if(siz[y]>tot/2) flag=0;
    }
    if(tot-siz[x]>tot/2) flag=0;
    if(flag) g=x;
}
int fa[N],cnt[N],scnt[N],cvis[N],siv[N];
inline void DFS(int x,vector<int> &v){
    siz[x]=1;
    v.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y,v);
        siz[x]+=siz[y];
    }
}
int ans;
inline void Solve(int x,int tot){
    FindG(x,-1,x,tot);
    // cout<<x<<" : "<<endl;
    vector<int> son,rollback;
    fa[x]=0,DFS(x,son);
    // for(int u:son) cout<<u<<' ';cout<<endl;

    for(int u:son) scnt[a[u]]++;
    int ccnt=0;
    queue<int> q;
    q.push(a[x]);
    while(q.size()){
        int c=q.front();
        q.pop();
        if(cvis[c]) continue ;
        // cout<<c<<endl;
        if(scnt[c]<cnt[c]){
            ccnt=m+1;
            // cout<<"E!"<<endl;
            break ;
        }
        ccnt++;
        cvis[c]=1;
        rollback.push_back(c);
        for(int u:bel[c]){
            while(u&&!siv[u]){
                siv[u]=1;
                q.push(a[u]);
                u=fa[u];
            }
        }
    }
    for(int c:rollback) cvis[c]=0;
    rollback.clear();
    for(int u:son) siv[u]=0,scnt[a[u]]--;
    ans=min(ans,ccnt);

    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        Solve(y,siz[y]);
    }
    
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++,bel[a[i]].push_back(i);

    ans=m+1;
    Solve(1,n);
    cout<<ans-1<<endl;

    return 0;
}