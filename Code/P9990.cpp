#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e6+9;

struct Node{
    int l,r,rev,add[2];
    ll sum,hsum;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define sum(x) tr[x].sum
#define hsum(x) tr[x].hsum
#define rev(x) tr[x].rev
#define add(x,k) tr[x].add[k]
#define len(x) (r(x)-l(x)+1)

inline void PushAdd(int x,int add0,int add1){
    add(x,rev(x))+=add0;
    add(x,rev(x)^1)+=add1;
    hsum(x)+=1ll*add0*sum(x);
    hsum(x)+=1ll*add1*(len(x)-sum(x));
}
inline void PushRev(int x){
    rev(x)^=1;
    sum(x)=len(x)-sum(x);
}
inline void PushDown(int x){
    if(add(x,0)||add(x,1)){
        PushAdd(x<<1,add(x,0),add(x,1));
        PushAdd(x<<1|1,add(x,0),add(x,1));
        add(x,0)=add(x,1)=0;
    }
    if(rev(x)){
        PushRev(x<<1);
        PushRev(x<<1|1);
        rev(x)=0;
    }
}
inline void PushUp(int x){
    sum(x)=sum(x<<1)+sum(x<<1|1);
    hsum(x)=hsum(x<<1)+hsum(x<<1|1);
}

inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,sum(x)=len(x);
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Reverse(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return PushRev(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Reverse(x<<1,l,r);
    if(r>mid) Reverse(x<<1|1,l,r);
    PushUp(x);
}
inline ll Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return hsum(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int pre[N],buc[N],a[N],n;
int ql[N],qr[N],q;
vector<int> ed[N];
ll ans[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>q;
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

    for(int i=1;i<=n;i++){
        pre[i]=buc[a[i]];
        buc[a[i]]=i;
    }
    for(int i=1;i<=q;i++) ed[qr[i]].push_back(i);

    Build(1,1,n);
    for(int i=1;i<=n;i++){
        Reverse(1,pre[i]+1,i);
        PushAdd(1,0,1);
        for(int j:ed[i]) ans[j]+=Query(1,ql[j],qr[j]);
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}