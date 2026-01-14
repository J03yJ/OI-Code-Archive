#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],d[N],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    d[y]++;
}

int siz[N],fa[N],n;
long long ans;
void DFS(int x){
    int cnt=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        siz[x]+=siz[y];
        if(d[y]==2) cnt++;
    }
    if(d[x]==2){
        ans+=siz[x]-cnt;
        siz[x]=1;
    }else if(d[x]!=3) siz[x]=0;
}
void Solve(int x,int s){
    ans+=siz[x]*s;
    int sum=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        sum+=siz[y];
    }
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(d[x]==3) Solve(y,sum-siz[y]);
        else Solve(y,0);
    }
}

int main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    DFS(1);
    ans<<=1;
    Solve(1,0);
    ans>>=1;
    
    cout<<ans<<endl;

    return 0;
}