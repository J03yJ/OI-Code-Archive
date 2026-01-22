#include<bits/stdc++.h>

using namespace std;

ifstream fin("title.in");
ofstream fout("title.out");
#define cin fin
#define cout fout

#define int long long
#define ssiz(x) (signed)x.size()
#define endl '\n'
const int N=5e5+9;

struct Node{
    int l,r,mx,ans,tag;
}tr[N<<2];

#define l(x) tr[x].l
#define r(x) tr[x].r
#define mx(x) tr[x].mx
#define ans(x) tr[x].ans
#define tag(x) tr[x].tag

void Push(int x,int k){
    tag(x)=max(tag(x),k);
    ans(x)=max(ans(x),mx(x)+k);
}
void PushDown(int x){
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=0;
}
void PushUp(int x){
    ans(x)=max(ans(x<<1),ans(x<<1|1));
    mx(x)=max(mx(x<<1),mx(x<<1|1));
    // cout<<l(x)<<' '<<r(x)<<" : "<<ans(x)<<' '<<mx(x)<<endl;
}

int a[N],ans[N],n,m;
vector<int> pos[N];
vector<pair<int,int>> q[N];
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        mx(x)=ans(x)=a[l(x)];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l(x),mid);
    Build(x<<1|1,mid+1,r(x));
    PushUp(x);
}
void ChMax(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) ChMax(x<<1,l,r,k);
    if(r>mid) ChMax(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return ans(x);
    int mid=l(x)+r(x)>>1,ans=0;
    PushDown(x);
    if(l<=mid) ans=max(ans,Query(x<<1,l,r));
    if(r>mid) ans=max(ans,Query(x<<1|1,l,r));
    return ans;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<int> stk;
    for(int i=1;i<=n;i++){
        while(ssiz(stk)&&a[stk.back()]<a[i]) stk.pop_back();
        if(ssiz(stk)&&i*2-stk.back()<=n) pos[stk.back()].push_back(i);
        stk.push_back(i);
    }
    stk.clear();
    for(int i=n;i>=1;i--){
        while(ssiz(stk)&&a[stk.back()]<a[i]) stk.pop_back();
        if(ssiz(stk)&&stk.back()*2-i<=n) pos[i].push_back(stk.back());
        stk.push_back(i);
    }

    Build(1,1,n);
    for(int i=1,l,r;i<=m;i++){
        cin>>l>>r;
        if(r-l>1) q[l].push_back({i,r});
    }
    for(int i=n;i>=1;i--){
        for(int j:pos[i]) ChMax(1,j+j-i,n,a[i]+a[j]);
        for(auto p:q[i]) ans[p.first]=Query(1,i,p.second);
    }
    for(int i=1;i<=m;i++){
        if(ans[i]) cout<<ans[i]<<endl;
        else cout<<"No solution"<<endl;
    }

    return 0;
}