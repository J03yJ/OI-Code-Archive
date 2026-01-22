#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int b[N],fa[N],d[N],n,k;
int DFS1(int x){
    int diss=n;
    if(b[x]) diss=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        diss=min(DFS1(y),diss);
    }
    d[x]=diss;
    return diss+1;
}
void DFS2(int x,int dis){
    d[x]=min(d[x],dis);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        DFS2(y,d[x]+1);
    }
}

int main(){
    cin>>n>>k;
    for(int i=1,x;i<=k;i++) cin>>x,b[x]=1;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    DFS1(1);
    DFS2(1,n);

    for(int i=1;i<=n;i++) cout<<d[i]<<' ';cout<<endl;

    return 0;
}