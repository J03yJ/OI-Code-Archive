#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int lgN=2e1;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int elr[N<<1],pos[N],sop[N],dep[N],fa[N],ecnt,n,m;
inline void DFS(int x){
    elr[++ecnt]=x,pos[x]=ecnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        dep[y]=dep[x]+1;
        fa[y]=x;
        DFS(y);
        elr[++ecnt]=x;
    }
    sop[x]=ecnt;
}
int mn[N<<1][lgN],lg[N<<1];
inline void InitLCA(){
    for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
    for(int k=1;k<=lg[ecnt];k++){
        for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
    }
}
inline int LCA(int x,int y){
    x=pos[x],y=pos[y];
    if(x>y) swap(x,y);
    int k=lg[y-x+1];
    return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
}

namespace SgT{
    struct Node{
        int l,r,dat,tag;
    }tr[N<<3];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag

    inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
    inline void Push(int x,int k){tag(x)+=k;dat(x)+=k;}
    inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}

    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r;
        if(l(x)==r(x)){
            dat(x)=pos[elr[l(x)]]==l(x)?dep[elr[l(x)]]:0;
            return ;
        }
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        PushUp(x);
    }
    inline void Modify(int x,int l,int r,int k){
        if(l<=l(x)&&r(x)<=r) return Push(x,k);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    inline int Query(int x,int l,int r){
        if(!l||l>r) return 0;
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid&&r>mid) return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
        else if(l<=mid) return Query(x<<1,l,r);
        else return Query(x<<1|1,l,r);
    }
}

namespace LCT{
    struct Node{
        int fa,son[2],rev;
    }tr[N];
    #define fa(x) tr[x].fa
    #define son(x,k) tr[x].son[k]
    #define rev(x) tr[x].rev

    inline bool IsRoot(int x){return son(fa(x),0)!=x&&son(fa(x),1)!=x;}
    inline void Push(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
    inline void PushDown(int x){if(rev(x)) Push(son(x,0)),Push(son(x,1)),rev(x)=0;}
    inline void Update(int x){
        if(!IsRoot(x)) Update(fa(x));
        PushDown(x);
    }

    inline bool Id(int x){return x==son(fa(x),1);}
    inline void Rotate(int x){
        int y=fa(x),z=fa(y),f=Id(x);
        if(!IsRoot(y)) son(z,Id(y))=x;
        son(y,f)=son(x,!f),fa(son(x,!f))=y;
        son(x,!f)=y,fa(y)=x;
        fa(x)=z;
    }
    inline void Splay(int x){
        Update(x);
        for(int y=fa(x);!IsRoot(x);Rotate(x),y=fa(x)){
            if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
        }
    }
    inline int Find(int x){
        int tmp=x;
        PushDown(x);
        while(son(x,0)) PushDown(x=son(x,0)); 
        return Splay(x),Splay(tmp),x;
    }
    inline void Access(int x){
        int p=0;
        for(;x;p=x,x=fa(x)){
            Splay(x);
            if(p){
                int y=Find(p);
                SgT::Modify(1,pos[y],sop[y],-1);
            }
            swap(son(x,1),p);
            if(p){
                int y=Find(p);
                SgT::Modify(1,pos[y],sop[y],1);
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);

    dep[1]=1,DFS(1);
    InitLCA();
    SgT::Build(1,1,ecnt);
    for(int i=1;i<=n;i++) LCT::fa(i)=fa[i];

    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int x;
            cin>>x;
            LCT::Access(x);
        }else if(op==2){
            int x,y;
            cin>>x>>y;
            int lca=LCA(x,y);
            cout<<SgT::Query(1,pos[x],pos[x])+SgT::Query(1,pos[y],pos[y])-2*SgT::Query(1,pos[lca],pos[lca])+1<<endl;
        }else if(op==3){
            int x;
            cin>>x;
            cout<<SgT::Query(1,pos[x],sop[x])<<endl;
        }
    }

    return 0;
}