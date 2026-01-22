// LUOGU_RID: 166824271
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
#define int long long

vector<pair<int,int>> a[N];

struct node{
    int l,r,mx,mn,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define mx(x) tr[x].mx
#define mn(x) tr[x].mn
#define tag(x) tr[x].tag

void build(int x,int l,int r){
    l(x)=l;r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    build(x<<1,l(x),mid);
    build(x<<1|1,mid+1,r(x));
}
inline void push_up(int x){
    mx(x)=max(mx(x<<1),mx(x<<1|1));
    mn(x)=min(mn(x<<1),mn(x<<1|1));
}
inline void push_down(int x){
    if(!tag(x)) return ;
    mn(x<<1)+=tag(x);
    mn(x<<1|1)+=tag(x);
    mx(x<<1)+=tag(x);
    mx(x<<1|1)+=tag(x);
    tag(x<<1)+=tag(x);
    tag(x<<1|1)+=tag(x);
    tag(x)=0;
}
void modify_add(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r){
        tag(x)+=k;
        mx(x)+=k;
        mn(x)+=k;
        return ;
    }
    push_down(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid) modify_add(x<<1,l,r,k);
    if(r>mid) modify_add(x<<1|1,l,r,k);
    push_up(x);
}
int mysqrt(int dat){
    int k=sqrt(dat);
    while(k*k<dat) k++;
    while(k*k>dat) k--;
    return k;
}
void modify_sqrt(int x){
    if(l(x)==r(x)){
        mx(x)=mysqrt(mx(x));
        mn(x)=mysqrt(mn(x));
        return ;
    }
    if(mn(x)-mysqrt(mn(x))==mx(x)-mysqrt(mx(x))){
        int k=-mn(x)+mysqrt(mn(x));
        tag(x)+=k;
        mn(x)+=k;
        mx(x)+=k;
        return ;
    }
    push_down(x);
    modify_sqrt(x<<1);
    modify_sqrt(x<<1|1);
    push_up(x);
}
void get_ans(int x,int *ans){
    if(l(x)==r(x)){
        ans[l(x)]=mx(x);
        return ;
    }
    push_down(x);
    int mid=l(x)+r(x)>>1;
    get_ans(x<<1,ans);
    get_ans(x<<1|1,ans);
}

int ans[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int n,q;
    cin>>n>>q;
    for(int i=1,x;i<=n;i++) cin>>x,a[i].push_back({0,x});
    for(int i=1,k,x;i<=q;i++) cin>>k>>x,a[k].push_back({i,x});

    build(1,0,q);
    for(int i=1;i<=n;i++) a[i].push_back({q+1,0});
    for(int i=1;i<=n;i++){
        for(int j=0;j<a[i].size()-1;j++){
            modify_add(1,a[i][j].first,a[i][j+1].first-1,a[i][j].second);
        }
        modify_sqrt(1);
    }

    get_ans(1,ans);
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}