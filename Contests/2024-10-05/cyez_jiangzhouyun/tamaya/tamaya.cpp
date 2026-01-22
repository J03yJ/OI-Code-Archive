#include<bits/stdc++.h>

using namespace std;

ifstream fin("tamaya.in");
ofstream fout("tamaya.out");
#define cin fin
#define cout fout

const int N=5e5+9;
const int inf=1e9;
const int lgN=2e1;

struct Node{
    int l,r,dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=0;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
}
void Push(int x,int l,int r,int t){
    if(l<=l(x)&&r(x)<=r){
        dat(x)=t;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(l<=mid) Push(x<<1,l,r,t);
    if(r>mid) Push(x<<1|1,l,r,t);
}
int Query(int x,int pos){
    if(l(x)==r(x)) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) return max(dat(x),Query(x<<1,pos));
    else return max(dat(x),Query(x<<1|1,pos));
}

int a[N],ml[N],mr[N],n,m;
int ql[N],qr[N],qx[N],op[N],q;
int lfa[N][lgN],rfa[N][lgN],lpos[N],rpos[N],lx[N],rx[N];
vector<pair<int,int>> qst[N];

namespace Mx{
    struct Node{
        int l,r,dat;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat

    void Build(int x,int l,int r){
        l(x)=l,r(x)=r,dat(x)=0;
        if(l(x)==r(x)){
            dat(x)=a[l(x)];
            return ;
        }
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid);
        Build(x<<1|1,mid+1,r);
        dat(x)=max(dat(x<<1),dat(x<<1|1));
    }
    void Modify(int x,int pos,int k){
        if(l(x)==r(x)){
            dat(x)=k;
            return ;
        }
        int mid=l(x)+r(x)>>1;
        if(pos<=mid) Modify(x<<1,pos,k);
        else Modify(x<<1|1,pos,k);
        dat(x)=max(dat(x<<1),dat(x<<1|1));
    }
    int Query(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1,ans=0;
        if(l<=mid) ans=max(ans,Query(x<<1,l,r));
        if(r>mid) ans=max(ans,Query(x<<1|1,l,r));
        return ans;
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>ml[i]>>mr[i];
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>op[i];
        if(op[i]==1) cin>>ql[i]>>qx[i];
        else cin>>ql[i]>>qr[i]>>qx[i],qst[qr[i]].push_back({i,qx[i]});
    }

    Build(1,1,n);
    for(int i=1;i<=m;i++){
        lfa[i][0]=Query(1,ml[i]);
        Push(1,ml[i],mr[i],i);
        for(auto p:qst[i]) lx[p.first]=Query(1,p.second);
    }
    Build(1,1,n);
    for(int i=1;i<=m;i++){
        rfa[i][0]=Query(1,mr[i]);
        Push(1,ml[i],mr[i],i);
        for(auto p:qst[i]) rx[p.first]=Query(1,p.second);
    }

    for(int k=1;k<lgN;k++){
        for(int i=1;i<=m;i++) lfa[i][k]=lfa[lfa[i][k-1]][k-1];
        for(int i=1;i<=m;i++) rfa[i][k]=rfa[rfa[i][k-1]][k-1];
    }

    for(int i=1;i<=q;i++){
        if(op[i]==1) continue ;
        if(lx[i]<ql[i]) lpos[i]=qx[i];
        else{
            int pos=lx[i];
            for(int k=lgN-1;~k;k--) if(lfa[pos][k]>=ql[i]) pos=lfa[pos][k];
            lpos[i]=ml[pos];
        }
        if(rx[i]<ql[i]) rpos[i]=qx[i];
        else{
            int pos=rx[i];
            for(int k=lgN-1;~k;k--) if(rfa[pos][k]>=ql[i]) pos=rfa[pos][k];
            rpos[i]=mr[pos];
        }
        // cout<<lpos[i]<<' '<<rpos[i]<<endl;
    }

    Mx::Build(1,1,n);
    for(int i=1;i<=q;i++){
        if(op[i]==1) Mx::Modify(1,ql[i],qx[i]);
        else cout<<Mx::Query(1,lpos[i],rpos[i])<<endl;
    }

    return 0;
}