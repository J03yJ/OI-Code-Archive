#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],d[N],n;

struct Node{
    int l,r;
    int dat,tag;
}tr[N<<3];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void PushUp(int x){
    dat(x)=max(dat(x<<1),dat(x<<1|1));
}
void Push(int x,int k){
    dat(x)+=k;
    tag(x)+=k;
}
void PushDown(int x){
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=0;
}

void Build(int x,int l,int r){
    l(x)=l,r(x)=r,tag(x)=0;
    if(l(x)==r(x)){
        dat(x)=-l(x);
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
multiset<int> s;
void Ins(int x){
    s.insert(x);
    if(x>0) Modify(1,x,n,1);
}
void Del(int x){
    s.erase(s.lower_bound(x));
    if(x>0) Modify(1,x,n,-1);
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        
        d[n+1]=a[n]+1;d[0]=a[1]+1;
        for(int i=n;i;i--) d[i]=min(d[i+1]-1,a[i]);

        int ans=0;
        Build(1,1,n);
        for(int i=1;i<=n;i++) Ins(d[i]);
        for(int i=1;i<=n;i++){
            Del(d[i]);
            d[i]=min(d[i-1]-1,d[i]);
            Ins(d[i]);
            int flag=0;
            if(*s.begin()<=0) flag=1;
            if(dat(1)>0) flag=1;
            if(!flag) ans++;    
            Del(d[i]);
            d[i]=min(d[i-1]-1,a[i]);
            Ins(d[i]);
        }
        cout<<ans<<endl;
        s.clear();
    }

    return 0;
}