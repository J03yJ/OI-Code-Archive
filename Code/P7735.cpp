#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],adj,n;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
inline void ClearEdge(){
    for(int i=1;i<=n;i++) fi[i]=0;
    adj=0;
}

int fa[N],siz[N],dep[N],hson[N],m;
inline void DFS1(int x){
    siz[x]=1,hson[x]=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>=siz[hson[x]]) hson[x]=y;
    }
}
int top[N],dfn[N],idfn[N],dcnt;
inline void DFS2(int x,int t){
    top[x]=t;
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    if(hson[x]) DFS2(hson[x],t);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
}

struct Data{
    int lp,rp,ans;
    Data(){}
    Data(int _lp,int _rp,int _ans){lp=_lp,rp=_rp,ans=_ans;}
    Data operator +(Data x){return Data(lp,x.rp,ans+x.ans+(rp==x.lp));}
    Data operator -(){return Data(rp,lp,ans);}
};
struct Node{
    int l,r,tag;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define tag(x) tr[x].tag
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
inline void Push(int x,int k){if(k) tag(x)=k,dat(x)=Data(k,k,r(x)-l(x));}
inline void PushDown(int x){
    if(!x||!tag(x)) return ;
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=0;
}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,tag(x)=0;
    if(l(x)==r(x)) return dat(x)=Data(-l(x),-r(x),0),void();
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Assign(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Assign(x<<1,l,r,k);
    if(r>mid) Assign(x<<1|1,l,r,k);
    PushUp(x);
}
inline Data Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Query(x<<1,l,mid)+Query(x<<1|1,mid+1,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

inline void PAssign(int u,int v,int t){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        Assign(1,dfn[top[u]],dfn[u],t);
        u=fa[top[u]];
    }
    if(dep[u]>=dep[v]) swap(u,v);
    Assign(1,dfn[u],dfn[v],t);
}
inline int PQuery(int u,int v){
    Data up(0,0,0),vp(0,0,0);
    while(top[u]!=top[v]){
        if(dep[top[u]]>=dep[top[v]]){
            up=up+(-Query(1,dfn[top[u]],dfn[u]));
            u=fa[top[u]];
        }else{
            vp=Query(1,dfn[top[v]],dfn[v])+vp;
            v=fa[top[v]];
        }
    }
    if(dep[u]>=dep[v]) up=up+(-Query(1,dfn[v],dfn[u]));
    else vp=Query(1,dfn[u],dfn[v])+vp;
    return (up+vp).ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
        
        Build(1,1,n);
        DFS1(1),DFS2(1,1);
        for(int t=1;t<=m;t++){
            int op,u,v;
            cin>>op>>u>>v;
            if(op==1) PAssign(u,v,t);
            else cout<<PQuery(u,v)<<endl;
        }

        ClearEdge();
        dcnt=0;
    }

    return 0;
}