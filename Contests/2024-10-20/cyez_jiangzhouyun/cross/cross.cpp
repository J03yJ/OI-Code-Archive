#include<bits/stdc++.h>

using namespace std;

ifstream fin("cross.in");
ofstream fout("cross.out");
#define cin fin
#define cout fout

const int N=3e5+9;
const int M=5e3+9;
const int B=100;
const int lgN=20;

unsigned f[M][M],g[M][M],n,q;
int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int fa[N][lgN],dep[N],c[N];
void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x][0]) continue ;
        fa[y][0]=x;
        c[y]=w[i];
        dep[y]=dep[x]+1;
        DFS(y);
    }
}
void Init(){
    fa[1][0]=1;
    dep[1]=1;
    DFS(1);
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++){
            fa[i][k]=fa[fa[i][k-1]][k-1];
        }
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    if(x==y) return x;
    for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}
int Dist(int x,int y){
    int z=LCA(x,y);
    return dep[x]+dep[y]-dep[z]*2;
}

int main(){
    f[1][1]=g[1][1]=1;
    for(int i=2;i<=B;i++){
        for(int j=1;j<=i;j++){
            g[i][j]=f[i-1][j]+f[i-1][j-1]-f[i-2][j-1];
            f[i][j]=g[i][j]<<1;
        }
    }
    
    cin>>n>>q;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w),AdEg(v,u,w);
    }
    Init();
    while(q--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1) c[x]=y;
        else{
            if(Dist(x,y)>B){
                cout<<0<<endl;
                continue ;
            }
            int z=LCA(x,y);
            vector<int> a,b;
            while(x!=z) a.push_back(x),x=fa[x][0];
            while(y!=z) b.push_back(y),y=fa[y][0];
            reverse(b.begin(),b.end());
            for(int x:b) a.push_back(x);
            unsigned ans=0;
            for(int i=0;i<a.size();i++) ans+=g[a.size()][i+1]*unsigned(c[a[i]]);
            cout<<ans<<endl;
        }
    }

    return 0;
}