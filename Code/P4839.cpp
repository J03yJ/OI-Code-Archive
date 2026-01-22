#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e4+9;
const int B=31;

struct Basis{
    int b[B];
    Basis(){memset(b,0,sizeof b);}
    inline void Insert(int x){
        for(int i=B-1;~i;i--){
            if(~x>>i&1) continue ;
            if(!b[i]){
                b[i]=x;
                break ;
            }else x^=b[i];
        }
    }
    inline int Max(){
        int x=0;
        for(int i=B-1;~i;i--) x=max(x,x^b[i]);
        return x;
    }
    Basis operator +(Basis x){
        Basis res(x);
        for(int i=B-1;~i;i--) if(b[i]) res.Insert(b[i]);
        return res;
    }
};

struct Node{
    int l,r;
    Basis dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Insert(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x).Insert(k);
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Insert(x<<1,pos,k);
    else Insert(x<<1|1,pos,k);
    PushUp(x);
}
inline Basis Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Query(x<<1,l,mid)+Query(x<<1|1,mid+1,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int n,m;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>m>>n;
    Build(1,1,n);
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1) Insert(1,x,y);
        else cout<<Query(1,x,y).Max()<<endl;
    }

    return 0;
}