#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int a[N];
int ans[N],pos[N],l[N],r[N];

struct node{
    int l,r,pos;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define pos(x) tr[x].pos

int Upd(int x,int y){
    if(a[x]>a[y]) return x;
    else return y;
}
void build(int x,int l,int r){
    l(x)=l;r(x)=r;
    if(l==r) {
        pos(x)=l;
        return ;
    }
    int mid=l+r>>1;
    build(1<<x,l,mid);build(1<<x|1,mid+1,r);
    pos(x)=Upd(pos(x<<1),pos(x<<1|1));
}
int query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return pos(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Upd(query(1<<x,l,r),query(1<<x|1,l,r));
    else if(l<=mid) return query(1<<x,l,r);
    else return query(1<<x|1,l,r);
}

struct Q{int l,r,id;};
vector<Q> q1,q2;
bool Lcmp(Q x,Q y){
    return x.l<y.l;
}
bool Rcmp(Q x,Q y){
    return x.r>y.r;
}

int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=q;i++){
        cin>>l[i]>>r[i];
        pos[i]=query(1,l[i],r[i]);
        ans[i]=a[pos[i]];
        q1.push_back({l[i],});
    }
    return 0;
}