#include<bits/stdc++.h>

using namespace std;

ifstream fin("graph.in");
ofstream fout("graph.out");
#define cin fin
#define cout fout

#define ssiz(x) (signed)x.size()
const int N=5e5+9;
const int inf=2e9;

int a[N],mp[N],n,m;
vector<pair<int,int>> e[N];

struct Node{
    int l,r,dat,tag=1,pos,ban;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag
#define pos(x) tr[x].pos
#define ban(x) tr[x].ban

void Push(int x,int k){
    if(ban(x)) return ;
    dat(x)=min(dat(x),k);
    tag(x)=min(tag(x),k);
}
void PushDown(int x){
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=inf;
}
void PushUp(int x){
    if(ban(x<<1)&&ban(x<<1|1)) ban(x)=1,dat(x)=tag(x)=inf,pos(x)=-1;
    else if(dat(x<<1)<dat(x<<1|1)) dat(x)=dat(x<<1),pos(x)=pos(x<<1);
    else dat(x)=dat(x<<1|1),pos(x)=pos(x<<1|1);
}

void Build(int x,int l,int r){
    l(x)=l,r(x)=r,pos(x)=l(x),tag(x)=dat(x)=inf;
    if(l(x)==r(x)) return ;
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(r<l) return ;
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
void Ban(int x,int pos){
    if(l(x)==r(x)){
        ban(x)=1,dat(x)=tag(x)=inf,pos(x)=-1;
        return ;
    }
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(pos<=mid) Ban(x<<1,pos);
    else Ban(x<<1|1,pos);
    PushUp(x);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++) sort(e[i].begin(),e[i].end());

    long long stp=n,ans=0;
    Build(1,1,n);
    Modify(1,1,1,0);
    
    vector<int> cur(n);
    iota(cur.begin(),cur.end(),1);
    while(stp--){
        int pos=pos(1);
        ans+=dat(1);
        assert(pos!=-1);
        Ban(1,pos);
        
        for(auto p:e[pos]) mp[p.first]=1;
        vector<int> tmp;
        for(int x:cur){
            if(mp[x]) tmp.push_back(x);
            else Modify(1,x,x,a[x]);
        }
        for(auto p:e[pos]) mp[p.first]=0;
        cur=tmp;

        int l=1,r;
        for(int i=0;i<ssiz(e[pos]);i++){
            Modify(1,e[pos][i].first,e[pos][i].first,e[pos][i].second);
            r=e[pos][i].first-1;
            if(l<=r) Modify(1,l,r,a[pos]);
            l=r+2;
        }
        r=n;
        if(l<=r) Modify(1,l,r,a[pos]);
    }

    cout<<ans<<endl;

    return 0;
}