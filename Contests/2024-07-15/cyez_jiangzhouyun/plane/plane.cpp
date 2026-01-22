#include<bits/stdc++.h>

using namespace std;

ifstream fin("plane.in");
ofstream fout("plane.out");
#define cin fin
#define cout fout

const int N=1e3+9;

int fa[N*N],u[N][N],r[N][N],n,m,q;
inline int id(int x,int y){
    return (x-1)*n+y;
}
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    fa[find(y)]=find(x);
}

signed main(){ 
    cin>>q>>m>>n;
    for(int i=1;i<=q;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        if(x1==x2){
            if(y1>y2) swap(y1,y2) ;
            for(int j=y1+1;j<=y2;j++) r[x1][j]=1;
        }else{
            if(x1>x2) swap(x1,x2);
            for(int j=x1+1;j<=x2;j++) u[j][y1]=1;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            fa[id(j,i)]=id(j,i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            if(r[j][i]) continue ;
            merge(id(j,i),id(j+1,i));
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            if(u[j][i]) continue ;
            merge(id(j,i),id(j,i+1));
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(find(id(j,i))==id(j,i)) ans++;
            // cout<<j<<' '<<i<<' '<<find(id(j,i))<<' '<<id(j,i)<<endl;
        }
    }

    cout<<ans<<endl;

    return 0;
}