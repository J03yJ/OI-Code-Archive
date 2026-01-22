#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int inf=4e18;

int a[N],n;
struct Node{
    int l,r;
    int tag=-inf,dat,mx;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define tag(x) tr[x].tag
#define dat(x) tr[x].dat
#define mx(x) tr[x].mx
#define len(x) (r(x)-l(x)+1)

void PushUp(int x){
    dat(x)=dat(x<<1)+dat(x<<1|1);
    mx(x)=max(mx(x<<1),mx(x<<1|1));
}
void Push(int x,int k){
    dat(x)=k*len(x);
    tag(x)=k;
    mx(x)=k;
}
void PushDown(int x){
    if(tag(x)==-inf) return ;
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=-inf;
}
void Build(int x,int l,int r){
    tag(x)=-inf;l(x)=l;r(x)=r;
    if(l(x)==r(x)){
        mx(x)=dat(x)=a[l(x)];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l(x),mid);
    Build(x<<1|1,mid+1,r(x));
    PushUp(x);
}
void Assign(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Assign(x<<1,l,r,k);
    if(r>mid) Assign(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1,ans=0;
    PushDown(x);
    if(l<=mid) ans+=Query(x<<1,l,r);
    if(r>mid) ans+=Query(x<<1|1,l,r);
    return ans;
}
int LowerBound(int x,int k){
    if(l(x)==r(x)) return l(x);
    PushDown(x);
    if(k<=mx(x<<1)) return LowerBound(x<<1,k);
    else return LowerBound(x<<1|1,k);
}
int UpperBound(int x,int k){
    if(l(x)==r(x)) return l(x);
    PushDown(x);
    if(k<mx(x<<1)) return UpperBound(x<<1,k);
    else return UpperBound(x<<1|1,k);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]-=i;
    a[0]=-inf;a[n+1]=inf;
    Build(1,0,n+1);

    int q;
    cin>>q;
    int ans=0;
    while(q--){
        int x,k;
        cin>>x>>k;
        k-=x;
        int cur=Query(1,x,x);
        if(k==cur) continue ;
        else if(k<cur){
            int pos=UpperBound(1,k);
            ans-=k*(x-pos+1);
            ans+=Query(1,pos,x);
            Assign(1,pos,x,k);
        }else{
            int pos=LowerBound(1,k)-1;
            ans-=Query(1,x,pos);
            ans+=k*(pos-x+1);
            Assign(1,x,pos,k);
        }
        // for(int i=1;i<=n;i++) cout<<Query(1,i,i)+i<<' ';cout<<endl;
    }
    cout<<ans<<endl;

    return 0;
}