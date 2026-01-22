#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int inf=2e9;

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
    if(l(x)==r(x)) return ;
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
void Modify(int x,int l,int r,int k){
    if(l>r) return ;
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}

int n,m;
vector<array<int,3>> seg;

int main(){
    cin>>m>>n;
    for(int i=1,l,r,w;i<=m;i++){
        cin>>l>>r>>w;
        seg.push_back({w,l,r});
    }
    seg.push_back({inf,1,n});

    int ans=inf;
    Build(1,1,n-1);
    sort(seg.begin(),seg.end());
    for(int i=0,j=0;i<seg.size()-1;i++){
        if(i) Modify(1,seg[i-1][1],seg[i-1][2]-1,-1);
        while(!dat(1)) Modify(1,seg[j][1],seg[j][2]-1,1),j++;
        // cout<<i<<' '<<j<<' '<<seg[j-1][0]<<' '<<seg[i][0]<<endl;
        ans=min(ans,seg[j-1][0]-seg[i][0]);
    }
    cout<<ans<<endl;

    return 0;
}