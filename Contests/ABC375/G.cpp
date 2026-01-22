#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int inf=1e18;

struct node{
    int l,r,dat;
}tr[N<<2];
void Build(int x,int l,int r){
    tr[x].l=l;tr[x].r=r;tr[x].dat=inf;
    if(tr[x].l==tr[x].r) return ;
    int mid=tr[x].l+tr[x].r>>1;
    Build(x<<1,tr[x].l,mid);
    Build(x<<1|1,mid+1,tr[x].r);
}
void Modify(int x,int l,int r,int k){
    if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat=min(tr[x].dat,k),void();
    int mid=tr[x].l+tr[x].r>>1;
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
}

int fi[N],to[N<<1],ne[N<<1],w[N<<1],adj=1;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int dis[N],rdis[N],vis[N],n,m;
void Dij(int s,int *dis){
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    priority_queue<pair<int,int>> q;
    dis[s]=0;
    q.push({0,s});
    while(q.size()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            if(dis[x]+w[i]>=dis[y]) continue ;
            dis[y]=dis[x]+w[i];
            q.push({-dis[y],y});
        }
    }
}
int pth[N],pv[N],pe[N],tot;
void FindPath(int s,int t){
    int pos=s;
    while(pos!=t){
        pv[pos]=1;
        pth[++tot]=pos;
        for(int i=fi[pos];i;i=ne[i]){
            int qos=to[i];
            if(rdis[pos]==rdis[qos]+w[i]){
                pos=qos;
                pe[i]=pe[i^1]=1;
                break ;
            }
        }
    }
    pv[pos]=1;
    pth[++tot]=pos;
}
int ans[N],cut[N];
void Query(int x,int cur){
    cur=min(cur,tr[x].dat);
    if(tr[x].l==tr[x].r){
        if(cur>dis[n]) ans[tr[x].l]=1;
        return ;
    }else return Query(x<<1,cur),Query(x<<1|1,cur);
}
int lv[N],rv[N];
void BFS(int c,int *dis,int *blg){
    queue<int> q;
    q.push(pth[c]);
    blg[pth[c]]=c;
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(pv[y]) continue ;
            if(blg[y]) continue ;
            if(dis[x]+w[i]!=dis[y]) continue ;
            blg[y]=c;
            q.push(y);
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w);
        AdEg(v,u,w);
    }

    Dij(1,dis);
    Dij(n,rdis);
    FindPath(1,n);
    for(int i=1;i<=n;i++) BFS(i,dis,lv);
    for(int i=n;i>=1;i--) BFS(i,rdis,rv);

    Build(1,1,tot);
    for(int x=1;x<=n;x++){
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(pe[i]) continue ;
            if(!lv[x]||!rv[y]) continue ;
            if(rv[y]<=lv[x]) continue ;
            Modify(1,lv[x],rv[y]-1,dis[x]+rdis[y]+w[i]);
        }
    }
    Query(1,inf);
    for(int i=1;i<tot;i++){
        if(!ans[i]) continue ;
        for(int j=fi[pth[i]];j;j=ne[j]){
            if(to[j]==pth[i+1]){
                cut[j]=cut[j^1]=1;
                break ;
            }
        }
    }
    for(int i=2;i<=adj;i+=2){
        if(cut[i]) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}