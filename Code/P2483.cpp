#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pdi=pair<double,int>;
const int N=2e5+9;
const double eps=1e-8;
const double inf=1e18;

struct Node{
    int lc,rc,dat;
}tr[N*40];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat

int cnt;
mt19937 rng(4649);
inline int Allc(){return ++cnt;}
inline int Allc(int k){int x=Allc();dat(x)=k;return x;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline int Merge(int x,int y){
    if(!x||!y) return Clone(x|y);
    if(dat(x)<dat(y)) swap(x,y);
    if(rng()&1) swap(lc(x),rc(x));
    lc(x)=Merge(lc(x),y);
    return x;
}
inline int Make(int l,int r,const vector<int> &v){
    if(l>r) return 0;
    if(l==r) return Allc(v[l]);
    int mid=l+r>>1;
    int x=Allc(v[mid]);
}

namespace G{
    int fi[N],ne[N],to[N],adj;
    double w[N];
    inline void AddEdge(int x,int y,double z){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
        w[adj]=z;
    }
}
namespace R{
    int fi[N],ne[N],to[N],adj;
    double w[N];
    inline void AddEdge(int x,int y,double z){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
        w[adj]=z;
    }
}

double dis[N],esum;
int vis[N],fa[N],pe[N],ist[N],n,m,s,t;
inline void Dij(){
    using namespace R;
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    priority_queue<pdi> q;
    q.push({dis[t]=0,t});
    while(q.size()){
        int x=sec(q.top());
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(dis[x]+w[i]<dis[y]){
                dis[y]=dis[x]+w[i];
                fa[y]=x;
                ist[pe[y]]=0;
                ist[pe[y]=i]=1;
                q.push({-dis[y],y});
            }
        }
    }
}
inline void Link(){
    using namespace R;
    for(int x=1;x<=n;x++){
        for(int i=fi[x];i;i=ne[i]){
            if(ist[i]) continue ;
            int y=to[i];
            G::AddEdge(y,x,dis[y]+w[i]-dis[x]);
        }
    }
}

vector<int> son[N];
inline void GetHeap(){
    vector<int> tmp;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        double z;
        cin>>x>>y>>z;
        R::AddEdge(y,x,z);
    }
    s=1,t=n;

    Dij(),Link();
    
    return 0;
}