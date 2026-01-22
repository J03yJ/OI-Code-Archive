#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],b[N],n,k,cnt;
map<int,int> mp;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int vis[N];
void DFS(int x){
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        DFS(y);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]++,k^=a[i];
    for(int i=1;i<=n;i++) cin>>b[i],mp[b[i]]--;
    mp[k]++;
    
    int ans=0;
    for(auto p:mp) if(p.second<0) return cout<<-1<<endl,0;
    for(auto &p:mp) p.second=++cnt;
    for(int i=1,u,v;i<=n;i++){
        if(a[i]==b[i]) continue ;
        u=mp[a[i]],v=mp[b[i]];
        AdEg(u,v);
        AdEg(v,u);
    }
    for(int i=1;i<=cnt;i++){
        if(!fi[i]) continue ;
        if(vis[i]) continue ;
        DFS(i);
        ans++;
    }
    if(fi[mp[k]]) ans--;

    cout<<ans+adj/2<<endl;

    return 0;
}