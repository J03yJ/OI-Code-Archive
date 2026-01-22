#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=1e5+9;
const int M=1e6+9;

struct Node{
    int fa,son[2],rev;
    pii dat,val;
}tr[N+M];
#define fa(x) tr[x].fa
#define son(x,k) tr[x].son[k]
#define dat(x) tr[x].dat
#define val(x) tr[x].val
#define rev(x) tr[x].rev

inline bool IsRoot(int x){return son(fa(x),0)!=x&&son(fa(x),1)!=x;}
inline void Push(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
inline void PushDown(int x){if(rev(x)) Push(son(x,0)),Push(son(x,1)),rev(x)=0;}
inline void PushUp(int x){dat(x)=max(val(x),max(dat(son(x,0)),dat(son(x,1))));}
inline void Update(int x){
    if(!IsRoot(x)) Update(fa(x));
    PushDown(x);
}

inline bool Id(int x){return x==son(fa(x),1);}
inline void Rotate(int x){
    int y=fa(x),z=fa(y),f=Id(x);
    if(!IsRoot(y)) son(z,Id(y))=x;
    son(y,f)=son(x,!f),fa(son(x,!f))=y,PushUp(y);
    son(x,!f)=y,fa(y)=x,PushUp(x);
    fa(x)=z;
}
inline void Splay(int x){
    Update(x);
    for(int y=fa(x);!IsRoot(x);Rotate(x),y=fa(x)){
        if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
    }
}

inline int Access(int x){
    int p=0;
    for(;x;p=x,x=fa(x)) Splay(x),son(x,1)=p,PushUp(x);
    return p;
}
inline void MakeRoot(int x){Push(Access(x)),Splay(x);}
inline void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
inline void Cut(int x,int y){Split(x,y),fa(x)=son(y,0)=0,PushUp(y);}
inline void Link(int x,int y){Split(x,y),fa(x)=y;}

int u[M],v[M],t[M],ban[M],n,m,q;
int op[N],qu[N],qv[N],id[N],ans[N];

int vis[N],fa[N],a[N];
vector<pii> e[N];
inline void Prim(){
    priority_queue<pii> q;
    t[0]=1e9+7;
    q.push({0,1});
    while(q.size()){
        int x=sec(q.top());
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(pii p:e[x]){
            if(vis[fir(p)]) continue ;
            if(t[sec(p)]<t[a[fir(p)]]){
                fa[fir(p)]=x;
                a[fir(p)]=sec(p);
                q.push({-t[sec(p)],fir(p)});
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>q;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>t[i];
    for(int i=1;i<=q;i++) cin>>op[i]>>qu[i]>>qv[i];

    map<pii,int> mp;
    for(int i=1;i<=m;i++) mp[{u[i],v[i]}]=mp[{v[i],u[i]}]=i;
    for(int i=1;i<=q;i++) if(op[i]==2) ban[id[i]=mp[{qu[i],qv[i]}]]=1;
    for(int i=1;i<=m;i++){
        if(ban[i]) continue ;
        e[u[i]].push_back({v[i],i});
        e[v[i]].push_back({u[i],i});
    }

    Prim();
    for(int i=1;i<=m;i++) dat(i+n)=val(i+n)={t[i],i};
    for(int i=2;i<=n;i++) Link(u[a[i]],n+a[i]),Link(v[a[i]],n+a[i]);
    for(int i=q;i>=1;i--){
        Split(qu[i],qv[i]);
        pii mx=dat(qv[i]);
        if(op[i]==1) ans[i]=fir(mx);
        else{
            int k=t[id[i]];
            if(k>=fir(mx)) continue ;
            int p=u[sec(mx)],q=v[sec(mx)];
            Cut(p,n+sec(mx)),Cut(q,n+sec(mx));
            Link(u[id[i]],n+id[i]),Link(v[id[i]],n+id[i]);
        }
    }

    for(int i=1;i<=q;i++) if(op[i]==1) cout<<ans[i]<<endl;

    return 0;
}