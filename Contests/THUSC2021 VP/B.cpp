#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int inf=1e9+7;
using pii=pair<int,int>;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int ans;
struct Node{
    int lc,rc,f,g;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define f(x) tr[x].f
#define g(x) tr[x].g
int trs[N<<4],top,cnt;
int Allc(){return ++cnt;}
void Assign(int &x,int L,int R,int pos,int f,int g){
    if(!x) x=Allc();
    f(x)=max(f(x),f),g(x)=max(g(x),g);
    if(L==R) return ;
    int mid=L+R>>1;
    if(pos<=mid) Assign(lc(x),L,mid,pos,f,g);
    else Assign(rc(x),mid+1,R,pos,f,g);
}
void Merge(int &x,int y,int L,int R){
    if(!x||!y) return x|=y,void();
    int mid=L+R>>1;
    ans=max(ans,max(g(lc(x))+f(rc(y)),f(rc(x))+g(lc(y))));
    f(x)=max(f(x),f(y)),g(x)=max(g(x),g(y));
    if(L!=R) Merge(lc(x),lc(y),L,mid),Merge(rc(x),rc(y),mid+1,R);
}

pii Query(int x,int L,int R,int l,int r){
    if(!x) return {0,0};
    if(l<=L&&R<=r) return {f(x),g(x)};
    pii res={0,0};
    int mid=L+R>>1;
    if(l<=mid){
        pii lres=Query(lc(x),L,mid,l,r);
        res.first=max(res.first,lres.first);
        res.second=max(res.second,lres.second);
    }
    if(r>mid){
        pii rres=Query(rc(x),mid+1,R,l,r);
        res.first=max(res.first,rres.first);
        res.second=max(res.second,rres.second);
    }
    return res;
}

int a[N],rt[N],fa[N],n;
void DFS(int x){
    int f=1,g=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        int fy=Query(rt[y],0,inf,a[x]+1,inf).first+1;
        int gy=Query(rt[y],0,inf,0,a[x]-1).second+1;
        ans=max(ans,Query(rt[x],0,inf,a[x]+1,inf).first+gy);
        ans=max(ans,Query(rt[x],0,inf,0,a[x]-1).second+fy);
        f=max(f,fy),g=max(g,gy);
        Merge(rt[x],rt[y],0,inf);
    }
    Assign(rt[x],0,inf,a[x],f,g);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AdEg(u,v),AdEg(v,u);
    DFS(1);
    
    cout<<ans<<endl;

    return 0;
}