#include<bits/stdc++.h>

using namespace std;

ifstream fin("sheriruth.in");
ofstream fout("sheriruth.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=1.5e6+9;
const int lgN=2e1;

vector<int> e[N],scc[N];

int fa[N],siz[N],w[N],to[N],vis[N],n,m,q,mod,o;
inline void InitDSU(){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    siz[x]+=siz[y];
    fa[y]=x;
    for(int u:e[y]) if(Find(u)!=x) e[x].push_back(u);
}
int srk[N];
inline void Shrink(int x){
    x=Find(x);
    srk[x]=1;
    queue<int> q;
    vector<int> p;
    vis[x]=1;
    q.push(x);
    // cout<<"Shrink "<<x<<" : "<<endl;
    while(q.size()){
        int u=Find(q.front());
        p.push_back(u);
        q.pop();
        // cout<<" -> "<<u<<'/'<<Find(u)<<endl;
        srk[u]=1;
        for(int v:e[u]){
            v=Find(v);
            if(vis[v]) continue ;
            vis[v]=1;
            q.push(v);
        }
    }
    for(int u:p) vis[u]=0;
    for(int u:p) Merge(x,u);
    // for(int u:p) cout<<u<<' ';cout<<endl;
    x=Find(x);
    vector<int> tmp;
    for(int u:e[x]) if(Find(u)!=x) tmp.push_back(x);
    e[x]=tmp; 
}
inline int Calc(int n){
    int ans=1,cur=1;
    for(int i=n;i>=1;i--){
        cur=1ll*cur*i%mod;
        ans=(ans+cur)%mod;
    }
    return ans;
}

int anc[N][lgN],dep[N];
vector<int> son[N];
inline int Anc(int x,int d){
    for(int k=lgN-1;~k;k--){
        // cout<<" - "<<k<<" : "<<anc[x][k]<<' '<<dep[anc[x][k]]<<endl;
        if(dep[anc[x][k]]>=d) x=anc[x][k];
    }
    return x;
}
inline void DFS(int x){
    for(int y:son[x]){
        dep[y]=dep[x]+1;
        DFS(y);
    }
}
map<pii,int> scnt,vcnt;

signed main(){
    cin>>n>>m>>q>>mod>>o;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        u++,v++;
        e[u].push_back(v);
    }

    InitDSU();
    for(int i=1;i<=n;i++){
        if(e[i].size()<=1) continue ;
        // cout<<"~ "<<i<<" : ";
        for(int j=1;j<e[i].size();j++) /*cout<<Find(e[i][0])<<'/'<<Find(e[i][j])<<' ',*/Merge(e[i][0],e[i][j]);
        // cout<<endl;
    }
    for(int i=1;i<=n;i++){
        if(e[i].size()<=1) continue ;
        // cout<<"S "<<i<<" : ";
        for(int j=0;j<e[i].size();j++) Shrink(e[i][j]);
        // cout<<endl;
    }
    for(int i=1;i<=n;i++){
        if(fa[i]!=i) continue ;
        vector<int> tmp;
        for(int j:e[i]) if(Find(j)!=i) tmp.push_back(j);
        e[i]=tmp;
    }
    
    for(int i=1;i<=n;i++){
        if(fa[i]!=i) continue ;
        // cout<<"# "<<i<<" : ";
        // for(int j:e[i]) cout<<Find(j)<<' ';cout<<endl;
    }
    // for(int i=1;i<=300;i++) cout<<i<<'/'<<Calc(i)<<' ';cout<<endl;;
    
    for(int i=1;i<=n;i++) if(fa[i]==i) w[i]=Calc(siz[i]-2);
    for(int i=1;i<=n;i++) if(fa[i]==i&&e[i].size()) to[i]=Find(e[i].front());
    for(int i=1;i<=n;i++){
        if(fa[i]!=i) continue ;
        int cur=i,flag=0;
        while(cur){
            vis[cur]=i;
            cur=to[cur];
            if(vis[cur]){
                if(vis[cur]==i) flag=1;
                break ;
            }
        }
        if(!flag) continue ;
        int x=cur;
        do{
            // cout<<x<<" : "<<cur<<endl;
            Merge(x,cur);
            cur=to[cur];
        }while(x!=cur);
        x=Find(x);
        to[x]=0,w[x]=1;
    }
    for(int i=1;i<=n;i++){
        if(fa[i]!=i) continue ;
        vector<int> tmp;
        for(int j:e[i]) if(Find(j)!=i) tmp.push_back(j);
        e[i]=tmp;
    }
    for(int i=1;i<=n;i++) if(fa[i]==i&&e[i].size()) to[i]=Find(e[i].front());
    // for(int i=1;i<=n;i++){
    //     if(fa[i]!=i) continue ;
    //     vector<int> tmp=e[i];
    //     for(int &j:tmp) j=Find(j);
    //     tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    //     if(tmp.size()>2){
    //         cout<<"!? "<<i<<" : ";
    //         for(int j:tmp) cout<<Find(j)<<' ';cout<<endl;
    //     }
    // }
    
    vector<int> p;
    for(int i=1;i<=n;i++) if(fa[i]==i) p.push_back(i);
    for(int i=1;i<=n;i++) scc[Find(i)].push_back(i);
    // for(int i=1;i<=n;i++) cout<<Find(i)<<' ';cout<<endl;
    for(int i=1;i<=n;i++) anc[i][0]=to[i],son[to[i]].push_back(i);
    for(int k=1;k<lgN;k++){
        for(int i:p) anc[i][k]=anc[anc[i][k-1]][k-1];
    }
    for(int x:p){
        if(to[x]) continue ;
        dep[x]=1;
        DFS(x);
    }
    for(int i=1;i<=n;i++){
        if(fa[i]!=i) continue ;
        for(int j:e[i]){
            scnt[{i,Find(j)}]++;
            vcnt[{i,j}]++;
        }
    }

    while(q--){
        int u,v;
        cin>>u>>v;
        u++,v++;
        int x=Find(u),y=Find(v);
        // cout<<u<<' '<<v<<' '<<x<<' '<<y<<endl;
        // int cur=x;
        // cout<<"# ";while(cur) cout<<cur<<'/'<<e[cur].size()<<' ',cur=to[cur];cout<<endl;
        // cur=y;
        // cout<<"# ";while(cur) cout<<cur<<'/'<<e[cur].size()<<' ',cur=to[cur];cout<<endl;
        // cout<<Anc(x,1)<<' '<<Anc(y,1)<<endl;
        if(Anc(x,1)!=Anc(y,1)){
            cout<<0<<endl;
            continue ;
        }
        if(u==v){
            cout<<1%mod<<endl;
            continue ;
        }
        if(x==y){
            cout<<w[x]%mod<<endl;
            continue ;
        }
        if(dep[x]<dep[y]||Anc(x,dep[y])!=y){
            // cout<<dep[x]<<' '<<dep[y]<<' '<<Anc(x,dep[y])<<endl;
            cout<<0<<endl;
            continue ;
        }
        x=Anc(x,dep[y]+1);
        // cout<<x<<' '<<y<<endl;
        int cnt=(1ll*w[y]*(scnt[{x,y}]-vcnt[{x,v}])+vcnt[{x,v}])%mod;
        cout<<cnt<<endl;
        // cout<<scnt[{x,y}]<<' '<<vcnt[{x,v}]<<' '<<w[y]<<' '<<siz[y]<<endl;
        // cout<<scc[y].size()<<" : ";
    }

    return 0;
}

// 41764 344816