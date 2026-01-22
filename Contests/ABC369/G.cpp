#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int dep[N],fa[N],dfn[N],siz[N],idfn[N],vis[N],dcnt,n;
void DFS(int x){
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        dep[y]=dep[x]+w[i];
        fa[y]=x;
        DFS(y);
        siz[x]+=siz[y];
    }
    // cout<<x<<' '<<dfn[x]<<' '<<fa[x]<<' '<<dep[x]<<' '<<siz[x]<<endl;
}

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void PushUp(int x){
    dat(x)=max(dat(x<<1),dat(x<<1|1));
}
void Push(int x,int k){
    tag(x)+=k;
    dat(x)+=k;
}
void PushDown(int x){
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=0;
}

void Build(int x,int l,int r){
    l(x)=l,r(x)=r,tag(x)=0;
    if(l(x)==r(x)){
        dat(x)=dep[idfn[l(x)]];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l(x),mid);
    Build(x<<1|1,mid+1,r(x));
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
pair<int,int> Query(int x){
    if(l(x)==r(x)) return {idfn[l(x)],dat(x)};
    PushDown(x);
    if(dat(x)==dat(x<<1)) return Query(x<<1);
    else return Query(x<<1|1);
}

signed main(){
    cin>>n;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w);
        AdEg(v,u,w);
    }

    DFS(1);
    Build(1,1,n);

    int ans=0;
    for(int i=1;i<=n;i++){
        pair<int,int> tmp=Query(1);
        ans+=tmp.second<<1;
        // cout<<tmp.first<<' '<<tmp.second<<endl;
        cout<<ans<<endl;
        int cur=tmp.first;
        while(cur!=1&&!vis[cur]){
            vis[cur]=1;
            // cout<<cur<<' '<<dfn[cur]<<' '<<dfn[cur]+siz[cur]-1<<' '<<dep[fa[cur]]-dep[cur]<<endl;
            Modify(1,dfn[cur],dfn[cur]+siz[cur]-1,dep[fa[cur]]-dep[cur]);
            cur=fa[cur];
        }
    }

    return 0;
}