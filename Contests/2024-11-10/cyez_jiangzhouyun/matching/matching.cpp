#include<bits/stdc++.h>

using namespace std;

ifstream fin("matching.in");
ofstream fout("matching.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
const int N=2e5+9;

int a[N],u[N],v[N],r[N],ans[N],n,tot;
vector<pair<int,int>> e[N];
vector<int> tmp[N];

int vis[N],c[N],root;
void DFS(int x){
    vis[x]=1;
    for(auto p:e[x]){
        int y=p.first;
        if(!vis[y]){
            c[y]=c[x]^1;
            DFS(y);
        }else if(c[y]==c[x]) root=x;
    }
}
int dep[N],siv[N],fa[N];
int Solve(int x){
    int cnt=r[x];
    siv[x]=1;
    for(auto p:e[x]){
        int y=p.first;
        if(siv[y]) continue ;
        fa[y]=x,dep[y]=dep[x]+1;
        int tmp=Solve(y);
        if(tmp==1){
            cnt^=1;
            ans[p.second]^=1;
        }
    }
    return cnt;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        
        tot=0;
        map<int,int> mp;
        for(int i=1;i<=n;i++){
            if(!mp[i-a[i]]) mp[i-a[i]]=++tot;
            u[i]=mp[i-a[i]];
            r[u[i]]^=1;
        }
        mp.clear();
        for(int i=1;i<=n;i++){
            if(!mp[i+a[i]]) mp[i+a[i]]=++tot;
            v[i]=mp[i+a[i]];
        }
        for(int i=1;i<=n;i++){
            e[u[i]].push_back({v[i],i});
            e[v[i]].push_back({u[i],i});
        }

        int err=0;
        for(int i=1,flag;i<=tot;i++){
            if(vis[i]) continue ;
            root=0,flag=1;
            DFS(i);
            if(!root) root=i,flag=0;
            int cnt=Solve(root);
            if(!cnt) continue ;
            if(!flag){
                err=1;
                continue ;
            }
            int pos=0;
            for(auto p:e[root]){
                int x=p.first;
                if(dep[x]&1) continue ;
                pos=x;
                ans[p.second]^=1;
                break ;
            }
            vector<int> pth;
            while(pos!=root){
                pth.push_back(pos);
                pos=fa[pos];
            }
            pth.push_back(root);
            reverse(allc(pth));
            for(int j=1;j<ssiz(pth);j++){
                for(auto p:e[pth[j]]){
                    if(p.first!=pth[j-1]) continue ;
                    ans[p.second]^=1;
                    break ;
                }
            }
        }

        if(err) cout<<"No"<<endl;
        else{
            cout<<"Yes"<<endl;
            for(int i=1;i<=n;i++){
                if(ans[i]) tmp[v[i]].push_back(i);
                else tmp[u[i]].push_back(i);
            }
            for(int i=1;i<=tot;i++){
                for(int j=0;j<ssiz(tmp[i]);j+=2) cout<<tmp[i][j]<<' '<<tmp[i][j+1]<<endl;
            }
        }

        for(int i=1;i<=tot;i++){
            e[i].clear(),tmp[i].clear();
            vis[i]=siv[i]=dep[i]=fa[i]=c[i]=r[i]=0;
        }
        for(int i=1;i<=n;i++){
            a[i]=u[i]=v[i]=ans[i]=0;
        }
    }

    return 0;
}