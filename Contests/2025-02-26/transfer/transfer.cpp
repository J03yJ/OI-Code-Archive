#include<bits/stdc++.h>

using namespace std;

ifstream fin("transfer.in");
ofstream fout("transfer.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e2+9;
const int M=1e5+9;
const int mod=998244353;
const ll inf=1e18;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}

int v[N],l[N],r[N];
vector<int> e[N];
int n;

int fi[M],ne[M],to[M],w[M],cst[M],adj=1;
inline void AddEdge(int x,int y,int z,int c){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
    cst[adj]=c;
}
inline void AddFlow(int x,int y,int z,int c){
    AddEdge(x,y,z,c),AddEdge(y,x,0,-c);
}

ll dis[M];
int inq[M],pre[M],s,t;
inline bool SPFA(){
    for(int i=1;i<=t;i++) dis[i]=inf;
    dis[s]=0;
    queue<int> q;
    q.push(s),inq[s]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        inq[x]=0;
        for(int i=fi[x];i;i=ne[i]){
            if(!w[i]) continue ;
            int y=to[i];
            if(dis[x]+cst[i]<dis[y]){
                pre[y]=i^1;
                dis[y]=dis[x]+cst[i];
                if(!inq[y]) q.push(y),inq[y]=1;
            }
        }
    }
    return dis[t]!=inf;
}
inline ll MCMF(){
    ll ans=0;
    while(SPFA()){
        if(dis[t]>=0) break ;
        ll f=inf,c=0;
        int cur=t;
        while(cur!=s){
            c+=cst[pre[cur]^1];
            f=min(f,ll(w[pre[cur]^1]));
            cur=to[pre[cur]];
        }
        cur=t;
        while(cur!=s){
            w[pre[cur]^1]-=f;
            w[pre[cur]]+=f;
            cur=to[pre[cur]];
        }
        ans+=f*c;
    }
    return ans;
}

inline void DFS(int x,vector<int> &v){
    v.push_back(x);
    for(int y:e[x]) DFS(y,v);
}
inline void Clear(){
    for(int i=1;i<=t;i++) fi[i]=0;
    adj=1;
}
inline int Solve(){
    Clear();
    s=n<<1|1,t=s+1;
    for(int i=1;i<=n;i++){
        AddFlow(s,i,1,-v[i]);
        vector<int> tmp;
        DFS(i,tmp);
        for(int j:tmp) AddFlow(i,j+n,1,0);
        AddFlow(i+n,t,1,v[i]);
    }
    return (-MCMF())%mod;
}

inline int Work(int p){
    if(p>n) return Solve();
    int sum=0;
    for(int i=l[p];i<=r[p];i++){
        v[p]=i;
        AddAs(sum,Work(p+1));
    }
    return sum;
}

signed main(){
    int Tid,T;
    cin>>Tid>>T;
    while(T--){
        cin>>n;
        for(int i=2,fa;i<=n;i++) cin>>fa,e[fa].push_back(i);
        for(int i=1;i<=n;i++) cin>>l[i];
        for(int i=1;i<=n;i++) cin>>r[i];

        cout<<Work(1)<<endl;

        for(int i=1;i<=n;i++) e[i].clear();
    }

    return 0;
}