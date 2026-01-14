#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

struct Node{
    int l,r,dat,tag;
}tr[N<<4];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}
inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=tag(x)=0;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
inline void Modify(int x,int l,int r,int k){
    if(l>r) return ;
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
inline void Insert(int x,int pos,int k){
    if(l(x)==r(x)){
        dat(x)=max(dat(x),k);
        return ;
    }
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(pos<=mid) Insert(x<<1,pos,k);
    else Insert(x<<1|1,pos,k);
    PushUp(x);
}
inline int Query(int x,int l,int r){
    if(l>r) return 0;
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int a[N],cnt[N],n,tot;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        vector<int> val(a+1,a+n+1);
        val.push_back(-1);
        val.push_back(0);
        val.push_back(1e9+7);
        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());
        tot=val.size()-1;

        for(int i=1;i<=n;i++){
            a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
            cnt[a[i]]++;
        }
        Build(1,1,tot);
        for(int i=1;i<=tot;i++) Modify(1,i,i,-cnt[i]);
        for(int i=1;i<=n;i++){
            cnt[a[i]]--;
            Modify(1,1,a[i],1);
            Insert(1,a[i],Query(1,a[i]+1,tot)+1-cnt[a[i]]);
        }
        cout<<dat(1)<<endl;
        for(int i=1;i<=tot;i++) cnt[i]=0;
    }

    return 0;
}