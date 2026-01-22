#include<bits/stdc++.h>

using namespace std;

const int N=4e6+9;
const int M=1e3+9;

int fa[N],siz[N];
int find(int x){
    if(fa[x]==x) return fa[x];
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y) return ;
    fa[y]=x;
    siz[x]+=siz[y];
}

int n,m;
int H[M][M];
int trs(int x,int y){
    return (x-1)*m+y;
}
vector<pair<int,int>> a[N];

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

int main(){
    int h;
    cin>>n>>m>>h;
    n+=2;m+=2;
    for(int i=1;i<=n*m;i++) fa[i]=i,siz[i]=1;
    for(int i=1;i<m;i++) merge(trs(1,i),trs(1,i+1));
    for(int i=1;i<m;i++) merge(trs(n,i),trs(n,i+1));
    for(int i=1;i<n;i++) merge(trs(i,1),trs(i+1,1));
    for(int i=1;i<n;i++) merge(trs(i,m),trs(i+1,m));
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){
            cin>>H[i][j];
            a[H[i][j]].push_back({i,j});
        }
    }
    for(int i=1;i<=h;i++){
        for(pair<int,int> p:a[i]){
            int x=p.first,y=p.second;
            for(int k=0;k<4;k++){
                int xx=x+dx[k],yy=y+dy[k];
                // cout<<x<<' '<<y<<' '<<xx<<' '<<yy<<endl;
                if(H[xx][yy]<=i) merge(trs(x,y),trs(xx,yy));
            }
        }
        cout<<n*m-siz[find(1)]<<endl;
    }
}