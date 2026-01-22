#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e6+9;

int u[N],v[N],w[N],n,m,lim;
vector<int> vec[N];

int fa[N],siz[N];
inline int Find(int x){return fa[x]==x?x:Find(fa[x]);}
inline void Merge(int x,int y,vector<array<int,3>> &rb){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    rb.push_back({x,fa[x],siz[x]});
    rb.push_back({y,fa[y],siz[y]});
    siz[x]+=siz[y];
    fa[y]=x;
}

int ans=-1;
inline void Div(int l,int r){
    if(l==r){
        if(siz[Find(1)]==n) ans=l;
        return ;
    }
    int mid=l+r>>1;
    vector<array<int,3>> rb;
    for(int i=mid+1;i<=r;i++) for(int j:vec[i]) Merge(u[j],v[j],rb);
    Div(l,mid);
    while(rb.size()){
        auto t=rb.back();
        rb.pop_back();
        fa[t[0]]=t[1];
        siz[t[0]]=t[2];
    }
    if(~ans) return ;
    for(int i=l;i<=mid;i++) for(int j:vec[i]) Merge(u[j],v[j],rb);
    Div(mid+1,r);
    while(rb.size()){
        auto t=rb.back();
        rb.pop_back();
        fa[t[0]]=t[1];
        siz[t[0]]=t[2];
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
        vec[w[i]].push_back(i);
        lim=max(lim,w[i]);
    }
    iota(fa+1,fa+n+1,1);
    fill(siz+1,siz+n+1,1);

    Div(0,lim+1);
    cout<<ans<<endl;

    return 0;
}