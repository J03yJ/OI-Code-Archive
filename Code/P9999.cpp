#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
#define endl '\n'
using pii=pair<int,int>;
const int N=1e6+9;
const int inf=1e9+7;
template<class S,class T> inline void ChMax(S &x,T y){if(y>x) x=y;}
template<class S,class T> inline void ChMin(S &x,T y){if(y<x) x=y;}

mt19937 rng(4649);

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int siz[N],fa[N],hson[N],dep[N];
inline void DFS1(int x){
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
int top[N],dfn[N],idfn[N],dcnt;
inline void DFS2(int x,int t){
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    top[x]=t;
    if(hson[x]) DFS2(hson[x],t);
    else return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
}

int f[N<<2];
inline void InitDSU(int lim){for(int i=1;i<=lim;i++) f[i]=i;}
inline int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}
inline void Union(int x,int y){f[Find(y)]=Find(x);}

struct Node{
    int lc,rc,fa,dat,tag,qid,prio;
}tr[N<<2];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define fa(x) tr[x].fa
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag
#define qid(x) tr[x].qid
#define prio(x) tr[x].prio

int cnt;
inline int Allc(){return ++cnt;}
inline void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
inline void PushDown(int x){
    if(lc(x)) Push(lc(x),tag(x));
    if(rc(x)) Push(rc(x),tag(x));
    tag(x)=0;
}
inline void PushUp(int x){
    fa(x)=0;
    if(lc(x)) fa(lc(x))=x;
    if(rc(x)) fa(rc(x))=x;
}
inline int Merge(int x,int y){
    if(!x||!y) return x|y;
    if(prio(x)>prio(y)){
        PushDown(x);
        rc(x)=Merge(rc(x),y);
        return PushUp(x),x;
    }else{
        PushDown(y);
        lc(y)=Merge(x,lc(y));
        return PushUp(y),y;
    }
}
inline pii Split(int x,int k){
    if(!x) return {0,0};
    PushDown(x);
    if(k>=dat(x)){
        pii res=Split(rc(x),k);
        rc(x)=fir(res);
        PushUp(x);
        return {x,sec(res)};
    }else{
        pii res=Split(lc(x),k);
        lc(x)=sec(res);
        PushUp(x);
        return {fir(res),x};
    }
}
inline int FindL(int x){while(lc(x)) PushDown(x),x=lc(x);return x;}
inline int FindR(int x){while(rc(x)) PushDown(x),x=rc(x);return x;}
inline int Join(int x,int y){
    if(!x||!y) return x|y;
    int u=FindR(x),v=FindL(y);
    if(dat(u)==dat(v)){
        y=sec(Split(y,dat(v)));
        Union(qid(u),qid(v));
    }else assert(dat(u)<dat(v));
    return Merge(x,y);
}
inline int Insert(int &rt,int k,int id){
    int x=Allc();
    dat(x)=k,qid(x)=id,prio(x)=rng();
    pii tmp=Split(rt,k);
    rt=Merge(Join(fir(tmp),x),sec(tmp));
    return x;
}
inline void PushAll(int x){
    if(!x) return ;
    PushAll(fa(x));
    PushDown(x);
}

int a[N],ql[N],qr[N],qx[N],nid[N],ans[N],n,m,q;
vector<int> st[N],ed[N];

int lst[N],rt[N];
set<pii> hp;
inline void Erase(int x){
    if(lst[x]) hp.erase({lst[x],x}),lst[x]=0;
}
inline void Insert(int x){
    if(rt[x]){
        lst[x]=dat(FindL(rt[x]))-dfn[x]+1;
        hp.insert({lst[x],x});
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m>>q;
    for(int i=2;i<=n;i++) cin>>fa[i],AddEdge(fa[i],i);
    for(int i=1;i<=m;i++) cin>>a[i];
    for(int i=1;i<=q;i++){
        cin>>ql[i]>>qr[i]>>qx[i];
        st[ql[i]].push_back(i);
        ed[qr[i]].push_back(i);
    }
    
    InitDSU(q);
    DFS1(1),DFS2(1,1);
    for(int t=0;t<m;){
        for(int i:st[t+1]){
            Erase(top[qx[i]]);
            nid[i]=Insert(rt[top[qx[i]]],dfn[qx[i]]+t,i);
            Insert(top[qx[i]]);
        }
        int u=a[t+1],v=a[t+1];
        while(u){
            Erase(top[u]);
            pii tmp=Split(rt[top[u]],dfn[u]+t);
            rt[top[u]]=sec(tmp);
            tmp=Split(fir(tmp),dfn[u]+t-1);
            Push(fir(tmp),2);
            if(sec(tmp)){
                int x=sec(tmp);
                tag(x)=0,dat(x)=dfn[v]+t+1;
                rt[top[v]]=Join(x,rt[top[v]]);
            }
            rt[top[u]]=Join(fir(tmp),rt[top[u]]);
            u=fa[v=top[u]];
        }
        t++;
        while(hp.size()&&fir(*hp.begin())==t){
            int p=sec(*hp.begin()),q=top[fa[p]];
            Erase(p),Erase(q);
            pii tmp=Split(rt[p],t+dfn[p]-1);
            rt[p]=sec(tmp);
            int x=fir(tmp);
            tag(x)=0,dat(x)=dfn[fa[p]]+t;
            tmp=Split(rt[q],dfn[fa[p]]+t);
            rt[q]=Merge(Join(fir(tmp),x),sec(tmp));
            Insert(p),Insert(q);
        }
        u=top[a[t]];
        while(u) Insert(u),u=top[fa[u]];
        for(int i:ed[t]){
            int x=nid[Find(i)];
            PushAll(x);
            ans[i]=idfn[dat(x)-t];
        }
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
    
    return 0;
}