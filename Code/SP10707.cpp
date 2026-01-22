#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AddEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
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

    return 0;
}