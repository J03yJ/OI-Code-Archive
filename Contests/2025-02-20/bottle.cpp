#include<bits/stdc++.h>

using namespace std;

ifstream fin("bottle.in");
ofstream fout("bottle.out");
#define cin fin
#define cout fout

const int N=1e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
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

struct Data{
    int f,g,c,w;
    inline Data(){}
    inline Data(int _f,int _g,int _c,int _w){f=_f,g=_g,c=_c,w=_w;}
    inline void Set(int _f,int _g,int _c,int _w){f=_f,g=_g,c=_c,w=_w;}
    inline Data operator +(Data x){
        return Data(Add(f,x.f),Add(g,x.g),Add(c,x.c),Add(w,x.w));
    }
    inline Data operator *(int k){
        return Data(1ll*f*k%mod,1ll*g*k%mod,1ll*c*k%mod,1ll*w*k%mod);
    }
};

struct Node{
    int l,r,tag;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
inline void Push(int x,int k){dat(x)=dat(x)*k,tag(x)=1ll*tag(x)*k%mod;}
inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=1;}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,tag(x)=1;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Set(int x,int pos,Data k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(pos<=mid) Set(x<<1,pos,k);
    else Set(x<<1|1,pos,k);
    PushUp(x);
}
inline void Mul(int x,int l,int r,int k){
    if(l>r) return ;
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Mul(x<<1,l,r,k);
    if(r>mid) Mul(x<<1|1,l,r,k);
    PushUp(x);
}
inline Data Query(int x,int l,int r){
    if(l>r) return Data(0,0,0,0);
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int a[N],ans[N],cnt[N],w[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++) AddAs(cnt[a[i]],1),AddAs(w[a[i]],a[i]);
    for(int i=1;i<=n;i++) AddAs(cnt[i],cnt[i-1]),AddAs(w[i],w[i-1]);

    const int p=Inv(n-1);
    Build(1,1,n);
    for(int i=1;i<=n;i++){
        if(i==1) Set(1,a[i],Data(1,a[i],1ll*a[i]*cnt[a[i]]%mod,w[a[i]]));
        else{
            Mul(1,1,a[i],1+p);
            int tmp=Add(Query(1,a[i],a[i]).f,1ll*p*Query(1,a[i]+1,n).f%mod);
            Set(1,a[i],Data(tmp,1ll*tmp*a[i]%mod,1ll*tmp*a[i]%mod*cnt[a[i]]%mod,1ll*tmp*w[a[i]]%mod));
        }
        AddAs(ans[i],Sub(Query(1,1,a[i]).c,Query(1,1,a[i]).w));
        if(i<n) SubAs(ans[i+1],Sub(Query(1,1,a[i+1]).c,Query(1,1,a[i+1]).w));;
        SubAs(ans[i],Add(Query(1,1,a[i]).g,1ll*a[i]*Query(1,a[i]+1,n).f%mod));
    }
    for(int i=1;i<=n;i++){
        AddAs(ans[i],Add(Query(1,1,a[i]).g,1ll*a[i]*Query(1,a[i]+1,n).f%mod));
        cout<<1ll*p*ans[i]%mod<<endl;
    }

    return 0;
}