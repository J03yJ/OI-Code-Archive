#include<bits/stdc++.h>

using namespace std;

ifstream fin("array.in");
ofstream fout("array.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e5+9;
const int inf=1e9+7;

struct Node{
    int l,r;
    int mn,mx;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define mn(x) tr[x].mn
#define mx(x) tr[x].mx

inline void PushUp(int x){
    mn(x)=min(mn(x<<1),mn(x<<1|1));
    mx(x)=max(mx(x<<1),mx(x<<1|1));
}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,mn(x)=inf,mx(x)=-inf;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Set(int x,int pos,int k){
    if(l(x)==r(x)) return mx(x)=mn(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Set(x<<1,pos,k);
    else Set(x<<1|1,pos,k);
    PushUp(x);
}
inline int Max(int x,int l,int r){
    if(l>r) return -inf;
    if(l<=l(x)&&r(x)<=r) return mx(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return max(Max(x<<1,l,mid),Max(x<<1|1,mid+1,r));
    else if(l<=mid) return Max(x<<1,l,r);
    else return Max(x<<1|1,l,r);
}
inline int Min(int x,int l,int r){
    if(l>r) return inf;
    if(l<=l(x)&&r(x)<=r) return mn(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return min(Min(x<<1,l,mid),Min(x<<1|1,mid+1,r));
    else if(l<=mid) return Min(x<<1,l,r);
    else return Min(x<<1|1,l,r);
}

int a[N],n,m,Tid;
int lp[N],rp[N],val[N],tot;
vector<int> p[N];
inline bool Check(int k){
    Build(1,1,tot);
    for(int i=1;i<=n;i++){
        int l=lower_bound(val+1,val+tot+1,val[a[i]]-k)-val;
        int r=upper_bound(val+1,val+tot+1,val[a[i]]+k)-val-1;
        lp[i]=Max(1,l,r);
        Set(1,a[i],i);
    }
    Build(1,1,tot);
    for(int i=n;i>=1;i--){
        int l=lower_bound(val+1,val+tot+1,val[a[i]]-k)-val;
        int r=upper_bound(val+1,val+tot+1,val[a[i]]+k)-val-1;
        rp[i]=Min(1,l,r);
        Set(1,a[i],i);
    }
    bool flag=0;
    Build(1,1,n);
    for(int i=1;i<=n;i++) p[max(lp[i],0)].push_back(i);
    for(int i:p[0]) Set(1,i,rp[i]);
    for(int l=1;l<=n-m+1;l++){
        int r=l+m-1;
        while(r!=inf){
            int pos=Max(1,l,r);
            if(pos<=r){
                flag=1;
                for(int i=0;i<=n;i++) p[i].clear();
                return flag;
            }
            r=pos;
        }
        for(int i:p[l]) Set(1,i,rp[i]);
    }
    for(int i=0;i<=n;i++) p[i].clear();
    return flag;
}

signed main(){
    cin>>Tid>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    copy(a+1,a+n+1,val+1);
    sort(val+1,val+n+1);
    tot=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+tot+1,a[i])-val;
    
    int l=-1,r=inf;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) r=mid;
        else l=mid;
    }
    cout<<r<<endl;

    return 0;
}