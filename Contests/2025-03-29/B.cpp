#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const ll inf=1e18;
const int N=2e3+9;
const int M=5e6+9;

int n;
ll a[N],b[N],c[N];

namespace Flow{
    ll w[N][N];
    inline void AddEdge(int x,int y,ll z){w[x][y]+=z;}
    inline void AddFlow(int x,int y,ll z){return AddEdge(x,y,z),AddEdge(y,x,0);}

    int lev[N],cur[N],s,t;
    inline bool BFS(){
        for(int i=1;i<=t;i++) lev[i]=0,cur[i]=1;
        lev[s]=1;
        queue<int> q;
        q.push(s);
        while(q.size()){
            int x=q.front();
            q.pop();
            if(x==t) return 1;
            for(int y=1;y<=t;y++){
                if(!w[x][y]) continue ;
                if(lev[y]) continue ;
                lev[y]=lev[x]+1;
                q.push(y);
            }
        }
        return 0;
    }
    inline ll DFS(int x,ll lft){
        if(x==t) return lft;
        ll k=lft;
        for(int &y=cur[x];y<=t;y++){
            if(!w[x][y]) continue ;
            if(lev[y]!=lev[x]+1) continue ;
            ll tmp=DFS(y,min(k,w[x][y]));
            w[x][y]-=tmp;
            w[y][x]+=tmp;
            k-=tmp;
            if(!k) return lft;
        }
        return lft-k;
    }
    inline ll MF(){
        ll sum=0;
        while(BFS()) sum+=DFS(s,inf);
        return sum;
    }

    inline void Clear(){
        for(int i=1;i<=t;i++){
            for(int j=1;j<=t;j++) w[i][j]=0;
        }
    }
}
ll ans;string str;
namespace Tree{
    int fi[N],ne[N<<1],to[N<<1],adj;
    inline void AddEdge(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }

    int siz[N],fa[N],vis[N],id[N];
    inline void GetGrv(int x,int tot,int f,int &grv){        
        bool flag=1;
        siz[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            if(y==f) continue ;
            GetGrv(y,tot,x,grv);
            siz[x]+=siz[y];
            if(siz[y]>tot/2) flag=0;
        }
        if(tot-siz[x]>tot/2) flag=0;
        if(flag) grv=x; 
    }
    inline void GetMemb(int x,vector<int> &v){
        siz[x]=1;
        v.push_back(x);
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            if(y==fa[x]) continue ;
            fa[y]=x;
            GetMemb(y,v);
            siz[x]+=siz[y];
        }
    }
    inline void TDiv(int x,int tot){
        GetGrv(x,tot,0,x);
        vis[x]=1;

        ll res=0;
        vector<int> p;
        fa[x]=0,GetMemb(x,p);
        Flow::s=tot+1;
        Flow::t=tot+2;
        ll bsum=0;
        for(int i=0;i<tot;i++) bsum+=b[p[i]];
        for(int i=0;i<tot;i++) id[p[i]]=i;
        for(int i=0;i<tot;i++){
            ll w=a[p[i]]*bsum-c[p[i]];
            if(w<0) Flow::AddFlow(i+1,Flow::t,-w);
            else{
                res+=w;
                Flow::AddFlow(Flow::s,i+1,w);
            }
        }
        for(int i=1;i<tot;i++) Flow::AddFlow(i+1,id[fa[p[i]]]+1,inf);
        for(int i=0;i<tot;i++){
            for(int j=0;j<tot;j++){
                if(i==j) continue ;
                Flow::AddFlow(i+1,j+1,a[p[i]]*b[p[j]]);
            }
        }
        
        res-=Flow::MF();
        if(res>ans){
            Flow::BFS();
            ans=res;
            str=string(n,'0');
            for(int i=0;i<tot;i++) if(Flow::lev[i+1]) str[p[i]-1]='1';
        }
        Flow::Clear();

        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]) continue ;
            TDiv(y,siz[y]);
        }
    }

    inline void Clear(){
        for(int i=1;i<=n;i++) fi[i]=vis[i]=0;
        adj=1;
    }
}

inline void Solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        Tree::AddEdge(u,v);
        Tree::AddEdge(v,u);
    }

    ans=0,str=string(n,'0');
    Tree::TDiv(1,n);
    cout<<ans<<endl;
    cout<<str<<endl;

    Tree::Clear();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}