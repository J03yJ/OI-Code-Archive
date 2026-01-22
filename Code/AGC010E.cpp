#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;
const int M=4e6+9;

int a[N],c[N][N],vis[N],n;
int fi[N],ind[N],to[M<<1],ne[M<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    ind[y]++;
}
void DFS(int x){
    vis[x]=1;
    for(int y=1;y<=n;y++){
        if(!c[x][y]) continue ;
        if(vis[y]) continue ;
        AdEg(x,y);
        DFS(y);
    }
}
int t[N],tcnt;
void Topo(){
    priority_queue<int> q;
    for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
    while(q.size()){
        int x=t[++tcnt]=q.top();
        q.pop();
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            ind[y]--;
            if(!ind[y]) q.push(y);
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) c[i][j]=!(__gcd(a[i],a[j])==1);
    }
    for(int i=1;i<=n;i++) if(!vis[i]) DFS(i);
    Topo();

    for(int i=1;i<=n;i++) cout<<a[t[i]]<<' ';
    cout<<endl;

    return 0;
}