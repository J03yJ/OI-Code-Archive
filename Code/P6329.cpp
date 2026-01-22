#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int val[N],n,m;

struct node{
    int lc,rc;
    long long dat;
    node(){}
    node(int L,int R,int D){
        lc=L;rc=R;dat=D;
    }
};
node TR[N<<5];int cnt;
struct sgt{
    int root=1;
    sgt(){
        TR[++cnt]=node(0,0,0);
        root=cnt;
    }
    void insert(int &x,int L,int R,int pos,int k){
        if(!x) x=++cnt,TR[cnt]=node(0,0,0);
        if(L==R){
            TR[x].dat+=k;
            return ;
        }
        int mid=L+R>>1;
        if(pos<=mid) insert(TR[x].lc,L,mid,pos,k);
        else insert(TR[x].rc,mid+1,R,pos,k);
        TR[x].dat=TR[TR[x].lc].dat+TR[TR[x].rc].dat;
    }
    int query(int x,int L,int R,int l,int r){
        if(!x) return 0;
        if(l<=L&&R<=r) return TR[x].dat;
        int mid=L+R>>1,ans=0;
        if(l<=mid) ans+=query(TR[x].lc,L,mid,l,r);
        if(r>mid) ans+=query(TR[x].rc,mid+1,R,l,r);
        return ans;
    }
};

namespace tr{
    int fi[N],ne[N<<1],to[N<<1],adj=1;
    void adeg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }
    int dep[N],fa[N][20];
    void dfs(int x){
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa[x][0]) continue ;
            fa[y][0]=x;
            dep[y]=dep[x]+1;
            dfs(y);
        }
    }
    void init(int n){
        dfs(1);
        for(int k=1;k<20;k++){
            for(int i=1;i<=n;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
        }
    }
    int lca(int x,int y){
        if(dep[x]<dep[y]) swap(x,y);
        for(int k=19;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
        if(x==y) return x;
        for(int k=19;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
        return fa[x][0];
    }
    int dis(int x,int y){
        return dep[x]+dep[y]-dep[lca(x,y)]*2;
    }
}
namespace dtr{
    int fi[N],ne[N],to[N],fa[N],adj=1;
    void adeg(int x,int y){
        fa[y]=x;
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }
    bool vis[N],del[N];
    int siz[N],G;
    void find(int x,int tot){
        siz[x]=1;
        vis[x]=1;
        bool flag=1;
        for(int i=tr::fi[x];i;i=tr::ne[i]){
            int y=tr::to[i];
            if(del[y]) continue ;
            if(vis[y]) continue ;
            find(y,tot);
            siz[x]+=siz[y];
            if(siz[y]>tot/2) flag=0;
        }
        if(tot-siz[x]>tot/2) flag=0;
        if(flag) G=x;
        vis[x]=0;
    }
    void calc_siz(int x){
        siz[x]=1;
        vis[x]=1;
        for(int i=tr::fi[x];i;i=tr::ne[i]){
            int y=tr::to[i];
            if(del[y]) continue ;
            if(vis[y]) continue ;
            calc_siz(y);
            siz[x]+=siz[y];
        }
        vis[x]=0;
    }
    int build(int x,int tot){
        find(x,tot);x=G;
        calc_siz(x);
        del[x]=1;
        for(int i=tr::fi[x];i;i=tr::ne[i]){
            int y=tr::to[i];
            if(del[y]) continue ;
            adeg(x,build(y,siz[y]));
        }
        return x;
    }
    sgt dis[N],fdis[N];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        tr::adeg(x,y);
        tr::adeg(y,x);
    }
    dtr::build(1,n);
    tr::init(n);
    for(int i=1;i<=n;i++){
        int x=i;
        while(x){
            dtr::dis[x].insert(dtr::dis[x].root,0,n,tr::dis(i,x),val[i]);
            if(dtr::fa[x]) dtr::fdis[x].insert(dtr::fdis[x].root,0,n,tr::dis(i,dtr::fa[x]),val[i]);
            x=dtr::fa[x]; 
        }
    }
    long long lst=0;
    while(m--){
        long long op,u,k;
        cin>>op>>u>>k;
        u^=lst,k^=lst;
        if(op){
            int x=u;
            while(x){
                dtr::dis[x].insert(dtr::dis[x].root,0,n,tr::dis(u,x),k-val[u]);
                if(dtr::fa[x]) dtr::fdis[x].insert(dtr::fdis[x].root,0,n,tr::dis(u,dtr::fa[x]),k-val[u]);
                x=dtr::fa[x]; 
            }
            val[u]=k;
        }else{
            long long sum=0;
            int x=u,y=0;
            while(x){
                int d=tr::dis(u,x);
                if(d>k){
                    y=x;
                    x=dtr::fa[x];
                    continue ; 
                }
                sum+=dtr::dis[x].query(dtr::dis[x].root,0,n,0,k-d);
                if(y) sum-=dtr::fdis[y].query(dtr::fdis[y].root,0,n,0,k-d);
                y=x;
                x=dtr::fa[x]; 
            }
            cout<<(lst=sum)<<endl;
        }
    }
    return 0;
}