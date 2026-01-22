#include<bits/stdc++.h>

using namespace std;

ifstream fin("bottle.in");
ofstream fout("bottle.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}

inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){dat(x)=Add(dat(x<<1),dat(x<<1|1));}
inline void Push(int x,int k){tag(x)=1ll*k*tag(x)%mod,dat(x)=1ll*k*dat(x)%mod;}
inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=1;}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,tag(x)=1;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Set(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(pos<=mid) Set(x<<1,pos,k);
    else Set(x<<1|1,pos,k);
    PushUp(x);
}
inline void Mut(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Mut(x<<1,l,r,k);
    if(r>mid) Mut(x<<1|1,l,r,k);
    PushUp(x);
}

int a[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    return 0;
}