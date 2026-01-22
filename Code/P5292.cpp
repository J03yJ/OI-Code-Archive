#include<bits/stdc++.h>

using namespace std;

#define int long long
const int p=1e9+7;
const int N=5e5+9;

int n,m,H;
int fa[N],ans[N],cur[N];
vector<tuple<int,int,int>> q;
inline int trs(int x,int y){
    return (x-1)*m+y;
}
inline int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    fa[find(y)]=find(x);
}

signed main(){
    cin>>n>>m>>H;
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int h;
            cin>>h;
            q.push_back(make_tuple(h,trs(i,j),trs(i,j+1)));
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int h;
            cin>>h;
            q.push_back(make_tuple(h,trs(i,j),trs(i+1,j)));
        }
    }

    sort(q.begin(),q.end());
    for(int i=1;i<=n*m;i++) fa[i]=i,cur[i]=-1;
    for(tuple<int,int,int> Q:q){
        int h=get<0>(Q),u=get<1>(Q),v=get<2>(Q);
        u=find(u);v=find(v);
        if(u==v) continue ;
        ans[u]=(ans[u]+h-cur[u])%p;
        ans[v]=(ans[v]+h-cur[v])%p;
        // cout<<ans[u]<<' '<<ans[v]<<endl;
        merge(u,v);
        ans[u]=ans[u]*ans[v]%p;
        cur[u]=h;
        // cout<<u<<' '<<v<<' '<<ans[u]<<' '<<cur[u]<<endl;
    }
    ans[find(1)]=(ans[find(1)]+H-cur[find(1)])%p;
    
    cout<<ans[find(1)]<<endl;

    return 0;
}