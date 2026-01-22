#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int dis[N],vis[N];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v);
    }

    queue<int> q;
    q.push(1);vis[1]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(vis[y]){
                if(y==1){
                    cout<<dis[x]+1<<endl;
                    return 0;
                }
                continue ;
            }
            vis[y]=1;
            dis[y]=dis[x]+1;
            q.push(y);
        }
    }
    cout<<-1<<endl;

    return 0;
}