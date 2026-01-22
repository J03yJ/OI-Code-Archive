#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;
const int mod=998244353;

struct Node{
    int lc,rc,siz,dat,rev,add;
    inline Node(){}
    inline Node(int l,int r,int s,int d){lc=l,rc=r,siz=s,dat=d;}
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define dat(x) tr[x].dat
#define rev(x) tr[x].rev
#define add(x) tr[x].add

int trs[N<<5],cnt,top;
inline int Allc(){return top?trs[top--]:++cnt;}
inline int Allc(int l,int r,int s,int d){
    int x=Allc();
    tr[x]=Node(l,r,s,d);
    return x;
}
inline int Allc(int d){return Allc(0,0,1,d);}
inline int Bind(int x,int y){return Allc(lc(x),rc(y),siz(x)+siz(y),(dat(x)+dat(y))%mod);}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void PushUp(int x){
    if(!lc(x)) siz(x)=1;
    else siz(x)=siz(lc(x))+siz(rc(x)),dat(x)=dat(lc(x))+dat(rc(x));
}
inline void PushAdd(int &x,int k){
    x=Clone(x);
    dat(x)=(dat(x)+1ll*siz(x)*k%mod)%mod;
    add(x)=(add(x)+k)%mod;
}
inline void PushRev(int &x){
    x=Clone(x);
    rev(x)^=1,swap(lc(x),rc(x));
}
inline void PushDown(int x){
    if(!lc(x)) return ;
    if(rev(x)) PushRev(lc(x)),PushRev(rc(x)),rev(x)=0;
    PushAdd(lc(x),add(x)),PushAdd(rc(x),add(x)),add(x)=0;
}

inline int Merge(int x,int y){
    if(!x||!y) return x|y;
    if(min(siz(x),siz(y))*4>=siz(x)+siz(y)) return Bind(x,y);
    if(siz(x)>siz(y)){
        PushDown(x);
        if(siz(lc(x))*4>=siz(x)+siz(y)) return Merge(lc(x),Merge(rc(x),y));
        else return PushDown(rc(x)),Merge(Merge(lc(x),rc(lc(x))),Merge(rc(rc(x)),y));
    }else{
        PushDown(y);
        if(siz(rc(x))*4>=siz(x)+siz(y)) return Merge(Merge(x,lc(y)),rc(y));
        else return PushDown(lc(x)),Merge(Merge(x,lc(lc(y))),Merge(rc(lc(y)),rc(y)));
    }
}

signed main(){

    return 0;
}