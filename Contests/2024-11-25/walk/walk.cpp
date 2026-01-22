#include<bits/stdc++.h>

using namespace std;

ifstream fin("walk.in");
ofstream fout("walk.out");
#define cin fin
#define cout fout

const int N=1e6+9;

int w[N],n,m;
vector<int> e[N];

auto Find(vector<int> &v,int x){
    for(auto it=v.begin();it!=v.end();it++) if(*it==x) return it;
    return v.end();
}
int Erase(int a,int b){
    auto it=Find(e[a],b);
    if(it==e[a].end()) return 1;
    e[a].erase(it);
    e[b].erase(Find(e[b],a));
    return 0;
}

long long siz[N],sum,g;
void DFS(int x,int fa){
    cout<<x<<' '<<fa<<endl;
    bool flag=1;
    siz[x]=w[x];
    for(int y:e[x]){
        if(y==fa) continue ;
        DFS(y,x);
        siz[x]+=siz[y];
        if(siz[y]>sum/2) flag=0;
    }
    if(sum-siz[x]>sum/2) flag=0;
    if(flag) g=x;
}
int dep[N];
void DFS2(int x,int fa){
    for(int y:e[x]){
        if(y==fa) continue ;
        dep[y]=dep[x]+1;
        DFS2(y,x);
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i],sum+=w[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    long long ans=0;
    while(m--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(Erase(a,b)) continue ;
        e[c].push_back(d);
        e[d].push_back(c);

        g=0,DFS(1,-1);
        dep[g]=0,DFS2(g,-1);
        long long res=0;
        for(int i=1;i<=n;i++) res+=2ll*w[i]*dep[i];
        ans^=res;

        e[a].push_back(b);
        e[b].push_back(a);
        Erase(c,d);
    }
    cout<<ans<<endl;

    return 0;
}