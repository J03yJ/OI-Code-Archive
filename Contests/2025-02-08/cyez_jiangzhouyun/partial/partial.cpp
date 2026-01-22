#include<bits/stdc++.h>

using namespace std;

ifstream fin("partial.in");
ofstream fout("partial.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;
using ll=long long;
const ll inf=1e18;

string a;
int n,m;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int siz[N],dep[N],fa[N],hson[N];
inline void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x,dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int top[N],dfn[N],dcnt;
inline void DFS2(int x,int t){
    top[x]=t;
    dfn[x]=++dcnt;
    if(hson[x]) DFS2(hson[x],t);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
}

namespace Brute{
    inline bool Check(){return 1ll*n*n*m<=1e9;}
    vector<ll> Merge(vector<ll> f,vector<ll> g){
        vector<ll> h(f.size()+g.size()-1,-inf);
        for(int i=0;i<f.size();i++){
            for(int j=0;j<g.size();j++) h[i+j]=max(h[i+j],f[i]+g[j]);
        }
        return h;
    }
    inline vector<ll> Work(int x){
        vector<ll> res({0});
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            vector<ll> tmp=Work(y);
            res=Merge(res,tmp);
        }
        res.push_back(-inf);
        if(a[x]=='1'){
            for(int i=res.size()-2;~i;i--) res[i+1]=max(res[i+1],res[i]);
        }else if(a[x]=='0'){
            for(int i=res.size()-1;~i;i--) res[i]+=i;
        }else if(a[x]=='?'){
            for(int i=res.size()-1;~i;i--){
                if(i+1<res.size()) res[i+1]=max(res[i+1],res[i]);
                res[i]+=i;
            }
        }
        return res;
    }
    inline void Solve(){
        while(m--){
            int x;char c;
            cin>>x>>c;
            a[x]=c;
            vector<ll> tmp=Work(1);
            ll res=-inf;
            for(ll x:tmp) res=max(res,x);
            cout<<res<<endl;
        }
    }
}
namespace Flower{
    inline bool Check(){
        int cnt=0;
        for(int i=fi[1];i;i=ne[i]) cnt++;
        return cnt==n-1;
    }
    inline void Solve(){
        for(int x=1;x<=n;x++) if(a[x]=='?') a[x]=x==1?'0':'1';
        int cnt=0;
        for(int x=2;x<=n;x++) if(a[x]=='1') cnt++;
        while(m--){
            int x;char c;
            cin>>x>>c;
            if(c=='?') c=x==1?'0':'1';
            if(x!=1) cnt-=a[x]=='1';
            a[x]=c;
            if(x!=1) cnt+=a[x]=='1';
            cout<<(a[1]=='0'?cnt:0)<<endl;
        }
    }
}
namespace NoSwitch{
    int tr[N];
    inline void Add(int x,int k){
        while(x<=n){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    inline int Ask(int x){
        int sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
    inline int Ask0(int l,int r){return (r-l+1)-(Ask(r)-Ask(l-1));}
    inline int Ask1(int l,int r){return Ask(r)-Ask(l-1);}
    inline int Count(int x){
        int cnt=0;
        x=fa[x];
        while(x){
            cnt+=Ask0(dfn[top[x]],dfn[x]);
            x=fa[top[x]];
        }
        return cnt;
    }
    inline void Solve(){
        DFS1(1),DFS2(1,1);
        for(int i=1;i<=n;i++) if(a[i]=='1') Add(dfn[i],1);
        ll ans=0;
        for(int i=1;i<=n;i++) if(a[i]=='0') ans+=Ask1(dfn[i],dfn[i]+siz[i]-1);
        while(m--){
            int x;char c;
            cin>>x>>c;
            if(c!=a[x]){
                if(c=='0'){
                    ans-=Count(x);
                    a[x]=1,Add(dfn[x],-1);
                    ans+=Ask1(dfn[x],dfn[x]+siz[x]-1);
                }else{
                    ans+=Count(x);
                    ans-=Ask1(dfn[x],dfn[x]+siz[x]-1);
                    a[x]=0,Add(dfn[x],1);
                }
            }
            cout<<ans<<endl;
        }
    }
}

signed main(){
    cin>>n>>m>>a;
    a.insert(a.begin(),'#');
    for(int i=2,fa;i<=n;i++) cin>>fa,AddEdge(fa,i);

    if(Brute::Check()) Brute::Solve();
    else if(Flower::Check()) Flower::Solve();
    else NoSwitch::Solve();

    return 0;
}