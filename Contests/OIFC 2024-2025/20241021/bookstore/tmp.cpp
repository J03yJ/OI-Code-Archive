#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int d[N],del[N],fa[N],dep[N],anc[N],n,m;
vector<int> a[N],id[N],son[N],ans;
void Clear(){
    for(int i=1;i<=n;i++){
        d[i]=del[i]=fa[i]=dep[i]=anc[i]=0;
        a[i].clear(),id[i].clear(),son[i].clear();
    }
    ans.clear();
}
int Find(int x,int y){
    for(int i=0;i<a[x].size();i++) if(a[x][i]==y) return id[x][i];
    return -1;
}
void AddP(int x,int y){
    int cur=y;
    while(cur!=x){
        ans.push_back(Find(fa[cur],cur));
        cur=fa[cur];
        cout<<cur<<' '<<x<<endl;
    }
}
void DAddP(int x,int y){
    vector<int> tmp;
    int cur=y;
    while(cur!=x){
        tmp.push_back(Find(fa[cur],cur));
        cur=fa[cur];
    }
    reverse(tmp.begin(),tmp.end());
    for(int x:tmp) ans.push_back(x);
}
void DFS1(int x){
    anc[x]=0;
    for(int i=0;i<a[x].size();i++){
        int y=a[x][i];
        if(del[y]) continue ;
        if(y==fa[x]) continue ;
        if(!fa[y]){
            fa[y]=x;
            dep[y]=dep[x]+1;
            DFS1(y);
        }
        else if(dep[y]<dep[x]&&y!=fa[x]){
            if(dep[x]-dep[y]&1){
                ans.push_back(id[x][i]);
                AddP(y,x);
            }else{
                if(!anc[x]){
                    anc[x]=y;
                    son[y].push_back(x);
                }else{
                    if(dep[y]>dep[anc[x]]) swap(anc[x],y);
                    ans.push_back(Find(y,x));
                    ans.push_back(Find(anc[x],x));
                }
            }
        }
        if(ans.size()) return ;
    }
}
int LCA(int u,int v){
    if(dep[u]<dep[v]) swap(u,v);
    while(dep[u]>dep[v]) u=fa[u];
    while(u!=v) u=fa[u],v=fa[v];
    return u;
}
void DFS2(int x,int f){
    if(son[x].size()>1){
        int u=son[x][0],v=son[x][1];
        if(dep[u]>dep[v]) swap(u,v);
        ans.push_back(Find(x,u));
        ans.push_back(Find(x,v));
        AddP(u,v);
    }else if(son[x].size()){
        if(!f) f=x;
        else{
            int u=son[f][0],v=son[x][0],l=LCA(u,v);
            if(dep[x]<dep[l]){
                AddP(l,v);
                reverse(ans.begin(),ans.end());
                ans.push_back(Find(x,v));
                AddP(f,x);
                ans.push_back(Find(f,u));
                AddP(l,u);
            }else{
                AddP(f,l);
                ans.push_back(Find(f,u));
                AddP(l,u);
                DAddP(l,x);
                ans.push_back(Find(x,v));
                AddP(x,v);
            }
            return ;
        }
    }
    for(int i=0;i<a[x].size();i++){
        int y=a[x][i];
        if(del[y]) continue ;
        if(y==fa[x]) continue ;
        if(fa[y]==x) DFS2(y,f);
        if(ans.size()) return ;
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1,u,v;i<=m;i++){
            cin>>u>>v;
            a[u].push_back(v),id[u].push_back(i);
            a[v].push_back(u),id[v].push_back(i);
            d[u]++,d[v]++;
        }

        priority_queue<pair<int,int>> q;
        for(int i=1;i<=n;i++) q.push({-d[i],i});
        while(q.size()&&-q.top().first<2){
            int x=q.top().second,val=-q.top().first;
            q.pop();
            if(val!=d[x]) continue ;
            del[x]=1;
            for(int y:a[x]){
                if(del[y]) continue ;
                d[y]--;
                q.push({-d[y],y});
            }
        }

        int flag=0;
        for(int i=1;i<=n;i++) if(!del[i]) flag=1;
        if(!flag){
            cout<<-1<<endl;
            Clear();
            continue ;
        }

        for(int i=1;i<=n;i++){
            if(del[i]) continue ;
            if(fa[i]) continue ;
            try{
                fa[i]=i,DFS1(i);
            }catch(exception &e){
                cout<<e.what()<<endl;
            }
            if(ans.size()) break ;
        }

        if(!ans.size()) cout<<-1<<endl;
        else{
            cout<<ans.size()/2<<' '<<ans.size()/2<<endl;
            for(int i=0;i<ans.size();i++) if(i&1) cout<<ans[i]<<' ';cout<<endl;
            for(int i=0;i<ans.size();i++) if(~i&1) cout<<ans[i]<<' ';cout<<endl;
        }
        Clear();
    }

    return 0;
}