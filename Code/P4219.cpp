#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

struct Node{
    int fa,son[2],siz,vsiz,rev;
}tr[N];
#define fa(x) tr[x].fa
#define son(x,k) tr[x].son[k]
#define siz(x) tr[x].siz
#define vsiz(x) tr[x].vsiz
#define rev(x) tr[x].rev

#define IsRoot(x) (son(fa(x),0)!=(x)&&son(fa(x),1)!=(x))
inline void Push(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
inline void PushDown(int x){if(rev(x)) Push(son(x,0)),Push(son(x,1)),rev(x)=0;}
inline void PushUp(int x){siz(x)=siz(son(x,0))+siz(son(x,1))+vsiz(son(x,0))+vsiz(son(x,1))+1;}
inline void Update(int x){
    if(!IsRoot(x)) Update(fa(x));
    PushDown(x);
}

#define Id(x) ((x)==son(fa(x),1))
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
    for(;x;p=x,x=fa(x)){
        Splay(x);
        if(son(x,1)) vsiz(x)+=siz(son(x,1))+vsiz(son(x,1));
        son(x,1)=p;
        if(p) vsiz(x)-=siz(p)+vsiz(p);
        PushUp(x);
    }
    return p;
}
inline void MakeRoot(int x){Push(Access(x)),Splay(x);}
inline void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
inline void Link(int x,int y){
    Split(x,y),fa(x)=y,vsiz(y)+=siz(x)+vsiz(x);
}

int n,q;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) siz(i)=1;

    while(q--){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='A') Link(x,y);
        else{
            Split(x,y);
            cout<<1ll*(siz(x)+vsiz(x))*(siz(y)+vsiz(y)-siz(x)-vsiz(x))<<endl;
        }
    }

    return 0;
}