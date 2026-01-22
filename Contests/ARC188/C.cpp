#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

int fa[N<<1],res[N],ans[N],vis[N],n,m;
vector<int> a[N],b[N],son[N<<1];
int Find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){fa[Find(x)]=Find(y);}
void MMerge(vector<int> &p,vector<int> &q){
    if(!p.size()&&!q.size()) return ;
    vector<int> a,b;
    for(int x:p) a.push_back(x),b.push_back(x+n);
    for(int x:q) a.push_back(x+n),b.push_back(x);
    int u=a.back();
    for(int x:a) Merge(u,x);
    int v=b.back();
    for(int x:b) Merge(v,x);
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v,x;i<=m;i++){
        cin>>u>>v>>x;
        if(!x) a[u].push_back(v);
        else b[u].push_back(v);
    }

    iota(fa+1,fa+n+n+1,1);
    for(int i=1;i<=n;i++) MMerge(a[i],b[i]);
    for(int i=1;i<=n;i++){
        if(Find(i)==Find(i+n)){
            cout<<-1<<endl;
            return 0;
        }
        son[Find(i)].push_back(i);
        son[Find(i+n)].push_back(i+n);
    }
    for(int i=1;i<=n+n;i++){
        if(!son[i].size()) continue ;
        if(vis[son[i].back()%n]) continue ;
        for(int x:son[i]){
            vis[x%n]=1;
            if(x>n) res[x%n]=1;
            else res[x%n]=0;
        }
    }
    res[n]=res[0];

    for(int i=1;i<=n;i++){
        ans[i]=res[i];
        if(a[i].size()){
            if(res[a[i].back()]) ans[i]^=1;
        }else if(b[i].size()){
            if(!res[b[i].back()]) ans[i]^=1;
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i];cout<<endl;

    return 0;
}