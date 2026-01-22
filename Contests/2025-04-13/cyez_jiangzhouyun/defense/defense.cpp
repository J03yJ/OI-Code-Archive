#include<bits/stdc++.h>

using namespace std;

ifstream fin("defense.in");
ofstream fout("defense.out");
#define cin fin
#define cout fout
#define endl '\n'

#define double long double
using ll=long long;
const int N=1e5+9;
const double eps=1e-10;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],siz[N],hson[N];
inline void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int dfn[N],top[N],dcnt;
inline void DFS2(int x,int t){
    dfn[x]=++dcnt;
    top[x]=t;
    if(hson[x]) DFS2(hson[x],t);
    else return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
}

struct Node{
    int l,r;
    ll sum,ssum,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define sum(x) tr[x].sum
#define ssum(x) tr[x].ssum
#define tag(x) tr[x].tag
#define len(x) (r(x)-l(x)+1)

inline void Push(int x,ll k){tag(x)+=k,ssum(x)+=2*sum(x)*k+len(x)*k*k,sum(x)+=len(x)*k;}
inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}
inline void PushUp(int x){sum(x)=sum(x<<1)+sum(x<<1|1),ssum(x)=ssum(x<<1)+ssum(x<<1|1);}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,ssum(x)=sum(x)=tag(x)=0;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
inline ll SSum(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return ssum(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return SSum(x<<1,l,mid)+SSum(x<<1|1,mid+1,r);
    else if(l<=mid) return SSum(x<<1,l,r);
    else return SSum(x<<1|1,l,r);
}
inline ll Sum(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return sum(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Sum(x<<1,l,mid)+Sum(x<<1|1,mid+1,r);
    else if(l<=mid) return Sum(x<<1,l,r);
    else return Sum(x<<1|1,l,r);
}
inline void ToRoot(int x,ll k){
    while(x){
        Modify(1,dfn[top[x]],dfn[x],k);
        x=fa[top[x]];
    }
}

int c[N],w[N],n,m;
int op[N],qu[N],qt[N],qk[N],q;
ll cl[N],cr[N],yl[N],yr[N],qa[N],qb[N],qc[N];
vector<int> nd[N],qry[N];

signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++) cin>>w[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    for(int i=1;i<=q;i++){
        cin>>op[i];
        if(op[i]==1) cin>>qu[i]>>qt[i];
        else cin>>qu[i]>>qt[i]>>qk[i];
    }

    DFS1(1),DFS2(1,1);
    Build(1,1,n);
    for(int i=1;i<=n;i++) nd[c[i]].push_back(i);
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            if(c[qu[i]]==qt[i]) continue ;
            qry[c[qu[i]]].push_back(i);
            qry[c[qu[i]]=qt[i]].push_back(i);
        }else qry[qt[i]].push_back(i);
    }
    
    for(int t=1;t<=m;t++){
        set<int> s;
        for(int i:nd[t]) s.insert(i),ToRoot(i,1);
        for(int i:qry[t]){
            if(op[i]==1){
                if(qt[i]==t) s.insert(qu[i]),ToRoot(qu[i],1);
                else s.erase(qu[i]),ToRoot(qu[i],-1);
            }else{
                ll a=siz[qu[i]];
                ll b=-2*Sum(1,dfn[qu[i]],dfn[qu[i]]+siz[qu[i]]-1)*w[t];
                ll c=SSum(1,dfn[qu[i]],dfn[qu[i]]+siz[qu[i]]-1)*w[t]*w[t]-qk[i];
                qa[i]=a,qb[i]=b,qc[i]=c;
                double dlt=(double)b*(double)b-4*(double)a*(double)c;
                if(dlt<0) cl[i]=cr[i]=yl[i]=yr[i]=-1;
                else{
                    double rdlt=sqrt((double)dlt)/(double)(2*a);
                    double nb=-(double)b/(double)(2*a);
                    cl[i]=ceil(nb-rdlt-eps);
                    cr[i]=floor(nb+rdlt+eps);
                    if(cl[i]>cr[i]) cl[i]=cr[i]=yl[i]=yr[i]=-1;
                    else{
                        c+=qk[i];
                        yl[i]=a*cl[i]*cl[i]+b*cl[i]+c;
                        yr[i]=a*cr[i]*cr[i]+b*cr[i]+c;
                    }
                }
            }
        }
        for(int i:s) ToRoot(i,-1);
    }

    for(int i=1;i<=q;i++){
        if(op[i]==2){
            cout<<cl[i]<<' '<<yl[i]<<endl;
            cout<<cr[i]<<' '<<yr[i]<<endl;
        }
    }

    return 0;
}