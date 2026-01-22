#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;
const int M=N*N;
const int inf=1e9;

int fi[N],ne[M<<2],to[M<<2],w[N<<2],adj=1;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
inline void AddFlow(int x,int y,int z){AddEdge(x,y,z),AddEdge(y,x,0);}

int lev[N],cur[N],s,t;
inline bool BFS(){
    for(int i=1;i<=t;i++) lev[i]=0,cur[i]=fi[i];
    queue<int> q;
    q.push(s);
    lev[s]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==t) return 1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(lev[y]) continue ;
            lev[y]=lev[x]+1;
            q.push(y);
        }
    }
    return 0;
}
inline int DFS(int x,int lim){
    if(x==t) return lim;
    int k=lim;
    for(int &i=cur[x];i;i=ne[i]){
        int y=to[i];
        if(!w[i]) continue ;
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=DFS(y,min(k,w[i]));
        k-=tmp,w[i]-=tmp,w[i^1]+=tmp;
        if(!k) return lim;
    }
    return lim-k;
}

int a[N],f[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        f[i]=1;
        for(int j=1;j<i;j++) if(a[j]<=a[i]) f[i]=max(f[i],f[j]+1);
    }
    int res=0;
    for(int i=1;i<=n;i++) res=max(res,f[i]);
    cout<<res<<endl;

    s=n+n+1,t=s+1;
    for(int i=1;i<=n;i++) AddFlow(i,i+n,1);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++) if(a[i]<=a[j]&&f[i]+1==f[j]) AddFlow(i+n,j,1);
    }
    for(int i=1;i<=n;i++) if(f[i]==1) AddFlow(s,i,1);
    for(int i=1;i<=n;i++) if(f[i]==res) AddFlow(i+n,t,1);

    int ans=0;
    while(BFS()) ans+=DFS(s,inf);
    cout<<ans<<endl;

    if(res==1){
        cout<<n<<endl;
        return 0;
    }
    AddFlow(1,1+n,inf),AddFlow(s,1,inf);
    if(f[n]==res) AddFlow(n,n+n,inf),AddFlow(n+n,t,inf);
    while(BFS()) ans+=DFS(s,inf);
    cout<<ans<<endl;

    return 0;
}