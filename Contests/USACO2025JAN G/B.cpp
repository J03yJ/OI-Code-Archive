#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

const int N=2e5+9;

int n,m;
vector<int> e[N];
char op[N];

int fa[N],siz[N],t[N];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
ll ans[N],res;
inline void Merge(int x,int y){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    fa[y]=x;
    res+=1ll*siz[x]*siz[y];
    siz[x]+=siz[y];
}
vector<pii> ins[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    For(i,1,n) cin>>op[i],fa[i]=i;
    For(i,1,m){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    For(x,1,n) t[x]=op[x]=='1'?n+1:x;
    For(x,1,n){
        for(int y:e[x]) if(x<y) ins[min(t[x],t[y])].push_back({x,y});
    }
    for(pii p:ins[n+1]) Merge(p.first,p.second);
    Rof(x,n,1){
        for(pii p:ins[x]) Merge(p.first,p.second);
        res+=siz[Find(x)];
        siz[Find(x)]++;
        ans[x]=res;
    }

    For(x,1,n) cout<<ans[x]<<endl;

    return 0;
}