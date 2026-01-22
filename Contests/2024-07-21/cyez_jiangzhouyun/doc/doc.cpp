#include<bits/stdc++.h>

using namespace std;

ifstream fin("doc.in");
ofstream fout("doc.out");
#define cin fin
#define cout fout

const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
void ClearEdge(int n){
    for(int i=1;i<=n;i++) fi[i]=0;
    adj=0;
}

int fa[N],dep[N];
void DFS(int x,int &mxdep){
    mxdep=max(mxdep,dep[x]);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        dep[y]=dep[x]+1;
        fa[y]=x;
        DFS(y,mxdep);
    }
}
void GetSib(int x,int &lft,vector<int> &res){
    if(lft) res.push_back(x),lft--;
    else return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        GetSib(y,lft,res);
        if(res.back()!=x) res.push_back(x);
    }
}
void ClearFa(int n){
    for(int i=1;i<=n;i++) fa[i]=0;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<n;i++){
            int x,y;
            cin>>x>>y;
            AddEdge(x,y);
            AddEdge(y,x);
        }

        int mxdep=0;
        dep[1]=1;
        DFS(1,mxdep);
        vector<int> ans;
        if(mxdep>=k){
            int pos=0;
            for(int i=1;i<=n;i++) if(dep[i]==k) pos=i;
            while(true){
                ans.push_back(pos);
                if(pos==1) break ;
                pos=fa[pos];
            }
            reverse(ans.begin(),ans.end());
        }else{
            int pos=0,lft=k-mxdep;
            for(int i=1;i<=n;i++) if(dep[i]==mxdep) pos=i;
            while(true){
                ans.push_back(pos);
                if(pos==1) break ;
                for(int i=fi[fa[pos]];i;i=ne[i]){
                    int y=to[i];
                    if(y==fa[fa[pos]]) continue ;
                    if(y==pos) continue ;
                    ans.push_back(fa[pos]);
                    int tmp=ans.size();
                    GetSib(y,lft,ans);
                    if(ans.size()==tmp) ans.pop_back();
                }
                pos=fa[pos];
            }
            reverse(ans.begin(),ans.end());
        }

        cout<<ans.size()<<endl;
        for(int x:ans) cout<<x<<' ';cout<<endl;

        ClearEdge(n);
        ClearFa(n);
    }
}