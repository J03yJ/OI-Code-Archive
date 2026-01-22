#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;
const int inf=2e9;
const int p=998244353;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout

int u[N],v[N];

int fi[N],ne[N<<1],to[N<<1],adj=1;
bool adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

bool blk[N<<1],vis[N];
int e[N];

int dis[N],n;
void dfs(int x,bool f=0){
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        if(blk[i]) continue ;
        int y=to[i];
        if(dis[y]!=inf) continue ;
        dis[y]=dis[x]+1;
        // cout<<x<<'-'<<y<<'-'<<i<<endl;
        if(f) e[y]=i;
        dfs(y,f);
    }
}
int getD(int s){
    // cout<<"%%"<<endl;
    for(int i=1;i<=n;i++) dis[i]=inf;
    dis[s]=0;
    int mx=0,pos=s;
    dfs(s);
    for(int i=1;i<=n;i++) if(dis[i]!=inf&&dis[i]>mx) mx=dis[i],pos=i;
    // for(int i=1;i<=n;i++) cout<<dis[i]<<' ';cout<<endl;
    for(int i=1;i<=n;i++) dis[i]=inf;
    dis[pos]=0;
    dfs(pos);
    int ans=0;
    for(int i=1;i<=n;i++) if(dis[i]!=inf) ans=max(ans,dis[i]);
    // for(int i=1;i<=n;i++) cout<<dis[i]<<' ';cout<<endl;
    return ans;
}

int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}
bool checkA(){
    for(int i=1;i<n;i++) if(u[i]!=1) return 0;
    return 1;
}
bool checkB(){
    for(int i=1;i<n;i++) if(u[i]!=i||v[i]!=i+1) return 0;
    return 1;
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++) cin>>u[i]>>v[i];

    if(checkA()){
        cout<<(2*((qpow(2,n-1)-n+p)%p)%p+n-1)%p<<endl;
        return 0;
    }
    if(checkB()){
        cout<<qpow(2,n-2)%p*(n-1)%p<<endl;
        return 0;
    }

    for(int i=1;i<n;i++) adeg(u[i],v[i]),adeg(v[i],u[i]);
    for(int i=1;i<=n;i++) dis[i]=inf;dis[1]=0;
    dfs(1,1);
    // for(int i=1;i<=n;i++) cout<<e[i]<<' ';cout<<endl;
    int ans=0;
    for(int sta=0;sta<(1<<n-1);sta++){
        for(int i=0;i<n-1;i++){
            if((sta>>i)&1) blk[e[i+2]]=blk[e[i+2]^1]=1;
            else blk[e[i+2]]=blk[e[i+2]^1]=0;
        }
        // for(int i=1;i<=adj;i++) cout<<blk[i]<<' ';cout<<endl;
        for(int i=1;i<=n;i++) vis[i]=0;
        int res=0;
        for(int i=1;i<=n;i++){
            if(vis[i]) continue ;
            res+=getD(i);
        }
        ans=(ans+res)%p;
        // cout<<endl;
    }

    cout<<ans<<endl;

    return 0;
}