#include<bits/stdc++.h>

using namespace std;

ifstream fin("bookstore.in");
ofstream fout("bookstore.out");
#define cin fin
#define cout fout
#define endl '\n'

#define allc(x) x.begin(),x.end()
#define ssiz(x) (signed)x.size()
const int N=2e5+9;

int fi[N],ne[N],to[N],id[N],adj,n,m;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    id[adj]=z;
}

int fa[N],dfn[N],dep[N],dcnt;
vector<pair<int,int>> cir[2];
void DFS(int x){
    dfn[x]=++dcnt;
    // cout<<x<<' '<<fa[x]<<' '<<dep[x]<<' '<<dcnt<<endl;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        // cout<<x<<' '<<y<<' '<<fa[x]<<' '<<fa[y]<<' '<<dfn[y]<<endl;
        if(y==fa[x]) continue ;
        if(!dfn[y]){
            // cout<<x<<' '<<y<<endl;
            fa[y]=x;
            dep[y]=dep[x]+1;
            DFS(y);
        }else if(dfn[y]>dfn[x]){
            // cout<<x<<' '<<y<<' '<<dep[x]<<' '<<dep[y]<<endl;
            cir[dep[x]-dep[y]&1^1].push_back({x,y});
        }
    }
}
int Find(int src,int trg){
    for(int i=fi[src];i;i=ne[i]){
        int x=to[i];
        if(x==trg) return id[i];
    }
    return -1;
}
void Pth(vector<int> &res,int u,int v){
    // cout<<u<<' '<<v<<endl;
    vector<int> tmp;
    if(dep[u]>dep[v]){
        int cur=u;
        while(cur!=v){
            // cout<<cur<<' '<<v<<endl;
            tmp.push_back(Find(fa[cur],cur));
            cur=fa[cur];
        }
    }else{
        int cur=v;
        while(cur!=u){
            // cout<<cur<<' '<<u<<endl;
            tmp.push_back(Find(fa[cur],cur));
            cur=fa[cur];
        }
        reverse(allc(tmp));
    }
    res.insert(res.end(),allc(tmp));
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]) x=fa[x];
    while(x!=y) x=fa[x],y=fa[y];
    return x;
}
void Clear(){
    for(int i=1;i<=n;i++) fi[i]=fa[i]=dfn[i]=dep[i]=0;
    for(int k:{0,1}) cir[k].clear();
    adj=0;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1,u,v;i<=m;i++){
            cin>>u>>v;
            AdEg(u,v,i);
            AdEg(v,u,i);
        }

        vector<int> ans;
        for(int i=1;i<=n;i++){
            if(dfn[i]) continue ;
            for(int j:{0,1}) cir[j].clear();
            fa[i]=i,DFS(i);
            if(ssiz(cir[0])){
                int a=cir[0][0].first,b=cir[0][0].second;
                ans.push_back(Find(a,b));
                Pth(ans,b,a);
            }else if(ssiz(cir[1])>1){
                int a=cir[1][0].first,b=cir[1][0].second;
                int c=cir[1][1].first,d=cir[1][1].second;
                if(dep[a]>dep[c]) swap(a,c),swap(b,d);
                int lca=LCA(b,d);
                if(dep[a]<=dep[lca]){
                    if(dep[c]<=dep[lca]){
                        // cout<<"Case A "<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<lca<<endl;
                        Pth(ans,c,a);
                        ans.push_back(Find(a,b));
                        Pth(ans,b,lca);
                        Pth(ans,lca,d);
                        ans.push_back(Find(d,c));
                    }else{
                        // cout<<"Case B "<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<lca<<endl;
                        Pth(ans,lca,a);
                        ans.push_back(Find(a,b));
                        Pth(ans,b,lca);
                        Pth(ans,lca,c);
                        ans.push_back(Find(c,d));
                        Pth(ans,d,c);
                    }
                }else{
                    // cout<<"Case C "<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<lca<<endl;
                    ans.push_back(Find(a,b));
                    Pth(ans,b,a);
                    Pth(ans,a,lca);
                    Pth(ans,lca,c);
                    ans.push_back(Find(c,d));
                    Pth(ans,d,c);
                }
            }
            if(ans.size()) break ;
        }

        if(!ssiz(ans)) cout<<-1<<endl;
        else{
            cout<<ssiz(ans)-ssiz(ans)/2<<' '<<ssiz(ans)/2<<endl;
            for(int i=0;i<ssiz(ans);i++) if(~i&1) cout<<ans[i]<<' ';cout<<endl;
            for(int i=0;i<ssiz(ans);i++) if(i&1) cout<<ans[i]<<' ';cout<<endl;
        }
        Clear();
    }

    return 0;
}