#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fa[N];
vector<int> ans[N];
int Find(int x){
    if(x==fa[x]) return x;
    else return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    fa[y]=x;
    for(int u:ans[y]) ans[x].push_back(u);
    ans[y].clear();
    sort(ans[x].begin(),ans[x].end(),[](int a,int b){return a>b;});
    while(ans[x].size()>10) ans[x].pop_back();
}

int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) fa[i]=i,ans[i].push_back(i);
    while(q--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1) Merge(x,y);
        else{
            x=Find(x);
            if(y>ans[x].size()) cout<<-1<<endl;
            else cout<<ans[x][y-1]<<endl;
        }
        // cout<<op<<' '<<x<<' '<<y<<" : ";
        // for(int u:ans[x]) cout<<u<<' ';cout<<endl;
    }
    

    return 0;
}