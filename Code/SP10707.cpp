#include<bits/stdc++.h>
<<<<<<< HEAD

using namespace std;

const int N=4e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AddEg(int x,int y){
=======
using namespace std;

const int N=2e5+9;
int fi[N],ne[N<<1],to[N<<1],adj;
void adeg(int x,int y){
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
<<<<<<< HEAD
int siz[N],dep[N],fa[N],hson[N];
void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int top[N],eu[N<<1],st[N],ed[N],ecnt;
void DFS2(int x,int t){
    top[x]=t;
    eu[++ecnt]=x;
    st[x]=ecnt;
    if(hson[x]) DFS2(hson[x],t);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
    eu[++ecnt]=x;
    ed[x]=ecnt;
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) return x;
    else return y;
}

int a[N],blk[N<<1],cnt[N],vis[N],n,m;
int ql[N],qr[N],lca[N],p[N],ans[N];
bool Cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return blk[ql[x]]%2?qr[x]<qr[y]:qr[x]>qr[y];
}
void Add(int x,int &res){if(!cnt[x]) res++;cnt[x]++;}
void Del(int x,int &res){cnt[x]--;if(!cnt[x]) res--;}
void Ins(int x,int &res){
    if(!vis[x]) Add(a[x],res);
    else Del(a[x],res);
    vis[x]^=1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AddEg(u,v);
        AddEg(v,u);
    }
    DFS1(1);
    DFS2(1,1);
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        lca[i]=LCA(u,v);
        if(st[u]>st[v]) swap(u,v);
        if(lca[i]==u){
            lca[i]=0;
            ql[i]=st[u];
            qr[i]=st[v];
        }else{
            ql[i]=ed[u];
            qr[i]=st[v];
        }
        p[i]=i;
    }

    int B=sqrt(ecnt);
    for(int i=1;i<=ecnt;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+m+1,Cmp);

    map<int,int> mp;int vcnt=0;
    for(int i=1;i<=n;i++){
        if(!mp[a[i]]) mp[a[i]]=++vcnt;
        a[i]=mp[a[i]];
    }
    // for(int i=1;i<=ecnt;i++) cout<<a[eu[i]]<<' ';cout<<endl;
    for(int i=1,l=1,r=0,res=0;i<=m;i++){
        while(r<qr[p[i]]) Ins(eu[++r],res);
        while(l>ql[p[i]]) Ins(eu[--l],res);
        while(r>qr[p[i]]) Ins(eu[r--],res);
        while(l<ql[p[i]]) Ins(eu[l++],res);
        if(lca[p[i]]) Ins(lca[p[i]],res);
        ans[p[i]]=res;
        if(lca[p[i]]) Ins(lca[p[i]],res);
        // cout<<ql[p[i]]<<' '<<qr[p[i]]<<' '<<lca[p[i]]<<endl;
        // for(int j=1;j<=vcnt;j++) cout<<cnt[i]<<' ';cout<<endl;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
=======

vector<int> Eul;
int st[N],ed[N];
int fa[N][21],dep[N];
void dfs(int x){
    st[x]=Eul.size();
    Eul.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(dep[y]) continue ;
        fa[y][0]=x;
        dep[y]=dep[x]+1;
        dfs(y);
    }
    ed[x]=Eul.size();
    Eul.push_back(x);
}
void Init(int n){
    for(int k=1;k<20;k++){
        for(int i=1;i<=n;i++){
            fa[i][k]=fa[fa[i][k-1]][k-1];
        }
    }
}
int Lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=19;~k;k--){
        if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    }
    if(x==y) return x;
    for(int k=19;~k;k--){
        if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[x][k];
    }
    return fa[x][0];
}

map<int,int> mp;
int a[N],blk[N];

struct Q{
    int l,r,u,v,id;
    bool operator <(Q x){
        if(blk[l]!=blk[x.l]) return blk[l]<blk[x.l];
        else return r<x.r;
    }
}q[N];

int c[N];bool vis[N];
void Modify(int &ans,int x){
    int k=a[x];
    if(vis[x]){
        vis[x]=0;
        c[k]--;
        if(!c[k]) ans--/*,cout<<"~"<<k<<endl*/;
    }else{
        vis[x]=1;
        if(!c[k]) ans++/*,cout<<"+"<<k<<endl*/;
        c[k]++;
    }
}
int res[N];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1,cnt=0;i<=n;i++){
        int x;
        cin>>x;
        if(!mp[x]) mp[x]=++cnt;
        a[i]=mp[x];
    }

    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        adeg(x,y);
        adeg(y,x);
    }

    // fa[1][0]=-1;
    dep[1]=1;
    dfs(1);
    Init(n);
    int B=sqrt(m);
    for(int i=1;i<=(n<<1);i++) blk[i]=(i-1)/B+1;

    // for(int i=0;i<Eul.size();i++) cout<<Eul[i]<<'/'<<a[Eul[i]]<<' ';cout<<endl;

    for(int i=1;i<=m;i++){
        cin>>q[i].u>>q[i].v;
        if(st[q[i].u]>st[q[i].v]) swap(q[i].u,q[i].v);
        if(ed[q[i].u]<ed[q[i].v]) q[i].l=ed[q[i].u],q[i].r=st[q[i].v];
        else q[i].l=st[q[i].u],q[i].r=st[q[i].v];
        q[i].id=i;
    }
    sort(q+1,q+m+1);

    for(int i=1,ans=0,l=0,r=-1;i<=m;i++){
        // cout<<q[i].l<<' '<<q[i].r<<' '<<q[i].u<<' '<<q[i].v<<' '<<q[i].id<<endl;

        while(l>q[i].l) Modify(ans,Eul[--l]);
        while(r<q[i].r) Modify(ans,Eul[++r]);
        while(l<q[i].l) Modify(ans,Eul[l++]);
        while(r>q[i].r) Modify(ans,Eul[r--]);

        int Lc=Lca(q[i].u,q[i].v);

        // cout<<Lc<<endl;

        if(Lc!=q[i].u&&Lc!=q[i].v) Modify(ans,Lc);
        res[q[i].id]=ans;
        if(Lc!=q[i].u&&Lc!=q[i].v) Modify(ans,Lc);
    }

    for(int i=1;i<=m;i++) cout<<res[i]<<endl;
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db

    return 0;
}