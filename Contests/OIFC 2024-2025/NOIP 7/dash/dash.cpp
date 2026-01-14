#include<bits/stdc++.h>

using namespace std;

ifstream fin("dash.in");
ofstream fout("dash.out");
#define cin fin
#define cout fout

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],a[N],adj=1,n,m,d;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dist[N];
void Nxt(int x,int pre,int dep,vector<int> &res){
    // cout<<" : "<<x<<' '<<dep<<' '<<pre<<endl;
    if(!dep){
        if(dist[x]) return ;
        if(a[x]) return ;
        dist[x]=1;
        res.push_back(x);
        return ;
    }
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==pre) continue ;
        Nxt(y,x,dep-1,res);
    }
}
void BFS(){
    queue<int> q;
    q.push(1);
    dist[1]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        vector<int> nxt;
        // cout<<x<<" : "<<endl;
        Nxt(x,0,d,nxt);
        for(int y:nxt){
            dist[y]=dist[x]+1;
            q.push(y);
            // cout<<y<<' ';
        }
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(dist[y]) continue ;
            if(a[y]) continue ;
            dist[y]=dist[x]+1;
            q.push(y);
            // cout<<y<<' ';
        }
        // cout<<endl;
    }
}

int main(){
    int tmp;
    cin>>tmp>>n>>m>>d;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]^=1;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    BFS();
    for(int i=1;i<=n;i++) cout<<dist[i]-1<<' ';
    cout<<endl;

    return 0;
}