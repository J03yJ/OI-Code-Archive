#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int a[N],n;

struct Node{
    int l,r,sum,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define sum(x) tr[x].sum
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){
    sum(x)=Add(sum(x<<1),sum(x<<1|1));
    dat(x)=Add(dat(x<<1),dat(x<<1|1));
}
inline void Push(int x,int k){MulAs(tag(x),k),MulAs(dat(x),k);}
inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=1;}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=sum(x)=0,tag(x)=1;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Set(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x)=Mul(tag(x),k),sum(x)=k,void();
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(pos<=mid) Set(x<<1,pos,k);
    else Set(x<<1|1,pos,k);
    PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
inline int Dat(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Add(Dat(x<<1,l,mid),Dat(x<<1|1,mid+1,r));
    else if(l<=mid) return Dat(x<<1,l,r);
    else return Dat(x<<1|1,l,r);
    PushUp(x); 
}
inline int Sum(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return sum(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Add(Sum(x<<1,l,mid),Sum(x<<1|1,mid+1,r));
    else if(l<=mid) return Sum(x<<1,l,r);
    else return Sum(x<<1|1,l,r);
    PushUp(x); 
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int ans=0;
    Build(1,1,n);
    for(int i=1;i<=n;i++){
        int pos=a[i];
        Set(1,pos,a[i]);
        AddAs(ans,Mul(i,Dat(1,pos,n)));
        SubAs(ans,Mul(i,Sum(1,pos,pos)));
        if(pos<n) Modify(1,pos+1,n,2);
    }
    Build(1,1,n);
    for(int i=1;i<=n;i++){
        int pos=n-a[i]+1;
        Set(1,pos,a[i]);
        SubAs(ans,Mul(i,Dat(1,pos,n)));
        AddAs(ans,Mul(i,Sum(1,pos,pos)));
        if(pos<n) Modify(1,pos+1,n,2);
    }
    Build(1,1,n);
    for(int i=n;i>=1;i--){
        int pos=a[i];
        Set(1,pos,a[i]);
        SubAs(ans,Mul(i,Dat(1,pos,n)));
        AddAs(ans,Mul(i,Sum(1,pos,pos)));
        if(pos<n) Modify(1,pos+1,n,2);
    }
    Build(1,1,n);
    for(int i=n;i>=1;i--){
        int pos=n-a[i]+1;
        Set(1,pos,a[i]);
        AddAs(ans,Mul(i,Dat(1,pos,n)));
        SubAs(ans,Mul(i,Sum(1,pos,pos)));
        if(pos<n) Modify(1,pos+1,n,2);
    }

    cout<<ans<<endl;

    return 0;
}