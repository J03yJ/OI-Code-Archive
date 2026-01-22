#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int M=1e3+9;
const int inf=1e9;

int n;
namespace Graph{
    int fi[N],ne[N],to[N],adj;
    void AdEg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }
    int dfn[N],low[N],bel[N],ins[N],dcnt,scnt;
    vector<int> stk;
    void Tj(int x){
        dfn[x]=low[x]=++dcnt;
        ins[x]=1,stk.push_back(x);
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!dfn[y]){
                Tj(y);
                low[x]=min(low[x],low[y]);
            }else if(ins[y]) low[x]=min(low[x],dfn[y]);
        }
        if(low[x]==dfn[x]){
            scnt++;
            while(stk.size()){
                int p=stk.back();
                stk.pop_back();
                ins[p]=0;
                bel[p]=scnt;
                if(p==x) break ;
            }
        }
    }
}
namespace SCCGraph{
    int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj=1;
    void AdEg(int x,int y,int z){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
        w[adj]=z;
    }
    int in[N],out[N],s,t;
    void Add(int x,int y,int z){
        // cout<<x<<' '<<y<<endl;
        AdEg(x,y,z);
        AdEg(y,x,0);
        out[x]++;
        in[y]++;
    }
    int lev[N],cur[N];
    bool BFS(){
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
    int DFS(int x,int mn){
        if(x==t) return mn;
        int lft=mn;
        for(int i=cur[x];i;i=ne[i]){
            cur[x]=i;
            int y=to[i];
            if(!w[i]) continue ;
            if(lev[y]!=lev[x]+1) continue ;
            int tmp=DFS(y,min(w[i],lft));
            lft-=tmp;
            w[i]-=tmp;
            w[i^1]+=tmp;
            if(!lft) return mn;
        }
        return mn-lft;
    }
    int MaxFlow(){
        int sum=0;
        while(BFS()){
            sum+=DFS(s,inf);
        }
        return sum;
    }
}

string s[N];
int a[M][M];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i].back()==s[j].front()) Graph::AdEg(i,j);
        }
    }
    for(int i=1;i<=n;i++) if(!Graph::dfn[i]) Graph::Tj(i);

    int m=Graph::scnt;
    for(int i=1;i<=n;i++) if(!Graph::bel[i]) Graph::bel[i]=++m;
    SCCGraph::s=m*2+1;
    SCCGraph::t=SCCGraph::s+1;

    for(int x=1;x<=n;x++){
        for(int i=Graph::fi[x];i;i=Graph::ne[i]){
            int y=Graph::to[i];
            if(Graph::bel[x]==Graph::bel[y]) continue ;
            a[Graph::bel[x]][Graph::bel[y]]=1;
        }
    }
    for(int k=1;k<=m;k++){
        for(int i=1;i<=m;i++){
            if(i==k) continue ;
            for(int j=1;j<=m;j++){
                if(i==j) continue ;
                if(j==k) continue ;
                a[i][j]|=a[i][k]&a[k][j];
            }
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]){
                // cout<<i<<' '<<j<<endl;
                SCCGraph::Add(i,j+m,inf);
            }
        }
    }
    for(int i=1;i<=m;i++){
        SCCGraph::Add(SCCGraph::s,i,1);
        SCCGraph::Add(i+m,SCCGraph::t,1);
    }
    cout<<m-SCCGraph::MaxFlow()<<endl;

    return 0;
}