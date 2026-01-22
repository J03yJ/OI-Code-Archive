#include<bits/stdc++.h>

using namespace std;

ifstream fin("nice.in");
ofstream fout("nice.out");
#define cin fin
#define cout fout

namespace IO{
    const int P=(1ll<<31)-1;
    int N,M,A,B;
    void GetSeed(int &n,int &m){
        cin>>N>>M>>A>>B;
        n=N,m=M;
    }
    int GetInt(){
        A=((A^B)+(B>>16)+(B<<16))&P;
        B=((A^B)+(A>>16)+(A<<16))&P;
        return (A^B)%N+1;
    }
    void GetEdge(int &u,int &v){
        u=GetInt(),v=GetInt();
        if(u==v) GetEdge(u,v);
    }
    const int MOD=998244353;
    int now,num;
    void PutInt(int x){
        ++num,++x;
        now+=1ll*num*x%MOD;
        now%=MOD;
    }
    void Flush(){
        cout<<now<<endl;
        now=num=0;
    }
}

const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],adj=1,n,m;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dfn[N],low[N],ins[N],scc[N],dcnt,scnt;
vector<int> stk,bel[N];
void Tj(int x){
    stk.push_back(x);
    dfn[x]=low[x]=++dcnt;
    ins[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]){
            Tj(y);
            low[x]=min(low[x],low[y]);
        }else if(ins[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        bel[++scnt].clear();
        while(stk.size()){
            int p=stk.back();
            stk.pop_back();
            scc[p]=scnt;
            ins[p]=0;
            bel[scnt].push_back(p);
            if(p==x) break ;
        }
    }
}
int vis[N],ans;
void DFS(int x){
    vis[x]=1;
    ans+=bel[x].size();
    for(int u:bel[x]){
        for(int i=fi[u];i;i=ne[i]){
            int y=scc[to[i]];
            if(vis[y]) continue ;
            DFS(y);
        }
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        IO::GetSeed(n,m);
        for(int i=1,u,v;i<=m;i++){
            IO::GetEdge(u,v);
            AdEg(u,v);
            for(int i=1;i<=n;i++) if(!dfn[i]) Tj(i);
            for(int i=1;i<=scnt;i++){
                if(vis[i]) continue ;
                if(bel[i].size()>1) DFS(i);
            }
            IO::PutInt(ans);
            for(int i=1;i<=n;i++) dfn[i]=low[i]=scc[i]=ins[i]=0;
            for(int i=1;i<=scnt;i++) vis[i]=0,bel[i].clear();
            scnt=dcnt=ans=0;
            stk.clear();
        }
        IO::Flush();
        for(int i=1;i<=n;i++) fi[i]=0;
        adj=0;
    }

    return 0;
}