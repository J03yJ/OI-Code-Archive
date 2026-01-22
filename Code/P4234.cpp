#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int inf=1e9+7;

int u[N],v[N],w[N],p[N],val[N<<1],n,m;

struct Node{
    int son[2],fa,rev,minx;
}tr[N<<1];
#define son(x,k) tr[x].son[k]
#define fa(x) tr[x].fa
#define rev(x) tr[x].rev
#define minx(x) tr[x].minx

inline bool IsRoot(int x){return son(fa(x),0)!=x&&son(fa(x),1)!=x;}
inline void PushUp(int x){
    minx(x)=x;
    if(son(x,0)&&val[minx(son(x,0))]<val[minx(x)]) minx(x)=minx(son(x,0)); 
    if(son(x,1)&&val[minx(son(x,1))]<val[minx(x)]) minx(x)=minx(son(x,1)); 
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
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i];
    iota(p+1,p+m+1,1);
    sort(p+1,p+m+1,[](int i,int j){return w[i]<w[j];});

    int ans=inf;
    for(int i=1;i<=m;i++) val[n+i]=w[i];
    for(int i=0;i<=n;i++) val[i]=inf;
    for(int i=1;i<=n+m;i++) minx(i)=i;
    multiset<int> s;
    for(int i=1,cnt=0;i<=m;i++){
        int j=p[i];
        if(u[j]==v[j]) continue ;
        if(!Check(u[j],v[j])){
            cnt++;
            s.insert(w[j]);
            Link(u[j],n+j),Link(n+j,v[j]);
        }else{
            Split(u[j],v[j]);
            int k=minx(v[j])-n;
            if(w[k]<w[j]){
                s.erase(s.lower_bound(w[k]));
                Splay(k+n);
                fa(son(k+n,0))=fa(son(k+n,1))=0;
                s.insert(w[j]);
                Link(u[j],n+j),Link(n+j,v[j]);
            }
        }
        if(cnt==n-1) ans=min(ans,*s.rbegin()-*s.begin());
    }

    cout<<ans<<endl;

    return 0;
}