#include<bits/stdc++.h>

using namespace std;

ifstream fin("superglue.in");
ofstream fout("superglue.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],dep[N],siz[N],hson[N];
void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int top[N],dfn[N],idfn[N],dcnt;
void DFS2(int x,int t){
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
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

int a[N],n,q;

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

vector<array<int,3>> stk;
void Record(int x){stk.push_back({x,dat(x),tag(x)});}
void Start(){stk.push_back({-1,-1,-1});}
void RollBack(){
    while(stk.size()){
        auto t=stk.back();
        stk.pop_back();
        if(t[0]==-1) break ;
        dat(t[0])=t[1];
        tag(t[0])=t[2];
    }
}
void Push(int x){
    Record(x);
    tag(x)=1,dat(x)=0;
}
void PushDown(int x){
    if(!tag(x)) return ;
    Record(x);
    Push(x<<1),Push(x<<1|1),tag(x)=0;
}
void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}

void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        dat(x)=a[idfn[l(x)]];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int pos,int k){
    if(l(x)==r(x)){
        Record(x),dat(x)=k;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    Record(x),PushUp(x);
}
void Assign(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r){
        return Push(x);
    }
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Assign(x<<1,l,r);
    if(r>mid) Assign(x<<1|1,l,r);
    Record(x),PushUp(x);
}
int _Find_(int x){
    if(l(x)==r(x)) return l(x);
    PushDown(x);
    if(dat(x<<1|1)) return _Find_(x<<1|1);
    else return _Find_(x<<1);
}
int Find(int x,int l,int r){
    if(!dat(x)) return -1;
    if(l<=l(x)&&r(x)<=r) return _Find_(x);
    int mid=l(x)+r(x)>>1,ans=-1;
    PushDown(x);
    if(r>mid) ans=Find(x<<1|1,l,r);
    if(ans!=-1) return ans;
    if(l<=mid) ans=Find(x<<1,l,r);
    return ans;
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1,ans=0;
    PushDown(x);
    if(l<=mid) ans+=Query(x<<1,l,r);
    if(r>mid) ans+=Query(x<<1|1,l,r);
    return ans;
}

int FindRoot(int x){
    while(x){
        int tmp=Find(1,dfn[top[x]],dfn[x]);
        if(tmp==-1){
            x=fa[top[x]];
            continue ;
        }
        return idfn[tmp];
    }
    assert(0);
    return -1;
}
int CalcSum(int x,int y){
    int sum=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        sum+=Query(1,dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    sum+=Query(1,dfn[y],dfn[x]);
    return sum;
}
void Clear(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        Assign(1,dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    Assign(1,dfn[y],dfn[x]);
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    DFS1(1);
    DFS2(1,1);
    Build(1,1,n);

    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int u,v;
            cin>>u>>v;
            Start();
            int lca=LCA(u,v),p=FindRoot(lca),w=CalcSum(u,v);
            if(p!=lca) w+=Query(1,dfn[p],dfn[p]);
            Clear(u,v);
            Modify(1,dfn[p],w);
        }else if(op==2){
            RollBack();
        }else if(op==3){
            int x;
            cin>>x;
            int rt=FindRoot(x);
            cout<<Query(1,dfn[rt],dfn[rt])<<endl;
        }
    }

    return 0;
}