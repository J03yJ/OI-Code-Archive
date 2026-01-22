#include<bits/stdc++.h>

using namespace std;

const int N=1e4+9;

ifstream fin("heap.in");
ofstream fout("heap.out");
#define cin fin
#define cout fout

int fa[N],val[N];
vector<int> son[N],c[N];
int L[N],R[N];

bool err;
int dfs(int x,int mn){
    int mx=0;
    if(val[x]>mn) err=1;
    if(val[x]) mn=min(val[x],mn);
    for(int y:son[x]) mx=max(mx,dfs(y,mn));
    if(err||mx>=mn) err=1;
    else L[x]=max(mx,max(val[x],1)),R[x]=mn;
    return mx;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>fa[i],son[fa[i]].push_back(i);
        for(int i=1;i<=n;i++) cin>>val[i];

        int root=0;
        for(int i=1;i<=n;i++) if(!fa[i]) root=i;
        if(!val[root]) val[root]=n;
        err=0;
        dfs(root,n+1);
        if(err){
            cout<<0<<endl;
            for(int i=1;i<=n;i++) son[i].clear();
            continue ;
        }
        for(int i=1;i<=n;i++) c[L[i]].push_back(R[i]);
        priority_queue<int> q;
        for(int i=1;i<=n;i++){
            for(int x:c[i]) q.push(-x);
            c[i].clear();
            int k=-q.top();q.pop();
            if(k<i){
                err=1;
            }
        }

        cout<<(!err)<<endl;

        for(int i=1;i<=n;i++) son[i].clear();
    }
    return 0;
}