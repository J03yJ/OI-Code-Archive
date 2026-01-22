#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=5e5+9;

int a[N],b[N],n;

namespace Max{
    struct Node{
        int l,r,dat,tag=-1;
    }tr[N<<3];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag

    inline void Push(int x,int k){dat(x)=tag(x)=k;}
    inline void PushDown(int x){if(~tag(x)) Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=-1;}
    inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
    inline void Build(int x,int l,int r){
        l(x)=l;r(x)=r;dat(x)=0;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    }
    inline void Modify(int x,int l,int r,int k){
        if(l<=l(x)&&r(x)<=r) return Push(x,k);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    inline int Query(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1,ans=0;
        PushDown(x);
        if(l<=mid) ans=max(ans,Query(x<<1,l,r));
        if(r>mid) ans=max(ans,Query(x<<1|1,l,r));
        return ans;
    }
}
namespace Min{
    struct Node{
        int l,r,dat,tag=-1;
    }tr[N<<3];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag

    inline void Push(int x,int k){dat(x)=tag(x)=k;}
    inline void PushDown(int x){if(~tag(x)) Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=-1;}
    inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
    inline void Build(int x,int l,int r){
        l(x)=l;r(x)=r;dat(x)=n+1;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    }
    inline void Modify(int x,int l,int r,int k){
        if(l<=l(x)&&r(x)<=r) return Push(x,k);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    inline int Query(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1,ans=n+1;
        PushDown(x);
        if(l<=mid) ans=min(ans,Query(x<<1,l,r));
        if(r>mid) ans=min(ans,Query(x<<1|1,l,r));
        return ans;
    }
}
int lp[N],rp[N];
int ql[N],qr[N],ans[N],q;

int t[N<<1];
inline void Add(int x,int k){
    while(x<=2*n){
        t[x]+=k;
        x+=x&-x;
    }
}
inline int Ask(int x){
    int sum=0;
    while(x){
        sum+=t[x];
        x&=x-1;
    }
    return sum;
}
inline void Work(vector<array<int,3>> v,int k){
    sort(v.begin(),v.end(),[](auto x,auto y){
        return x[0]^y[0]?x[0]>y[0]:x[2]<y[2];
    });
    for(auto t:v){
        if(t[2]<0) Add(t[1],1);
        else ans[t[2]]+=Ask(t[1])*k;
    }
    for(auto t:v) if(t[2]<0) Add(t[1],-1);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    cin>>q;
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

    for(int i=1;i<=n;i++) lp[i]=n+1,rp[i]=0;
    Max::Build(1,1,n<<1);
    for(int i=1;i<=n;i++){
        lp[i]=Max::Query(1,b[i],a[i]);
        Max::Modify(1,b[i],a[i],i);
    }
    Min::Build(1,1,n<<1);
    for(int i=n;i>=1;i--){
        rp[i]=Min::Query(1,b[i],a[i]);
        Min::Modify(1,b[i],a[i],i);
    }
   
    // for(int i=1;i<=n;i++) cout<<lp[i]<<"<->"<<rp[i]<<endl;

    vector<array<int,3>> tmp;
    for(int i=1;i<=q;i++) tmp.push_back({ql[i],qr[i],i});
    for(int i=1;i<=n;i++) tmp.push_back({i,rp[i],-i});
    Work(tmp,1);
    tmp.clear();
    for(int i=1;i<=q;i++) tmp.push_back({ql[i],qr[i],i});
    for(int i=1;i<=n;i++) tmp.push_back({lp[i],i,-i});
    Work(tmp,1);
    tmp.clear();
    for(int i=1;i<=q;i++) tmp.push_back({ql[i],qr[i],i});
    for(int i=1;i<=n;i++) tmp.push_back({lp[i],rp[i],-i});
    Work(tmp,-1);
    tmp.clear();

    for(int i=1;i<=q;i++) cout<<(ans[i]==qr[i]-ql[i]+1?"Yes":"No")<<endl;
    // for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}