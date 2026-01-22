#include<bits/stdc++.h>

using namespace std;

const int N=4e3+9;
int fi[N],to[N<<2],ne[N<<2],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int ans[N],vis[N];
void dfs(int x){
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        dfs(y);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;char a,b;
        cin>>x>>a>>y>>b;
        if(a=='N'&&b=='N') adeg(x+n,y),adeg(y+n,x);
        if(a=='N'&&b=='Y') adeg(x+n,y+n),adeg(y,x);
        if(a=='Y'&&b=='N') adeg(x,y),adeg(y+n,x+n);
        if(a=='Y'&&b=='Y') adeg(x,y+n),adeg(y,x+n);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n<<1;j++) vis[j]=0;
        dfs(i);
        if(!vis[i+n]) ans[i]|=1;
        for(int j=1;j<=n<<1;j++) vis[j]=0;
        dfs(i+n);
        if(!vis[i]) ans[i]|=2;
    }

    string s="";
    for(int i=1;i<=n;i++){
        if(!ans[i]){
            s="IMPOSSIBLE";
            break ;
        }
        if(ans[i]==1) s+='N';
        else if(ans[i]==2) s+='Y';
        else s+='?';
    }

    cout<<s<<endl;

    return 0;
}