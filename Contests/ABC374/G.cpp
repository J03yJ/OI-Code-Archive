#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;

int fi[N],ne[N<<1],to[N<<1],ind[N<<1],adj=1;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    ind[y]++;
}

int blk[N],vis[N],ps[N],up[N],flag,ans,res,m,n=26;
vector<int> stk;
void Del(int x){
    blk[x]=1;
    ind[to[x]]--;
}
void DFS(int x,int fa){
    stk.push_back(x);
    vis[x]=ps[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(blk[i]) continue ;
        if(y==fa) continue ;
        // cout<<x<<' '<<y<<endl;
        if(vis[y]){
            // cout<<"!!"<<endl;
            flag=1;
            up[y]=i;
            vector<int> tmp;
            for(int j=stk.size()-1;~j;j--){
                tmp.push_back(stk[j]);
                if(stk[j]==y) break ;
            }
            // for(int z:tmp) cout<<z<<' ';cout<<endl;
            for(int z:tmp) Del(up[z]),Del(up[z]^1);
            int f=1;
            for(int z:tmp) if(ind[z]) f=0;
            ans+=f;
        }else{
            up[y]=i;
            DFS(y,x);
        }
        if(flag){
            stk.pop_back();
            vis[x]=0;
            return ;
        }
    }
    // cout<<x<<" : "<<stk.back()<<endl;
    stk.pop_back();
    vis[x]=0;
}
void Solve(int x,int rt){
    vis[x]=1;
    if(ind[x]==1) res++;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(blk[i]) continue ;
        if(vis[y]) continue ;
        Solve(y,rt);
    }
}

int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        char u,v;
        cin>>u>>v;
        int x=u-'A'+1,y=v-'A'+1;
        AdEg(x,y);
        AdEg(y,x);
    }

    while(true){
        // cout<<"Fl"<<endl;
        for(int i=1;i<=n;i++) ps[i]=up[i]=0;
        for(int i=1;i<=n;i++){
            if(ps[i]) continue ;
            DFS(i,-1);
            if(flag) break ;
        }
        if(flag) flag=0;
        else break ;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            res=0;
            Solve(i,i);
            ans+=(res+1)/2;
        }
    }

    cout<<ans<<endl;

    return 0;
}