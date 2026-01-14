#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int d[N],cnt[N],p[N],fa[N],tot,tot2,n;
vector<int> e[N];
int Win(int u,int v){return cnt[u]-(d[v]<=1);}
long long ans;
void DFS(int x){
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        fa[y]=x,DFS(y);
        p[x]+=p[y];
        if(d[x]>1&&(d[y]<=1||cnt[y])) ans+=p[y]; 
    }
    if(d[x]>1&&!cnt[x]) p[x]++;
    if(d[x]>1) tot++;
}
void Work(int x,int psum){
    if(d[x]<=1) ans+=tot;
    else if(Win(fa[x],fa[fa[x]])) ans+=psum;
    for(int y:e[x]) if(y!=fa[x]) psum+=p[y];
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        int tmp=psum-p[y];
        if(d[x]>1&&!Win(x,y)) tmp++;
        Work(y,tmp);
    }
}

signed main(){
    d[0]=1e18;
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
            d[u]++,d[v]++;
        }
        for(int i=1;i<=n;i++) for(int j:e[i]) cnt[i]+=d[j]<=1;
        for(int i=1;i<=n;i++){
            if(d[i]>1){
                tot++;
                if(!cnt[i]) tot2++;
            }
        }
        for(int i=1;i<=n;i++){
            if(d[i]<=1){
                ans+=tot;
                continue ;
            }
            if(cnt[i]) ans+=tot2*(d[i]-cnt[i]-1);
        }
        // DFS(1);
        // Work(1,0);
        cout<<ans<<endl;
        for(int i=1;i<=n;i++) e[i].clear(),d[i]=cnt[i]=fa[i]=p[i]=0;
        tot=ans=tot2=0;
    }

    return 0;
}