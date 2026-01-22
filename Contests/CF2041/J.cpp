#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],b[N],c[N],leg[N],n;

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}
void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        dat(x)=-(n-l+1);
        return ;
    }
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l>r) return ;
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    PushDown(x);
    int mid=(l(x)+r(x))>>1;
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int pos){
    if(l(x)==r(x)) return dat(x);
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(pos<=mid) return Query(x<<1,pos);
    else return Query(x<<1|1,pos);
}

vector<pair<int,int>> opl[N],opr[N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i],b[i]--;
    sort(b+1,b+n+1);

    for(int i=1;i<=n;i++) c[i]=upper_bound(b+1,b+n+1,a[i])-b-1;

    Build(1,1,n);
    vector<array<int,3>> stk; 
    for(int i=1;i<=n;i++){
        int l=i,r=i;
        while(stk.size()&&stk.back()[2]>=c[i]){
            l=stk.back()[0];
            opl[i].push_back({stk.back()[2],-(stk.back()[1]-stk.back()[0]+1)});
            stk.pop_back();
        }
        cout<<c[i]<<" : "<<l<<' '<<r<<endl;
        opl[i].push_back({c[i],r-l+1});
        stk.push_back({l,r,c[i]});
    }
    stk.clear();
    cout<<endl;
    for(int i=n;i>=1;i--){
        int l=i,r=i;
        while(stk.size()&&stk.back()[2]>=c[i]){
            r=stk.back()[1];
            opr[i].push_back({stk.back()[2],-(stk.back()[1]-stk.back()[0]+1)});
            Modify(1,1,stk.back()[2],-(stk.back()[1]-stk.back()[0]+1));
            stk.pop_back();
        }
        cout<<c[i]<<" : "<<l<<' '<<r<<endl;
        opr[i].push_back({c[i],r-l+1});
        Modify(1,1,c[i],r-l+1);
        stk.push_back({l,r,c[i]});
    }

    for(int i=1;i<=n;i++){
        for(auto p:opl[i]) Modify(1,1,p.first,p.second);
        Modify(1,c[i],n,-1);
        if(dat(1)>0) leg[i]=0;
        else leg[i]=1;
        // cout<<dat(1)<<' ';
        Modify(1,c[i],n,1);
        for(auto p:opr[i]) Modify(1,1,p.first,-p.second);
        for(int j=1;j<=n;j++) cout<<Query(1,j)<<' ';cout<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++) cout<<leg[i]<<' ';cout<<endl;

    return 0;
}