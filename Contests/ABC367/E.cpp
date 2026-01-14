#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e6+9;

int fa[N],a[N],vis[N],ans[N],n,m;
vector<int> son[N];
vector<int> stk,r;
void DFS(int x,int k,int pos){
    if(!vis[x]) vis[x]=1;
    stk.push_back(x);
    if(k<stk.size()) ans[x]=a[stk[stk.size()-1-k]];
    else{
        int tmp=k-stk.size()+1;
        ans[x]=a[r[(pos+tmp)%r.size()]];
    }
    for(int y:son[x]){
        if(vis[y]==-1) continue ;
        DFS(y,k,pos);
    }
    stk.pop_back();
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>fa[i],son[fa[i]].push_back(i);
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        int x=i;
        while(!vis[x]){
            vis[x]=1;
            x=fa[x];
        }
        int y=x;
        r.clear();
        while(true){
            r.push_back(y);
            y=fa[y];
            if(y==x) break ;
        }
        for(int j=0;j<r.size();j++) ans[r[j]]=a[r[(j+m)%r.size()]],vis[r[j]]=-1;
        for(int j=0;j<r.size();j++) DFS(r[j],m,j);
    }

    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}