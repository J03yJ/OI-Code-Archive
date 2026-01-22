#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int inf=1e9+7;

int u[N],v[N],a[N],b[N],p[N],val[N<<1],n,m;

struct Node{
    int son[2],fa,rev,maxx;
}tr[N<<1];
#define son(x,k) tr[x].son[k]
#define fa(x) tr[x].fa
#define rev(x) tr[x].rev
#define maxx(x) tr[x].maxx

inline bool IsRoot(int x){return son(fa(x),0)!=x&&son(fa(x),1)!=x;}
inline void PushUp(int x){
    maxx(x)=x;
    if(son(x,0)&&val[maxx(son(x,0))]>val[maxx(x)]) maxx(x)=maxx(son(x,0)); 
    if(son(x,1)&&val[maxx(son(x,1))]>val[maxx(x)]) maxx(x)=maxx(son(x,1)); 
}
inline void Push(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
inline void PushDown(int x){if(rev(x)) Push(son(x,0)),Push(son(x,1)),rev(x)=0;}
inline void PushAll(int x){
    if(!IsRoot(x)) PushAll(fa(x));
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
    PushAll(x);
    for(int y=fa(x);!IsRoot(x);Rotate(x),y=fa(x)){
        if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
    }
}
inline int Access(int x){
    int p=0;
    while(x){
        Splay(x);
        son(x,1)=p;
        PushUp(x);
        p=x,x=fa(x);
    }
    return p;
}
inline void MakeRoot(int x){Push(Access(x)),Splay(x);}
inline void Link(int x,int y){MakeRoot(x),Splay(x),fa(x)=y;}
inline void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
inline void Cut(int x,int y){Split(x,y),son(y,0)=fa(x)=0;}
inline int FindRoot(int x){
    Access(x),Splay(x);
    PushDown(x);
    while(son(x,0)) PushDown(x=son(x,0));
    Splay(x);
    return x;
}
inline bool Check(int x,int y){return MakeRoot(x),FindRoot(y)==x;}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>a[i]>>b[i];
    iota(p+1,p+m+1,1);
    sort(p+1,p+m+1,[](int i,int j){return a[i]<a[j];});

    int ans=inf;
    for(int i=1;i<=m;i++) val[n+i]=b[i];
    for(int i=0;i<=n;i++) val[i]=-inf;
    for(int i=1;i<=n+m;i++) maxx(i)=i;
    for(int i=1;i<=m;i++){
        int j=p[i];
        if(u[j]==v[j]) continue ;
        if(!Check(u[j],v[j])) Link(u[j],n+j),Link(n+j,v[j]);
        else{
            Split(u[j],v[j]);
            int k=maxx(v[j])-n;
            if(b[k]>b[j]){
                Splay(k+n);
                fa(son(k+n,0))=fa(son(k+n,1))=0;
                Link(u[j],n+j),Link(n+j,v[j]);
            }
        }
        if(Check(1,n)) Split(1,n),ans=min(ans,val[maxx(n)]+a[j]);
    }

    cout<<(ans==inf?-1:ans)<<endl;

    return 0;
}