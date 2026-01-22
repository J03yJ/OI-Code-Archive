#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dep[N],mxdep[N],fa[N],n;
void DFS(int x){
    mxdep[x]=dep[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS(y);
        mxdep[x]=max(mxdep[x],mxdep[y]);
    }
}
int pre[N],suc[N];
void Clear(){
    for(int i=1;i<=n;i++) dep[i]=mxdep[i]=fa[i]=pre[i]=suc[i]=fi[i]=0;
    adj=0;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            AdEg(u,v);
            AdEg(v,u);
        }
        dep[1]=1;
        DFS(1);
        for(int i=2;i<=n;i++) suc[dep[i]]++,pre[mxdep[i]]++;
        for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
        for(int i=n;i>=1;i--) suc[i]+=suc[i+1];

        int ans=1e9;
        for(int i=1;i<=n;i++) ans=min(ans,pre[i-1]+suc[i+1]);
        cout<<ans<<endl;

        Clear();
    }
}