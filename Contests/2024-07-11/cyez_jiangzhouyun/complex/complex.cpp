#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("complex.in");
ofstream fout("complex.out");
#define cin fin
#define cout fout

const int N=2e5+9;
const int p=998244353;

pair<int,int> a[N];
int val[N],cnt,n;
inline int pos(int k){
    return lower_bound(val+1,val+cnt+1,k)-val;
}

int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}

namespace SGT{
    struct node{
        int l,r,dat,tag;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag
    inline void pushup(int x){
        dat(x)=(dat(x<<1)+dat(x<<1|1))%p;
    }
    inline void pushdown(int x){
        tag(x<<1)=tag(x<<1)*tag(x)%p;
        tag(x<<1|1)=tag(x<<1|1)*tag(x)%p;
        dat(x<<1)=dat(x<<1)*tag(x)%p;
        dat(x<<1|1)=dat(x<<1|1)*tag(x)%p;
        tag(x)=1;
    }
    void build(int x,int l,int r){
        l(x)=l;r(x)=r;tag(x)=1;dat(x)=0;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        build(x<<1,l(x),mid);
        build(x<<1|1,mid+1,r(x));
    }
    void add(int x,int pos,int k){
        if(l(x)==r(x)){
            dat(x)=(dat(x)+k)%p;
            return ;
        }
        pushdown(x);
        int mid=l(x)+r(x)>>1;
        if(pos<=mid) add(x<<1,pos,k);
        else add(x<<1|1,pos,k);
        pushup(x);
    }
    void mul(int x,int l,int r,int k){
        if(l>r) return ;
        if(l<=l(x)&&r(x)<=r){
            tag(x)=tag(x)*k%p;
            dat(x)=dat(x)*k%p;
            return ;
        }
        pushdown(x);
        int mid=l(x)+r(x)>>1;
        if(l<=mid) mul(x<<1,l,r,k);
        if(r>mid) mul(x<<1|1,l,r,k);
        pushup(x);
    }
    int query(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        pushdown(x);
        int mid=l(x)+r(x)>>1,ans=0;
        if(l<=mid) ans=(ans+query(x<<1,l,r))%p;
        if(r>mid) ans=(ans+query(x<<1|1,l,r))%p;
        return ans;
    }
}
namespace BIT{
    int tr[N];
    void add(int x,int k){
        while(x<=cnt){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    int ask(int x){
        int sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
    int ask(int l,int r){
        if(l>r) return 0;
        else return ask(r)-ask(l-1);
    }
    void clear(){
        for(int i=1;i<=cnt;i++) tr[i]=0;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;

    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) val[i]=a[i].second;
    sort(val+1,val+n+1);
    cnt=unique(val+1,val+n+1)-val-1;

    int ans=0;

    SGT::build(1,1,cnt);
    BIT::clear();
    for(int i=1,lst=0;i<=n;i++){
        int cur=pos(a[i].second);
        SGT::add(1,cur,a[i].second*qpow(2,BIT::ask(cur))%p);
        SGT::mul(1,cur+1,cnt,2);
        BIT::add(cur,1);
        int res=SGT::query(1,1,cnt);
        ans=(ans+a[i].first*((res-lst+p)%p)%p)%p;
        lst=res;
    }
    SGT::build(1,1,cnt);
    BIT::clear();
    for(int i=n,lst=0;i>=1;i--){
        int cur=pos(a[i].second);
        SGT::add(1,cur,a[i].second*qpow(2,BIT::ask(cur))%p);
        SGT::mul(1,cur+1,cnt,2);
        BIT::add(cur,1);
        int res=SGT::query(1,1,cnt);
        ans=(ans-a[i].first*((res-lst+p)%p)%p+p)%p;
        lst=res;
    }
    SGT::build(1,1,cnt);
    BIT::clear();
    for(int i=1,lst=0;i<=n;i++){
        int cur=pos(a[i].second);
        SGT::add(1,cur,a[i].second*qpow(2,BIT::ask(cur,cnt))%p);
        SGT::mul(1,1,cur-1,2);
        BIT::add(cur,1);
        int res=SGT::query(1,1,cnt);
        ans=(ans-a[i].first*((res-lst+p)%p)%p+p)%p;
        lst=res;
    }
    SGT::build(1,1,cnt);
    BIT::clear();
    for(int i=n,lst=0;i>=1;i--){
        int cur=pos(a[i].second);
        SGT::add(1,cur,a[i].second*qpow(2,BIT::ask(cur,cnt))%p);
        SGT::mul(1,1,cur-1,2);
        BIT::add(cur,1);
        int res=SGT::query(1,1,cnt);
        ans=(ans+a[i].first*((res-lst+p)%p)%p)%p;
        lst=res;
    }

    cout<<ans<<endl;

    return 0;
}