#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int siz[N],dep[N],st[N][20];
void dfs(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==st[x][0]) continue ;
        st[y][0]=x;
        dep[y]=dep[x]+1;
        dfs(y);
        siz[x]+=siz[y];
    }
}

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        
    }
}