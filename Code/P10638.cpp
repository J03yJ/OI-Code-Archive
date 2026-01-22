#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=3e5+9;
const int inf=1e18;

inline void chmax(int &x,int y){
    if(y>x) x=y;
}
inline void chmin(int &x,int y){
    if(y<x) x=y;
}

int a[N];

struct node{
    int l,r;
    int mn,se,cnt;
    int tag1,tag2;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define mn(x) tr[x].mn
#define se(x) tr[x].se
#define cnt(x) tr[x].cnt
#define tag1(x) tr[x].tag1
#define tag2(x) tr[x].tag2
#define len(x) (r(x)-l(x)+1)

inline void pushup(int x){
    mn(x)=min(mn(x<<1),mn(x<<1|1));
    if(mn(x<<1)==mn(x<<1|1)){
        cnt(x)=cnt(x<<1)+cnt(x<<1|1);
        se(x)=min(se(x<<1),se(x<<1|1));
    }else if(mn(x<<1)<mn(x<<1|1)){
        cnt(x)=cnt(x<<1);
        se(x)=min(se(x<<1),mn(x<<1|1));
    }else{
        cnt(x)=cnt(x<<1|1);
        se(x)=min(mn(x<<1),se(x<<1|1));
    }
}
void build(int x,int l,int r){
    l(x)=l;r(x)=r;tag1(x)=-1;
    if(l==r){
        mn(x)=a[l];
        se(x)=inf;
        cnt(x)=1;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
inline void upd1(int x,int k){
    mn(x)=k;se(x)=inf;cnt(x)=len(x);tag1(x)=k;tag2(x)=0;
}
inline void upd2(int x,int k){
    mn(x)+=k;se(x)+=k;tag2(x)+=k;
}
void pushdown(int x){
    if(~tag1(x)){
        upd1(x<<1,tag1(x));
        upd1(x<<1|1,tag1(x));
        tag1(x)=-1;
    }
    if(tag2(x)){
        upd2(x<<1,tag2(x));
        upd2(x<<1|1,tag2(x));
        tag2(x)=0;
    }
   chmax(mn(x<<1),mn(x));
    chmax(mn(x<<1|1),mn(x));
}
void Assign(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return upd1(x,k);
    int mid=l(x)+r(x)>>1;
    pushdown(x);
    if(l<=mid) Assign(x<<1,l,r,k);
    if(r>mid) Assign(x<<1|1,l,r,k);
    pushup(x);
}
void Add(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return upd2(x,k);
    int mid=l(x)+r(x)>>1;
    pushdown(x);
    if(l<=mid) Add(x<<1,l,r,k);
    if(r>mid) Add(x<<1|1,l,r,k);
    pushup(x);
}
void Chmax(int x,int l,int r,int k){
    if(k<=mn(x)) return ;
    if(l<=l(x)&&r(x)<=r&&k<se(x)){
        mn(x)=k;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    pushdown(x);
    if(l<=mid) Chmax(x<<1,l,r,k);
    if(r>mid) Chmax(x<<1|1,l,r,k);
    pushup(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return (mn(x)==0)*cnt(x);
    int mid=l(x)+r(x)>>1,ans=0;
    pushdown(x);
    if(l<=mid) ans+=Query(x<<1,l,r);
    if(r>mid) ans+=Query(x<<1|1,l,r);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #define endl '\n'
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(m--){
        int op,l,r,k;
        cin>>op>>l>>r;
        if(op==1){
            cin>>k;
            Assign(1,l,r,k);
        }else if(op==2){
            cin>>k;
            Add(1,l,r,k);
            Chmax(1,l,r,0);
        }else cout<<Query(1,l,r)<<endl;
    }
    return 0;
}