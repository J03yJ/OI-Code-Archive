#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int lgV=2e1;

struct Node{
    int son[2],dat,siz;
<<<<<<< HEAD
}tr[N<<6];
=======
}tr[N<<2];
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
#define son(x,k) tr[x].son[k]
#define dat(x) tr[x].dat
#define siz(x) tr[x].siz
int trs[N],top,cnt;
<<<<<<< HEAD
inline int Allc(){return ++cnt;}
inline void PushUp(int x){
    siz(x)=siz(son(x,0))+siz(son(x,1));
    dat(x)=((dat(son(x,0))^dat(son(x,1)))<<1)|(siz(son(x,1))&1);
}
inline void Insert(int &x,int k,int dep){
    if(!x) x=Allc();
    if(dep>lgV) return siz(x)^=1,dat(x)=0,void();
=======
inline int Allc(){return top?trs[top--]:cnt;}
inline void PushUp(int x){
    siz(x)=siz(son(x,0))+siz(son(x,1));
    dat(x)=(dat(son(x,0))^dat(son(x,1)))<<1|siz(x)&1;
}
inline void Insert(int &x,int k,int dep){
    if(!x) x=Allc();
    if(dep>=lgV) return siz(x)^=1,dat(x)^=1,void();
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    Insert(son(x,k&1),k>>1,dep+1);
    PushUp(x);
}
inline void Shift(int x){
    if(!x) return ;
    Shift(son(x,1));
    swap(son(x,0),son(x,1));
    PushUp(x);
}

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int a[N],fa[N],tag[N],rt[N],n,m;
void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
<<<<<<< HEAD
        if(y==fa[x]) continue ;
=======
        if(y==fa[i]) continue ;
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
        fa[y]=x;
        DFS(y);
    }
}
<<<<<<< HEAD
inline int At(int x){return tag[fa[x]]+a[x];}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

=======

int main(){
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    cin>>n>>m;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    DFS(1);
<<<<<<< HEAD
    for(int i=1;i<=n;i++) if(fa[i]) Insert(rt[fa[i]],At(i),0);

    while(m--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            tag[x]++,Shift(rt[x]);
            if(fa[fa[x]]) Insert(rt[fa[fa[x]]],At(fa[x]),0);
            if(fa[x]) a[fa[x]]++;
            if(fa[fa[x]]) Insert(rt[fa[fa[x]]],At(fa[x]),0);
        }else if(op==2){
            int v;
            cin>>v;
            if(fa[x]) Insert(rt[fa[x]],At(x),0);
            a[x]-=v;
            if(fa[x]) Insert(rt[fa[x]],At(x),0);
        }else if(op==3){
            int ans=dat(rt[x]);
            if(fa[x]) ans^=At(fa[x]);
            cout<<ans<<endl;
        }
=======

    for(int i=1;i<=n;i++){
        for(int j=fi[i];j;j=ne[j]){
            int k=to[j];
            if(k==fa[i]) continue ;
            Insert(rt[i],a[k],0);
        }
    }

    while(m--){
        
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    }

    return 0;
}