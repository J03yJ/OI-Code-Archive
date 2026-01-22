#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=2e5+9;

vector<int> e[N];
vector<array<int,3>> ans;
int fa[N],u[N],v[N],n,m;
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y,bool flag){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    if(e[x].size()<e[y].size()) swap(x,y);
    fa[y]=x;
    if(flag){
        int tmp=e[x].back();
        e[x].pop_back();
        ans.push_back({tmp,u[tmp],y});
    }
    e[x].insert(e[x].end(),e[y].begin(),e[y].end());
    e[y].clear();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        if(Find(u[i])==Find(v[i])) e[Find(u[i])].push_back(i);
        else Merge(u[i],v[i],0);
    }

    priority_queue<pii> q;
    for(int i=1;i<=n;i++) if(i==Find(i)) q.push({e[i].size(),i});
    while(q.size()>1){
        int x=sec(q.top());q.pop();
        int y=sec(q.top());q.pop();
        Merge(x,y,1);
        q.push({e[x].size(),x});
    }

    cout<<ans.size()<<endl;
    for(auto t:ans) cout<<t[0]<<' '<<t[1]<<' '<<t[2]<<endl;

    return 0;
}