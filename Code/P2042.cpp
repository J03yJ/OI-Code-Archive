#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const long long inf=1e18;

struct Data{
    long long lmx,rmx,mx,sum;
    Data(){}
    Data(long long x){lmx=rmx=mx=sum=0;}
    Data(long long _lmx,long long _rmx,long long _mx,long long _sum){
        lmx=_lmx,rmx=_rmx;mx=_mx;sum=_sum;
    }
    Data operator +(Data x){
        Data tmp(lmx,x.rmx,rmx+x.lmx,sum+x.sum);
        tmp.mx=max(tmp.mx,max(mx,x.mx));
        if(lmx==sum) tmp.lmx=max(tmp.lmx,x.lmx+sum);
        if(x.rmx==sum) tmp.rmx=max(tmp.rmx,rmx+x.sum);
    }
};
struct Node{
    int lc,rc;
    int dep,siz,rtag,atag;
    Data dat;
}tr[N<<6];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat
#define dep(x) tr[x].dep
#define siz(x) tr[x].siz
#define rtag(x) tr[x].rtag
#define atag(x) tr[x].atag

int trs[N],cnt,top;
inline int New(){
    if(top) return trs[top--];
    else return ++cnt;
}
inline void Del(int x){
    dep(x)=siz(x)=rtag(x)=0;
    dat(x)=Data(0);
    trs[++top]=x;
}
inline void Push(int x,int t){
    atag(x)=t;
    dat(x)=Data(t*siz(x));
}
inline void PushUp(int x){
    if(!lc(x)) dep(x)=1,siz(x)=1;
    else{
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        siz(x)=siz(lc(x))+siz(rc(x));
        dat(x)=max(dat(lc(x)),dat(rc(x)));
    }
}
inline void PushDown(int x){
    if(!lc(x)) return ;
    if(rtag(x)){
        rtag(lc(x))^=1;
        rtag(rc(x))^=1;
        swap(lc(x),rc(x));
        rtag(x)=0;
    }
}
inline int Bind(int x,int y){
    if(!x||!y) return x|y;
    int z=New();
    lc(z)=x,rc(z)=y;
    PushUp(z);
    return z;
}

void Rotate(int x,int flag){
    if(!flag){
        int y=lc(x);
        PushDown(y);
        lc(x)=lc(y);
        lc(y)=rc(y);
        rc(y)=rc(x);
        rc(x)=y;
        PushUp(y);
    }else{
        int y=rc(x);
        PushDown(y);
        rc(x)=rc(y);
        rc(y)=lc(y);
        lc(y)=lc(x);
        lc(x)=y;
        PushUp(y);
    }
    PushUp(x);
}
void Maintain(int x){
    PushDown(x);
    if(dep(lc(x))>dep(rc(x))+1){
        if(dep(lc(lc(x)))==dep(rc(x))) Rotate(lc(x),1);
        Rotate(x,0);
    }else if(dep(rc(x))>dep(lc(x))+1){
        if(dep(rc(rc(x)))==dep(lc(x))) Rotate(rc(x),0);
        Rotate(x,1);
    }else PushUp(x);
}

int n,m;
int Make(int l,int r,vector<int> &a){
    if(l==r){
        int x=New();
        dep(x)=siz(x)=1;
        dat(x)=Data(a[l]);
        return x;
    }
    int mid=l+r>>1;
    return Bind(Make(l,mid,a),Make(mid+1,r,a));
}
int Merge(int x,int y){
    if(abs(dep(x)-dep(y))<=1) return Bind(x,y);
    if(dep(x)<dep(y)){
        PushDown(y);
        lc(y)=Merge(x,lc(y));
        Maintain(y);
        return y;
    }else{
        PushDown(x);
        rc(x)=Merge(rc(x),y);
        Maintain(x);
        return x;
    }
}
pair<int,int> Split(int x,int k){
    if(!k) return {0,x};
    if(!lc(x)) return {x,0};
    PushDown(x);
    Del(x);
    if(k<=siz(lc(x))){
        pair<int,int> res=Split(lc(x),k);
        return {res.first,Merge(res.second,rc(x))};
    }else{
        pair<int,int> res=Split(rc(x),k-siz(lc(x)));
        return {Merge(lc(x),res.first),res.second};
    }
}
int Reverse(int x,int l,int r){
    pair<int,int> rt=Split(x,r);
    pair<int,int> lrt=Split(rt.first,l-1);
    rtag(lrt.second)^=1;
    return Merge(Merge(lrt.first,lrt.second),rt.second);
}
int Insert(int x,int pos,vector<int> &a){
    pair<int,int> rt=Split(x,pos);
    return Merge(Merge(rt.first,Make(0,a.size()-1,a)),rt.second);
}
int Erase(int x,int pos,int cnt){
    pair<int,int> rt=Split(x,pos);
    pair<int,int> rrt=Split(rt.second,cnt);
    return Merge(rt.first,rrt.second);
}
Data Query(int x,int l,int r){
    if(l<=1&&r>=siz(x)) return dat(x);
    PushDown(x);
    int mid=siz(lc(x));
    if(l<=mid&&r>mid) return Query(lc(x),l,r)+Query(rc(x),l-mid,r-mid);
    else if(l<=mid) return Query(lc(x),l,r);
    else return Query(rc(x),l-mid,r-mid);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    return 0;
}