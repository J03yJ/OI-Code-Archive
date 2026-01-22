#include<bits/stdc++.h>

using namespace std;

using ll=long long;
using bint=__int128;
const int N=2e5+9;
const ll mod=1ll<<32;
const ll inf=1e18+9ll;

struct Node{
    int l,r;
    ll sum,lcm;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define sum(x) tr[x].sum
#define lcm(x) tr[x].lcm

ll a[N];
inline ll LCM(ll x,ll y){
    if(x==inf||y==inf) return inf;
    bint lcm=bint(x)*y/__gcd(x,y);
    return lcm>inf?inf:lcm;
}
inline void PushUp(int x){
    sum(x)=(sum(x<<1)+sum(x<<1|1))&(mod-1);
    lcm(x)=LCM(lcm(x<<1),lcm(x<<1|1));
}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        sum(x)=lcm(x)=a[l(x)];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Modify(int x,int l,int r,ll k){
    if(lcm(x)!=inf&&k%lcm(x)==0) return ;
    if(l(x)==r(x)){
        sum(x)=lcm(x)=__gcd(sum(x),k);
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
inline ll Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return sum(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int n,m;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    Build(1,1,n);
    while(m--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1){
            ll x;
            cin>>x;
            Modify(1,l,r,x);
        }else{
            cout<<(Query(1,l,r)&(mod-1))<<endl;
        }
    }

    return 0;
}