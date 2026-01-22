#include<bits/stdc++.h>

using namespace std;

const int maxn=1005;

int n,m,cnt;
int x,y,o,c,z,s,t,ans=1e9,minn=1e9,maxx;
int f[maxn],head[maxn];
bool vis[maxn];
queue<int> q;
struct Edge{
    int to,next,s,t,val;
}e[maxn*5];
void addEdge(int u,int v,int s,int t,int w){
    e[++cnt].to=v;e[cnt].val=w;e[cnt].next=head[u];head[u]=cnt;
    e[cnt].s=s,e[cnt].t=t;
}
void spfa(int x){
    for(int i=1;i<=n;i++)
        vis[i]=0,f[i]=1e9;
    f[s]=x;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        if(u==t) ans=min(ans,f[u]-x);
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            if(f[u]+e[i].val<=e[i].t){    
                if(max(e[i].s,f[u])+e[i].val<f[v]){    
                    f[v]=max(e[i].s,f[u])+e[i].val;
                    if(!vis[v]) q.push(v),vis[v]=0;
                }
            }
        }
    }
}
int main(){
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        cin>>x>>y>>o>>c>>z;
        if(c-z<o) continue;
        if(x==s) minn=min(minn,o),maxx=max(maxx,c-z);
        addEdge(x,y,o,c,z);
    }
    for(int i=minn;i<=maxx;i++)
        spfa(i);
    if(ans<1e9) cout<<ans;
    else cout<<"Impossible";
}