#include<bits/stdc++.h>
using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int w[N],fa[N],hson[N];
long long val[N],dep[N];
void dfs1(int x){
    val[x]=dep[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+w[y];
        dfs1(y);
        val[x]=max(val[x],val[y]);
        if(val[y]>val[hson[x]]) hson[x]=y;
    }
}
long long ans[N];
void dfs2(int x,int t){
    ans[t]+=w[x];
    if(hson[x]) dfs2(hson[x],t);
    else return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        dfs2(y,y);
    }    
}

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>w[i];

    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        adeg(x,y);
        adeg(y,x);
    }
    dfs1(1);
    dfs2(1,1);

    long long res=0;
    priority_queue<long long> q;
    for(int i=1;i<=n;i++) q.push(ans[i]);
    for(int i=1;i<=k;i++,q.pop()) res+=q.top();

    cout<<res<<endl;

    return 0;
}