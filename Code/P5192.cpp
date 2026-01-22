#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int inf=1e9+7;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],in[N],out[N],adj=1;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
inline void AddFlow(int x,int y,int z){AddEdge(x,y,z);AddEdge(y,x,0);}
inline void Clear(int lim){
    for(int i=1;i<=lim;i++) in[i]=out[i]=fi[i]=0;
    for(int i=1;i<=adj;i++) ne[i]=to[i]=w[i]=0;
    adj=1;
}

int lvl[N],cur[N],n,m;
inline bool BFS(int s,int t,int lim){
    for(int i=1;i<=lim;i++) lvl[i]=0,cur[i]=fi[i];
    queue<int> q;
    q.push(s),lvl[s]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==t) return 1;
        for(int i=fi[x];i;i=ne[i]){
            if(!w[i]) continue ;
            int y=to[i];
            if(lvl[y]) continue ;
            lvl[y]=lvl[x]+1;
            q.push(y);
        }
    }
    return 0;
}
inline int DFS(int x,int t,int r){
    if(x==t) return r;
    int k=r;
    for(int &i=cur[x];i;i=ne[i]){
        if(!w[i]) continue ;
        int y=to[i];
        if(lvl[y]!=lvl[x]+1) continue ;
        int tmp=DFS(y,t,min(k,w[i]));
        k-=tmp,w[i]-=tmp,w[i^1]+=tmp;
        if(!k) return r;
    }
    return r-k;
}
inline int MaxFlow(int s,int t,int lim){
    int sum=0;
    while(BFS(s,t,lim)) sum+=DFS(s,t,inf);
    return sum;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    while(cin>>n>>m){
        int s=n+m+1,t=n+m+2,S=s+2,T=t+2;
        for(int i=1,lim;i<=m;i++){
            cin>>lim;
            out[n+i]+=lim,in[t]+=lim;
            AddFlow(n+i,t,inf-lim);
        }
        for(int i=1,c,d;i<=n;i++){
            cin>>c>>d;
            AddFlow(s,i,d);
            for(int j=1,u,l,r;j<=c;j++){
                cin>>u>>l>>r,u++;
                in[n+u]+=l,out[i]+=l;
                AddFlow(i,n+u,r-l);
            }
        }
        int sum=0;
        for(int i=1;i<=t;i++){
            if(in[i]>out[i]) AddFlow(S,i,in[i]-out[i]),sum+=in[i]-out[i];
            else if(out[i]>in[i]) AddFlow(i,T,out[i]-in[i]);
        }
        AddFlow(t,s,inf);
        if(MaxFlow(S,T,T)<sum){
            cout<<-1<<endl<<endl;
            Clear(T);
            continue ;
        }
        int ans=w[adj];
        w[adj]=w[adj^1]=0;
        ans+=MaxFlow(s,t,t);
        cout<<ans<<endl<<endl;
        Clear(T);
    }

    return 0;
}