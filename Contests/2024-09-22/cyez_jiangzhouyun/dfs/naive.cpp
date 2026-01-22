#include<bits/stdc++.h>

using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.ans");
#define cin fin
#define cout fout

const int N=1e2+9;

int fi[N],to[N<<1],ne[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dfn[N],ans[N][N],siz[N],mx[N],mn[N],fa[N],n;
void DFS(int x){
    siz[x]=1;
    mx[x]=mn[x]=dfn[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        siz[x]+=siz[y];
        mx[x]=max(mx[x],mx[y]);
        mn[x]=min(mn[x],mn[y]);
    }
}
bool Check(){
    DFS(1);
    for(int i=1;i<=n;i++) if(mn[i]!=dfn[i]||mx[i]!=dfn[i]+siz[i]-1) return 0;
    return 1;
}

int main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v);
        AdEg(v,u);
    }
    
    for(int i=1;i<=n;i++) dfn[i]=i;
    sort(dfn+1,dfn+n+1);
    do{
        if(Check()){
            for(int i=1;i<=n;i++) ans[i][dfn[i]]++;
        }
    }while(next_permutation(dfn+1,dfn+n+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<ans[i][j]<<' ';
        cout<<endl;
    }

    return 0;
}